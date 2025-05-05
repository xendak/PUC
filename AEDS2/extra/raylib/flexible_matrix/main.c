#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <raylib.h>

#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CELL_SIZE 60
#define CELL_PADDING 40
#define ARROW_THICKNESS 1.0f
#define FONT_SIZE 20

#define MAX_RAND_VALUE 10000

int max_val = 0;

typedef struct Cell {
  struct Cell *up;
  struct Cell *left;
  struct Cell *right;
  struct Cell *down;
  int val;
} M_CELL;

typedef struct {
  M_CELL *t;
  size_t row;
  size_t col;
} F_MATRIX;

// util
inline int digit_count(int n);

// FIX: change here to debug on NULL pointer, to see if delete works :)
int set_null = 0;
#define FAILURE_VALUE 300

static void *my_malloc(size_t n) {
  set_null += 1;
  if (set_null == FAILURE_VALUE)
    return NULL;
  return malloc(n);
}

#define malloc(x) my_malloc(x)
//

F_MATRIX *init_matrix();
F_MATRIX *create_matrix(size_t row, size_t col);
void print_matrix(F_MATRIX *m);

int get_matrix_val(F_MATRIX *m, size_t row, size_t col);
void set_matrix_val(F_MATRIX *m, size_t row, size_t col);
int is_valid_bound(F_MATRIX *m, size_t pos, size_t val);

M_CELL *get_matrix_cell(F_MATRIX *m, size_t i, size_t j);

void free_matrix(F_MATRIX *m);
void free_cell(M_CELL *c);
// end

// RAYLIB
void draw_matrix_raylib(F_MATRIX *m, Font font);
void DrawArrow(Vector2 startPos, Vector2 endPos, float thickness, Color color);

int main(int argc, char **argv) {

  srand(time(NULL));
  F_MATRIX *m = create_matrix(10, 10);

  if (!m)
    return 1;

  print_matrix(m);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Matrix Visualization");
  SetTargetFPS(60);
  Font font = GetFontDefault();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    draw_matrix_raylib(m, font);

    DrawText("Press ESC to close", 10, SCREEN_HEIGHT - 30, 20, WHITE);

    EndDrawing();
  }
  CloseWindow();

  free_matrix(m);

  return 0;
}

void draw_matrix_raylib(F_MATRIX *m, Font font) {
  if (!m || !m->t)
    return;

  M_CELL *row_start = m->t;
  float start_x = CELL_PADDING * 2;
  float start_y = CELL_PADDING * 2;
  float current_x, current_y;

  float total_width = m->col * CELL_SIZE + (m->col - 1) * CELL_PADDING;
  float total_height = m->row * CELL_SIZE + (m->row - 1) * CELL_PADDING;
  start_x = (SCREEN_WIDTH - total_width) / 2;
  start_y = (SCREEN_HEIGHT - total_height) / 2;

  for (size_t i = 0; i < m->row; i++) {
    M_CELL *current_cell = row_start;
    current_y = start_y + i * (CELL_SIZE + CELL_PADDING);

    for (size_t j = 0; j < m->col; j++) {
      if (!current_cell)
        break;

      current_x = start_x + j * (CELL_SIZE + CELL_PADDING);

      Vector2 cell_center = {current_x + CELL_SIZE / 2.0f,
                             current_y + CELL_SIZE / 2.0f};

      DrawRectangle((int)current_x, (int)current_y, CELL_SIZE, CELL_SIZE,
                    LIGHTGRAY);
      DrawRectangleLines((int)current_x, (int)current_y, CELL_SIZE, CELL_SIZE,
                         DARKGRAY);

      char val_str[16];
      snprintf(val_str, sizeof(val_str), "%d", current_cell->val);
      Vector2 text_size = MeasureTextEx(font, val_str, FONT_SIZE, 1);
      DrawTextEx(font, val_str,
                 (Vector2){cell_center.x - text_size.x / 2.0f,
                           cell_center.y - text_size.y / 2.0f},
                 FONT_SIZE, 1, BLACK);

      if (current_cell->right) {
        Vector2 start = {current_x + CELL_SIZE, cell_center.y};
        Vector2 end = {current_x + CELL_SIZE + CELL_PADDING, cell_center.y};
        DrawArrow(start, end, ARROW_THICKNESS, RED);
      }

      if (current_cell->down) {
        Vector2 start = {cell_center.x, current_y + CELL_SIZE};
        Vector2 end = {cell_center.x, current_y + CELL_SIZE + CELL_PADDING};
        DrawArrow(start, end, ARROW_THICKNESS, BLUE);
      }

      if (current_cell->left) {
        Vector2 start = {current_x, cell_center.y + 2};
        Vector2 end = {current_x - CELL_PADDING, cell_center.y + 2};
        DrawArrow(start, end, ARROW_THICKNESS, DARKGREEN);
      }

      if (current_cell->up) {
        Vector2 start = {cell_center.x + 2, current_y};
        Vector2 end = {cell_center.x + 2, current_y - CELL_PADDING};
        DrawArrow(start, end, ARROW_THICKNESS, PURPLE);
      }

      current_cell = current_cell->right;
    }
    if (row_start) {
      row_start = row_start->down;
    }
  }
}

