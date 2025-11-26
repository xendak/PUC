// omp_scale.c
// Atv. 02 - Strong & Weak Scaling com OpenMP
// Kernel "embarrassingly parallel" com carga ajustável e medições repetidas.

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <omp.h>

#ifdef _WIN32
#  include <windows.h>
static double now_s(void) {
    static LARGE_INTEGER f = {0};
    LARGE_INTEGER c;
    if (f.QuadPart == 0) QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)f.QuadPart;
}
#else
#  include <time.h>
static double now_s(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}
#endif

static void init_data(double *x, double *y, size_t N) {
    // valores determinísticos e "bem comportados"
    for (size_t i = 0; i < N; ++i) {
        x[i] = (double)(i % 1024) / 1024.0; // [0, ~1)
        y[i] = 0.0;
    }
}

// kernel computacional por elemento; WORK controla a carga de FP
// retorna soma (para evitar DCE e validar resultado)
static double kernel(const double *x, double *y, size_t N, int WORK) {
    double sum = 0.0;

    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (ptrdiff_t i = 0; i < (ptrdiff_t)N; ++i) {
        double v = x[i];
        // "trabalho" controlado: uma sequência de operações FP
        // (mantém a operação no domínio numérico simples)
        for (int k = 0; k < WORK; ++k) {
            // mistura linear + trig simples para evitar simplificação agressiva
            v = 0.999999 * v + 0.000001 * sin(v);
        }
        y[i] = v;
        sum += v;
    }
    return sum;
}

// executa e mede REPEAT vezes; retorna melhor/médio tempo e checksum
static void run_and_measure(size_t N, int REPEAT, int WORK, int threads,
                            double *t_best, double *t_avg, double *checksum) {
    double *x = (double*) malloc(N * sizeof(double));
    double *y = (double*) malloc(N * sizeof(double));
    if (!x || !y) {
        fprintf(stderr, "Falha ao alocar %.2f MB\n", (N*sizeof(double))*1.0/(1024*1024));
        exit(1);
    }
    init_data(x, y, N);

    omp_set_num_threads(threads);

    double best = 1e300, acc_t = 0.0, last_sum = 0.0;
    for (int r = 0; r < REPEAT; ++r) {
        double t0 = now_s();
        double s = kernel(x, y, N, WORK);
        double t1 = now_s();
        double dt = t1 - t0;

        if (dt < best) best = dt;
        acc_t += dt;
        last_sum = s;
    }

    free(x); free(y);
    *t_best = best;
    *t_avg  = acc_t / REPEAT;
    *checksum = last_sum;
}

static void usage(const char *p) {
    fprintf(stderr, "Uso: %s <mode> <N0> <MAX_POW_THREADS> <REPEAT> <WORK>\n", p);
    fprintf(stderr, "  mode: strong | weak\n");
    fprintf(stderr, "  N0: tamanho base (ex.: 1048576)\n");
    fprintf(stderr, "  MAX_POW_THREADS: usa threads=2^t, t=0..MAX (ex.: 3 => 1,2,4,8)\n");
    fprintf(stderr, "  REPEAT: repeticoes por ponto (ex.: 5)\n");
    fprintf(stderr, "  WORK: carga por elemento (ex.: 64)\n");
}

int main(int argc, char **argv) {
    if (argc != 6) { usage(argv[0]); return 1; }

    const char *mode = argv[1];
    size_t N0 = (size_t) strtoull(argv[2], NULL, 10);
    int max_pow = atoi(argv[3]);
    int REPEAT = atoi(argv[4]);
    int WORK = atoi(argv[5]);

    if (N0 == 0 || max_pow < 0 || REPEAT <= 0 || WORK <= 0) {
        usage(argv[0]); return 1;
    }

    printf("# mode=%s N0=%zu MAX_POW_THREADS=%d REPEAT=%d WORK=%d\n",
           mode, N0, max_pow, REPEAT, WORK);
    printf("# Columns: threads  N  t_best(s)  t_avg(s)  checksum  speedup(best)  efficiency(best)\n");

    // baseline para speedup/eficiência
    double base_best = -1.0;

    for (int pow = 0; pow <= max_pow; ++pow) {
        int threads = 1 << pow;
        size_t N = 0;

        if (strcmp(mode, "strong") == 0) {
            N = N0; // trabalho total constante
        } else if (strcmp(mode, "weak") == 0) {
            // trabalho por thread aproximadamente constante => N cresce proporcional a threads
            N = N0 * (size_t)threads;
        } else {
            fprintf(stderr, "mode inválido: %s (use strong|weak)\n", mode);
            return 1;
        }

        double t_best, t_avg, sum;
        run_and_measure(N, REPEAT, WORK, threads, &t_best, &t_avg, &sum);

        if (pow == 0) base_best = t_best;
        double speedup = base_best / t_best;
        double efficiency = speedup / (double)threads;

        printf("%d  %zu  %.6f  %.6f  %.6f  %.4f  %.4f\n",
               threads, N, t_best, t_avg, sum, speedup, efficiency);
        fflush(stdout);
    }

    return 0;
}

