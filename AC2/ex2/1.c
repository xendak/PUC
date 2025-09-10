/* pratica1.c
 * Objetivo: estressar CPU/cache, permitir variações (FP vs int, com/sem desvio,
 * stride) e medir tempo sem perf (timer portátil).
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
static double now_s(void) {
  static LARGE_INTEGER f = {0};
  LARGE_INTEGER c;
  if (f.QuadPart == 0)
    QueryPerformanceFrequency(&f);
  QueryPerformanceCounter(&c);
  return (double)c.QuadPart / (double)f.QuadPart;
}
#else
#include <time.h>
static double now_s(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}
#endif

// Gerador simples e determinístico
static uint32_t xorshift32(uint32_t *state) {
  uint32_t x = *state;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  *state = x;
  return x;
}

// Preenche matrizes com dados pseudoaleatórios em [0,1)
static void fill_float(float *A, float *B, int N, uint32_t seed) {
  uint32_t s = seed ? seed : 123456789u;
  for (int i = 0; i < N * N; ++i) {
    A[i] = (xorshift32(&s) & 0xFFFFFF) / (float)0x1000000; // [0,1)
    B[i] = (xorshift32(&s) & 0xFFFFFF) / (float)0x1000000;
  }
}

static void fill_int(int *A, int *B, int N, uint32_t seed) {
  uint32_t s = seed ? seed : 987654321u;
  for (int i = 0; i < N * N; ++i) {
    A[i] = (int)(xorshift32(&s) & 0xFFFF); // 0..65535
    B[i] = (int)(xorshift32(&s) & 0xFFFF);
  }
}

// Kernel MODE=0: float + DESVIO (branch)
// Acesso com STRIDE e laço i-j (varie STRIDE para observar cache)
static float kernel_float_branch(const float *A, const float *B, float *C,
                                 int N, int STRIDE, int REPEAT) {
  const float thresh = 0.5f;
  float acc = 0.0f;
  for (int r = 0; r < REPEAT; ++r) {
    for (int i = 0; i < N; ++i) {
      // percorre j com passo STRIDE para criar padrões ruins de localidade
      for (int j = 0; j < N; j += STRIDE) {
        int idx = i * N + j;
        float a = A[idx];
        float b = B[idx];
        if (a > thresh) {
          // caminho "pesado": FP + função
          float t = a * b + sinf(a);
          C[idx] = t;
          acc += t;
        } else {
          // caminho "leve"
          float t = a - 0.5f * b;
          C[idx] = t;
          acc += t;
        }
      }
    }
  }
  return acc;
}

// Kernel MODE=1: float SEM DESVIO (branchless)
// Substitui o if por seleção aritmética (mesma carga média, menos mispredict)
static float kernel_float_branchless(const float *A, const float *B, float *C,
                                     int N, int STRIDE, int REPEAT) {
  const float thresh = 0.5f;
  float acc = 0.0f;
  for (int r = 0; r < REPEAT; ++r) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; j += STRIDE) {
        int idx = i * N + j;
        float a = A[idx];
        float b = B[idx];
        // máscaras 0.0f/1.0f obtidas por comparação (true->1.0f, false->0.0f)
        float cond = (a > thresh) ? 1.0f : 0.0f;
        float heavy = a * b + sinf(a);
        float light = a - 0.5f * b;
        float t = cond * heavy + (1.0f - cond) * light;
        C[idx] = t;
        acc += t;
      }
    }
  }
  return acc;
}

// Kernel MODE=2: inteiro (aproximação)
// Remove FP: usa aritmética inteira como aproximação do caso "leve"
// Nota: não há sin() aqui; é um experimento de "trocar FP por int".
static long long kernel_int(const int *A, const int *B, int *C, int N,
                            int STRIDE, int REPEAT) {
  const int thresh = 32768; // ~0.5 * 65536
  long long acc = 0;
  for (int r = 0; r < REPEAT; ++r) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; j += STRIDE) {
        int idx = i * N + j;
        int a = A[idx];
        int b = B[idx];
        // caminho "pesado" aproxima multiplicação (evita FP)
        // e caminho "leve" usa shift para dividir por 2.
        if (a > thresh) {
          int t = a * (b & 0xFF); // deliberadamente tosco p/ custo
          C[idx] = t;
          acc += t;
        } else {
          int t = a - (b >> 1);
          C[idx] = t;
          acc += t;
        }
      }
    }
  }
  return acc;
}

int main(int argc, char **argv) {
  if (argc < 5) {
    fprintf(stderr, "Uso: %s N REPEAT STRIDE MODE\n", argv[0]);
    fprintf(stderr, "  N: tamanho da matriz NxN (ex.: 2048, 4096)\n");
    fprintf(stderr, "  REPEAT: repeticoes do kernel (ex.: 4, 8, 12)\n");
    fprintf(stderr, "  STRIDE: passo no acesso a colunas (1, 2, 4, 8...)\n");
    fprintf(stderr,
            "  MODE: 0=float+desvio | 1=float sem desvio | 2=int (aprox.)\n");
    return 1;
  }

  int N = atoi(argv[1]);
  int REPEAT = atoi(argv[2]);
  int STRIDE = atoi(argv[3]);
  int MODE = atoi(argv[4]);

  if (N <= 0 || REPEAT <= 0 || STRIDE <= 0) {
    fprintf(stderr, "Parâmetros inválidos.\n");
    return 1;
  }

  // Relatório dos parâmetros
  printf("# Params: N=%d REPEAT=%d STRIDE=%d MODE=%d\n", N, REPEAT, STRIDE,
         MODE);

  double t0, t1;

  if (MODE == 0 || MODE == 1) {
    size_t bytes = (size_t)N * (size_t)N * sizeof(float);
    float *A = (float *)malloc(bytes);
    float *B = (float *)malloc(bytes);
    float *C = (float *)malloc(bytes);
    if (!A || !B || !C) {
      fprintf(stderr, "Falha ao alocar %.2f MB.\n", bytes / (1024.0 * 1024.0));
      return 1;
    }

    fill_float(A, B, N, 42u);

    t0 = now_s();
    float checksum = 0.0f;
    if (MODE == 0) {
      checksum = kernel_float_branch(A, B, C, N, STRIDE, REPEAT);
    } else {
      checksum = kernel_float_branchless(A, B, C, N, STRIDE, REPEAT);
    }
    t1 = now_s();

    printf("Tempo(s): %.6f\n", t1 - t0);
    printf("Checksum(float): %.6f\n", checksum);

    free(A);
    free(B);
    free(C);
  } else { // MODE == 2
    size_t bytes = (size_t)N * (size_t)N * sizeof(int);
    int *A = (int *)malloc(bytes);
    int *B = (int *)malloc(bytes);
    int *C = (int *)malloc(bytes);
    if (!A || !B || !C) {
      fprintf(stderr, "Falha ao alocar %.2f MB.\n", bytes / (1024.0 * 1024.0));
      return 1;
    }

    fill_int(A, B, N, 7u);

    t0 = now_s();
    long long checksum = kernel_int(A, B, C, N, STRIDE, REPEAT);
    t1 = now_s();

    printf("Tempo(s): %.6f\n", t1 - t0);
    printf("Checksum(int): %lld\n", checksum);

    free(A);
    free(B);
    free(C);
  }

  return 0;
}
