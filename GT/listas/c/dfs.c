#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4096

typedef struct {
  int src;
  int dst;
} Edge;

typedef enum {
  TREE,
  BACK,
  FORWARD,
  CROSS,
} EdgeType;

typedef struct {
  int dst;
  EdgeType type;
} OutEdge;

typedef struct {
  int *src;
  int *dst;
  int vertices;
  int edges;
} Graph;

// simple arr stack
typedef struct {
  int v_index;
  int e_index;
} Stack;

typedef enum Colour {
  WHITE,
  GRAY,
  BLACK,
} Colour;

int cmp(const void *a, const void *b) {
  const Edge *x = (const Edge *)a;
  const Edge *y = (const Edge *)b;

  return x->src != y->src ? x->src - y->src : x->dst - y->dst;
}

void graph_free(Graph *g) {
  free(g->src);
  free(g->dst);
}

// from edge list to forward star
Graph forward_star(Edge *raw_edges, int vertices, int edges) {
  // TODO: init graph function
  Graph g;
  g.vertices = vertices;
  g.edges = edges;
  // init as 0, since its a counter array
  g.src = (int *)calloc(g.vertices + 2, sizeof(int));
  g.dst = (int *)malloc(g.edges * sizeof(int));

  for (int i = 0; i < g.edges; i++) {
    g.src[raw_edges[i].src + 1]++;
  }

  for (int i = 1; i <= g.vertices; i++) {
    g.src[i + 1] += g.src[i];
  }

  int *p = (int *)malloc((g.vertices + 2) * sizeof(int));
  memcpy(p, g.src, (g.vertices + 2) * sizeof(int));

  for (int i = 0; i < g.edges; i++) {
    int v = raw_edges[i].src;
    g.dst[p[v]++] = raw_edges[i].dst;
  }

  free(p);
  return g;
}

void print_out_edges(int v, int count, OutEdge *e) {
  printf("\nArestas divergentes de V(%d)\n", v);

  for (int i = 0; i < count; i++)
    switch (e[i].type) {
    case TREE:
      printf("Aresta de árvore: (%d -> %d)\n", v, e[i].dst);
      break;
    case BACK:
      printf("Aresta de retorno: (%d -> %d)\n", v, e[i].dst);
      break;
    case FORWARD:
      printf("Aresta de avanço: (%d -> %d)\n", v, e[i].dst);
      break;
    case CROSS:
      printf("Aresta de cruzamento: (%d -> %d)\n", v, e[i].dst);
      break;
    }
}

void dfs(const Graph *g, int query) {
  Colour *colour = (Colour *)calloc(g->vertices + 1, sizeof(Colour));
  int *discovery = (int *)calloc(g->vertices + 1, sizeof(int));
  int timer = 0;

  Stack *stack = (Stack *)malloc((g->vertices + 1) * sizeof(Stack));
  int top = -1;

  int degree = g->src[query + 1] - g->src[query];
  OutEdge *out_edges = (OutEdge *)malloc(degree * sizeof(OutEdge));
  int e_count = 0;

  for (int start = 1; start < g->vertices; start++) {
    if (colour[start] != WHITE)
      continue;

    colour[start] = GRAY;
    discovery[start] = ++timer;
    stack[++top] = (Stack){start, g->src[start]};

    while (top >= 0) {
      Stack *s = &stack[top];
      int curr = s->v_index;

      // if we can still reach a neighboor
      if (s->e_index < g->src[curr + 1]) {
        int next = g->dst[s->e_index];
        s->e_index++;

        if (colour[next] == WHITE) {
          colour[next] = GRAY;
          discovery[next] = ++timer;
          stack[++top] = (Stack){next, g->src[next]};

          printf("Aresta de árvore: (%d -> %d)\n", curr, next);

          if (curr == query)
            out_edges[e_count++] = (OutEdge){next, TREE};

        } else if (curr == query) {
          EdgeType type;
          if (colour[next] == GRAY)
            type = BACK;
          else
            type = (discovery[curr] < discovery[next]) ? FORWARD : CROSS;

          out_edges[e_count++] = (OutEdge){next, type};
        }
      } else {
        // if we can't, means we finished, mark black
        colour[curr] = BLACK;
        timer++;
        top--;
      }
    }
  }

  print_out_edges(query, e_count, out_edges);

  free(out_edges);
  free(colour);
  free(stack);
  free(discovery);
}

int main(void) {
  char file[MAX];
  int query;

  printf("Nome do arquivo: ");
  if (scanf("%4095s", file) != 1) {
    fprintf(stderr, "Erro de leitura.\n");
    return 1;
  }
  printf("Vertice: ");
  if (scanf("%d", &query) != 1) {
    fprintf(stderr, "Erro de leitura.\n");
    return 1;
  }

  FILE *fp = fopen(file, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }

  int vertices, edges;
  if (fscanf(fp, "%d %d", &vertices, &edges) != 2) {
    fprintf(stderr, "Formato invalido.\n");
    return 1;
  }
  if (query < 1 || query > vertices) {
    fprintf(stderr, "Vertice invalido (deve ser entre 1 e %d).\n", vertices);
    return 1;
  }

  Edge *edges_raw = (Edge *)malloc(edges * sizeof(Edge));
  for (int i = 0; i < edges; i++) {
    if (fscanf(fp, "%d %d", &edges_raw[i].src, &edges_raw[i].dst) != 2) {
      fprintf(stderr, "Erro ao ler aresta %d.\n", i + 1);
      return 1;
    }
  }
  fclose(fp);

  qsort(edges_raw, edges, sizeof(Edge), cmp);

  Graph g = forward_star(edges_raw, vertices, edges);
  free(edges_raw);

  printf("\nDFS: Início em V(%d) \n\n", query);
  dfs(&g, query);

  graph_free(&g);
  return 0;
}