void DrawArrow(Vector2 startPos, Vector2 endPos, float thickness, Color color) {
  DrawLineEx(startPos, endPos, thickness, color);

  float angle = atan2f(endPos.y - startPos.y, endPos.x - startPos.x);
  float arrowLength = 10.0f;
  float arrowAngle = PI / 6.0f;

  Vector2 arrowPoint1 = {endPos.x - arrowLength * cosf(angle - arrowAngle),
                         endPos.y - arrowLength * sinf(angle - arrowAngle)};
  Vector2 arrowPoint2 = {endPos.x - arrowLength * cosf(angle + arrowAngle),
                         endPos.y - arrowLength * sinf(angle + arrowAngle)};

  DrawLineEx(endPos, arrowPoint1, thickness, color);
  DrawLineEx(endPos, arrowPoint2, thickness, color);
}

inline int digit_count(int n) {
  if (n < 10)
    return 1;
  else if (n < 100)
    return 2;
  else if (n < 1000)
    return 3;
  else if (n < 10000)
    return 4;
  else if (n < 100000)
    return 5;
  else if (n < 1000000)
    return 6;
  else if (n < 10000000)
    return 7;
  else if (n < 100000000)
    return 8;
  else if (n < 1000000000)
    return 9;
  else
    return -1;
}

int my_strlen(const char *str) {
  int i = 0;
  while (str[++i])
    ;
  ;
  return i;
}

void print_matrix(F_MATRIX *m) {
  if (!m || !m->t) {
    perror("Matrix is empty or NULL.\n");
    return;
  }

  int max_digits = digit_count(max_val);
  // always odd to make easier for vertical connection.
  int print_width = max_digits % 2 == 0 ? max_digits + 1 : max_digits;

  const char *h_connector = " -- ";
  int h_connector_len = my_strlen(h_connector);

  M_CELL *row_start = m->t;
  while (row_start) {
    M_CELL *current_cell = row_start;
    while (current_cell) {
      // FIX: change this line to %*0d
      // to get matching 0's instead of spaces?
      printf("%*d", print_width, current_cell->val);

      if (current_cell->right) {
        printf("%s", h_connector);
      }
      current_cell = current_cell->right;
    }
    printf("\n");

    if (row_start->down) {
      current_cell = row_start;
      while (current_cell) {
        // always odd, makes this a simple n/2
        int middle_index = print_width / 2;
        for (int i = 0; i < middle_index; i++)
          printf(" ");

        printf("|");

        for (int i = 0; i < middle_index; i++)
          printf(" ");

        if (current_cell->right)
          for (int i = 0; i < h_connector_len; i++)
            printf(" ");

        current_cell = current_cell->right;
      }
      printf("\n");
    }

    row_start = row_start->down;
  }
}

void free_cell(M_CELL *c) {
  if (c)
    free(c);
}

void free_matrix(F_MATRIX *m) {
  if (m == NULL)
    return;
  if (!m->t) {
    free(m);
    return;
  }

  M_CELL *first_of_row = m->t;

  while (first_of_row) {
    M_CELL *curr = first_of_row;
    M_CELL *next_row = first_of_row->down;
    while (curr) {
      M_CELL *tmp = curr->right;
      free_cell(curr);
      curr = tmp;
    }
    first_of_row = next_row;
  }

  free(m);
}

F_MATRIX *create_matrix(size_t r, size_t c) {
  if ((r == 0 && c != 0) || (r != 0 && c == 0))
    return NULL;

  F_MATRIX *m = init_matrix();
  if (m == NULL)
    return NULL;

  m->col = c;
  m->row = r;

  M_CELL *curr = m->t;
  curr->val = rand() % MAX_RAND_VALUE;

  for (size_t i = 1; i < c; i++) {
    M_CELL *tmp = (M_CELL *)malloc(sizeof(M_CELL));
    if (tmp == NULL) {
      perror("Failed to allocate cell structure inside matrix");
      free_matrix(m);
      return NULL;
    }

    // R L U D
    curr->right = tmp;
    if (i == 0)
      curr->left = NULL;
    curr->up = NULL;
    curr->down = NULL;

    // R L U D
    tmp->right = NULL;
    tmp->left = curr;
    tmp->up = NULL;
    tmp->down = NULL;

    // debugging helper for now
    tmp->val = rand() % MAX_RAND_VALUE;
    max_val = max_val > tmp->val ? max_val : tmp->val;
    // move to next cell;
    curr = curr->right;
  }

  curr = m->t;
  M_CELL *prev_row;
  for (size_t i = 1; i < r; i++) {
    prev_row = curr;
    for (size_t j = 0; j < c; j++) {
      M_CELL *tmp = (M_CELL *)malloc(sizeof(M_CELL));
      if (tmp == NULL) {
        perror("Failed to allocate cell structure inside matrix");
        free_matrix(m);
        return NULL;
      }

      curr->down = tmp;
      tmp->up = curr;

      if (j == 0) {
        tmp->left = NULL;
      } else {
        tmp->left = curr->left->down;
        tmp->left->right = tmp;
      }
      tmp->right = NULL;
      tmp->down = NULL;

      tmp->val = rand() % MAX_RAND_VALUE;
      max_val = max_val > tmp->val ? max_val : tmp->val;

      curr = curr->right;
    }
    curr = prev_row->down;
  }

  return m;
}

F_MATRIX *init_matrix() {
  F_MATRIX *m = (F_MATRIX *)malloc(sizeof(F_MATRIX));
  if (m == NULL) {
    perror("Failed to allocate matrix struct");
    return NULL;
  }

  m->t = (M_CELL *)malloc(sizeof(M_CELL));
  if (m->t == NULL) {
    perror("failed to allocate cell structure");
    return NULL;
  };

  m->col = 0;
  m->row = 0;

  return m;
}
