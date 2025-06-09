#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 4096
#define MAX_SIZE 10000

typedef enum {
  false,
  true,
} bool;

typedef struct {
  int day;
  int month;
  int year;
} DATE;

typedef struct {
  char *show_id;
  char *type;
  char *title;
  char *director;
  char **cast;
  int cast_size;
  char *country;
  DATE date_added;
  int release_year;
  char *rating;
  char *duration;
  char **listed_in;
  int listed_in_size;
  char *description;
} Show;

void swap(char **arr, int i, int j) {
  char *temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

int median_of_three(char **arr, int a, int b, int c) {
  if (strcmp(arr[a], arr[b]) > 0) {
    if (strcmp(arr[b], arr[c]) > 0)
      return b;
    else if (strcmp(arr[a], arr[c]) > 0)
      return c;
    else
      return a;
  } else {
    if (strcmp(arr[a], arr[c]) > 0)
      return a;
    else if (strcmp(arr[b], arr[c]) > 0)
      return c;
    else
      return b;
  }
}

int partition(char **arr, int left, int right) {
  int mid = left + (right - left) / 2;
  int pivot_idx = median_of_three(arr, left, mid, right);
  char *pivot = arr[pivot_idx];
  swap(arr, pivot_idx, right);

  int i = left - 1;
  int j = right;

  while (1) {
    do
      i++;
    while (i < right && strcmp(arr[i], pivot) < 0);
    do
      j--;
    while (j > left && strcmp(arr[j], pivot) > 0);
    if (i >= j)
      break;
    swap(arr, i, j);
  }
  swap(arr, i, right);
  return i;
}

void quicksort(char **arr, int left, int right) {
  if (left >= right)
    return;
  int pivot = partition(arr, left, right);
  quicksort(arr, left, pivot - 1);
  quicksort(arr, pivot + 1, right);
}

int parse_month(const char *month) {
  if (!month || strlen(month) < 3)
    return 0;
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  for (int i = 0; i < 12; i++)
    if (strncmp(month, months[i], 3) == 0)
      return i + 1;
  return 0;
}

DATE parse_date(const char *date_str) {
  DATE result = {0, 0, 0};
  if (!date_str || strlen(date_str) < 6) {
    return result;
  }

  char month[20], day[10], year[10];
  if (sscanf(date_str, "%19s %9[^,], %9s", month, day, year) == 3) {
    result.month = parse_month(month);
    result.day = atoi(day);
    result.year = atoi(year);
  }
  return result;
}

char *safe_strdup(const char *str) {
  if (!str)
    return strdup("NaN");
  char *result = strdup(str);
  return result ? result : strdup("NaN");
}

char *remove_quotes_and_trim(const char *str) {
  if (!str)
    return safe_strdup("NaN");

  size_t len = strlen(str);
  if (len == 0)
    return safe_strdup("NaN");

  const char *start = str;
  while (*start && (*start == '"' || *start == ' '))
    start++;

  const char *end = str + len - 1;
  while (end > start && (*end == '"' || *end == ' '))
    end--;

  size_t new_len = end - start + 1;
  if (new_len == 0)
    return safe_strdup("NaN");

  char *result = malloc(new_len + 1);
  if (!result)
    return safe_strdup("NaN");

  strncpy(result, start, new_len);
  result[new_len] = '\0';

  return result;
}

char **parse_comma_separated(const char *str, int *count) {
  *count = 0;
  if (!str || strlen(str) == 0) {
    char **result = malloc(sizeof(char *));
    result[0] = safe_strdup("NaN");
    *count = 1;
    return result;
  }

  int comma_count = 0;
  for (const char *p = str; *p; p++) {
    if (*p == ',')
      comma_count++;
  }
  int max_items = comma_count + 1;

  char **items = malloc(max_items * sizeof(char *));
  if (!items)
    return NULL;

  char *str_copy = strdup(str);
  if (!str_copy) {
    free(items);
    return NULL;
  }

  char *token = strtok(str_copy, ",");
  while (token && *count < max_items) {
    items[*count] = remove_quotes_and_trim(token);
    (*count)++;
    token = strtok(NULL, ",");
  }

  if (*count > 1) {
    quicksort(items, 0, *count - 1);
  }

  free(str_copy);
  return items;
}

Show parse_line(char *line) {
  Show show = {0};
  char *fields[12] = {0};
  int field_count = 0;

  char *current = line;
  char buffer[MAX_LINE_LENGTH];
  int buf_pos = 0;
  int in_quotes = 0;

  while (*current && field_count < 12) {
    if (*current == '"') {
      in_quotes = !in_quotes;
    } else if (*current == ',' && !in_quotes) {
      buffer[buf_pos] = '\0';
      fields[field_count] = strdup(buffer);
      field_count++;
      buf_pos = 0;
    } else {
      buffer[buf_pos++] = *current;
    }
    current++;
  }

  if (buf_pos > 0 && field_count < 12) {
    buffer[buf_pos] = '\0';
    fields[field_count] = strdup(buffer);
    field_count++;
  }

  if (field_count >= 12) {
    show.show_id = remove_quotes_and_trim(fields[0]);
    show.type = remove_quotes_and_trim(fields[1]);
    show.title = remove_quotes_and_trim(fields[2]);
    show.director = remove_quotes_and_trim(fields[3]);

    show.cast = parse_comma_separated(fields[4], &show.cast_size);

    show.country = remove_quotes_and_trim(fields[5]);
    show.date_added = parse_date(fields[6]);
    show.release_year = atoi(fields[7]);
    show.rating = remove_quotes_and_trim(fields[8]);
    show.duration = remove_quotes_and_trim(fields[9]);

    show.listed_in = parse_comma_separated(fields[10], &show.listed_in_size);

    show.description = remove_quotes_and_trim(fields[11]);
  }

  for (int i = 0; i < field_count; i++) {
    free(fields[i]);
  }

  return show;
}

int count_lines(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return 0;

  int count = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), fp)) {
    count++;
  }
  fclose(fp);
  return count;
}

Show *parse_file(const char *filename, int *show_count) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    *show_count = 0;
    return NULL;
  }

  int total_lines = count_lines(filename);
  if (total_lines <= 1) {
    fclose(fp);
    *show_count = 0;
    return NULL;
  }

  rewind(fp);
  *show_count = total_lines - 1;
  Show *shows = malloc(*show_count * sizeof(Show));
  if (!shows) {
    fclose(fp);
    *show_count = 0;
    return NULL;
  }

  char line[MAX_LINE_LENGTH];
  fgets(line, sizeof(line), fp);

  int i = 0;
  while (fgets(line, sizeof(line), fp) && i < *show_count) {
    shows[i++] = parse_line(line);
  }

  fclose(fp);
  return shows;
}

char *month_name(int month) {
  static char *months[] = {"January",   "February", "March",    "April",
                           "May",       "June",     "July",     "August",
                           "September", "October",  "November", "December"};
  if (month < 1 || month > 12)
    return "Invalid";
  return months[month - 1];
}

char *date_to_string(DATE d) {
  if (d.day <= 0 || d.month <= 0 || d.year <= 0)
    return safe_strdup("NaN");

  char *buffer = malloc(50);
  if (!buffer)
    return safe_strdup("NaN");

  snprintf(buffer, 50, "%s %d, %d", month_name(d.month), d.day, d.year);
  return buffer;
}

char *show_to_string(Show s) {
  size_t size = MAX_LINE_LENGTH * 2;
  char *buffer = malloc(size);
  if (!buffer)
    return NULL;

  int pos = 0;
  pos += snprintf(buffer + pos, size - pos, "=> %s ## %s ## %s ## %s ## [",
                  s.show_id ? s.show_id : "NaN", s.title ? s.title : "NaN",
                  s.type ? s.type : "NaN", s.director ? s.director : "NaN");

  for (int i = 0; i < s.cast_size && pos < size - 100; i++) {
    if (i > 0)
      pos += snprintf(buffer + pos, size - pos, ", ");
    pos +=
        snprintf(buffer + pos, size - pos, "%s", s.cast[i] ? s.cast[i] : "NaN");
  }

  char *date_str = date_to_string(s.date_added);
  pos +=
      snprintf(buffer + pos, size - pos, "] ## %s ## %s ## %d ## %s ## %s ## [",
               s.country ? s.country : "NaN", date_str, s.release_year,
               s.rating ? s.rating : "NaN", s.duration ? s.duration : "NaN");
  free(date_str);

  for (int i = 0; i < s.listed_in_size && pos < size - 100; i++) {
    if (i > 0)
      pos += snprintf(buffer + pos, size - pos, ", ");
    pos += snprintf(buffer + pos, size - pos, "%s",
                    s.listed_in[i] ? s.listed_in[i] : "NaN");
  }

  pos += snprintf(buffer + pos, size - pos, "] ##");
  return buffer;
}

void free_show(Show *s) {
  if (!s)
    return;
  if (s->show_id)
    free(s->show_id);
  if (s->type)
    free(s->type);
  if (s->title)
    free(s->title);
  if (s->director)
    free(s->director);
  if (s->cast) {
    for (int i = 0; i < s->cast_size; i++) {
      if (s->cast[i])
        free(s->cast[i]);
    }
    free(s->cast);
  }
  if (s->country)
    free(s->country);
  if (s->rating)
    free(s->rating);
  if (s->duration)
    free(s->duration);
  if (s->listed_in) {
    for (int i = 0; i < s->listed_in_size; i++) {
      if (s->listed_in[i])
        free(s->listed_in[i]);
    }
    free(s->listed_in);
  }
  if (s->description)
    free(s->description);
}

Show copy_show(const Show *original) {
  Show copy = {0};

  copy.show_id = safe_strdup(original->show_id);
  copy.type = safe_strdup(original->type);
  copy.title = safe_strdup(original->title);
  copy.director = safe_strdup(original->director);
  copy.country = safe_strdup(original->country);
  copy.rating = safe_strdup(original->rating);
  copy.duration = safe_strdup(original->duration);
  copy.description = safe_strdup(original->description);

  if (original->cast && original->cast_size > 0) {
    copy.cast = malloc(original->cast_size * sizeof(char *));
    copy.cast_size = original->cast_size;
    for (int i = 0; i < original->cast_size; i++) {
      copy.cast[i] = safe_strdup(original->cast[i]);
    }
  } else {
    copy.cast = NULL;
    copy.cast_size = 0;
  }

  if (original->listed_in && original->listed_in_size > 0) {
    copy.listed_in = malloc(original->listed_in_size * sizeof(char *));
    copy.listed_in_size = original->listed_in_size;
    for (int i = 0; i < original->listed_in_size; i++) {
      copy.listed_in[i] = safe_strdup(original->listed_in[i]);
    }
  } else {
    copy.listed_in = NULL;
    copy.listed_in_size = 0;
  }

  copy.date_added.day = original->date_added.day;
  copy.date_added.month = original->date_added.month;
  copy.date_added.year = original->date_added.year;
  copy.release_year = original->release_year;

  return copy;
}

typedef struct Node {
  Show data;
  struct Node *prev;
  struct Node *next;
} Node, *pNode;

typedef struct {
  pNode head;
  pNode tail;
  int len;
} List;

List *init_list() {
  List *l = (List *)malloc(sizeof(List));
  if (l == NULL) {
    return NULL;
  }
  l->head = NULL;
  l->tail = NULL;
  l->len = 0;
  return l;
}

bool insert_at(List *l, int pos, Show s) {
  if (pos < 0 || pos > l->len)
    return false;

  pNode to_add = (pNode)malloc(sizeof(Node));
  if (to_add == NULL)
    return false;

  to_add->data = s;

  pNode curr = l->head;
  for (int i = 0; i < pos; i++) {
    curr = curr->next;
  }
  to_add->next = curr;
  to_add->prev = curr->prev;
  curr->prev->next = to_add;
  curr->prev = to_add;

  l->len++;
  return true;
}

bool insert_at_start(List *l, Show s) {
  pNode to_add = (pNode)malloc(sizeof(Node));
  if (to_add == NULL)
    return false;

  to_add->data = s;

  to_add->next = l->head;
  to_add->prev = NULL;

  if (l->head != NULL)
    l->head->prev = to_add;

  l->head = to_add;
  if (l->tail == NULL)
    l->tail = to_add;

  l->len++;
  return true;
}

bool insert_at_end(List *l, Show s) {
  pNode to_add = (pNode)malloc(sizeof(Node));
  if (to_add == NULL)
    return false;

  to_add->data = s;

  to_add->next = NULL;
  to_add->prev = l->tail;

  if (l->tail != NULL)
    l->tail->next = to_add;

  l->tail = to_add;

  if (l->head == NULL)
    l->head = to_add;

  l->len++;
  return true;
}

Show remove_at(List *l, int pos) {
  Show removed_show = {0};
  if (pos < 0 || pos >= l->len || l->head == NULL)
    return removed_show;

  pNode to_remove;
  if (pos == 0) {
    to_remove = l->head;
    l->head = to_remove->next;
    if (l->head != NULL) {
      l->head->prev = NULL;
    } else {
      l->tail = NULL;
    }
  } else if (pos == l->len - 1) {
    to_remove = l->tail;
    l->tail = to_remove->prev;
    if (l->tail != NULL) {
      l->tail->next = NULL;
    } else {
      l->head = NULL;
    }
  } else {
    pNode curr = l->head;
    for (int i = 0; i < pos; i++) {
      curr = curr->next;
    }
    to_remove = curr;
    to_remove->prev->next = to_remove->next;
    to_remove->next->prev = to_remove->prev;
  }

  removed_show = to_remove->data;
  free(to_remove);
  l->len--;
  return removed_show;
}

Show remove_at_start(List *l) { return remove_at(l, 0); }

Show remove_at_end(List *l) { return remove_at(l, l->len - 1); }

void print_list(List *l) {
  pNode curr = l->head;
  while (curr != NULL) {
    char *s = show_to_string(curr->data);
    printf("%s\n", s);
    free(s);
    curr = curr->next;
  }
}

void free_list(List *l) {
  if (l == NULL)
    return;
  pNode curr = l->head;
  pNode next;
  while (curr != NULL) {
    next = curr->next;
    free_show(&curr->data);
    free(curr);
    curr = next;
  }
  free(l);
}

int count_spaces(char *line) {
  int spaces = 0;
  for (int i = 0; i < strlen(line); i++)
    if (line[i] == ' ')
      spaces++;
  return spaces;
}

int main() {
  const char *filename = "/tmp/disneyplus.csv";
  int show_count;
  Show *shows = parse_file(filename, &show_count);

  if (!shows) {
    printf("Error: Could not parse file or file is empty\n");
    return 1;
  }

  List *list = init_list();

  char input[20];

  do {
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int id = atoi(input + 1);
    if (id > 0 && id <= show_count) {
      insert_at_end(list, copy_show(&shows[id - 1]));
    }
  } while (strcmp(input, "FIM") != 0);

  int n;
  if (scanf("%d\n", &n) != 1)
    return 1;

  for (int i = 0; i < n; i++) {
    char op[3];
    int sid = -1;
    int pos = -1;

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    int spaces = count_spaces(input);

    if (spaces == 2) {
      sscanf(input, "%s %d s%d", op, &pos, &sid);
    } else if (spaces == 1) {
      if (input[0] == 'R') {
        sscanf(input, "%s %d", op, &pos);
      } else {
        sscanf(input, "%s s%d", op, &sid);
      }
    } else {
      sscanf(input, "%s", op);
    }

    Show curr = {0};
    switch (op[0]) {
    case 'I': {
      curr = copy_show(&shows[sid - 1]);
      if (pos >= 0)
        insert_at(list, pos, curr);
      else if (op[1] == 'I')
        insert_at_start(list, curr);
      else if (op[1] == 'F')
        insert_at_end(list, curr);
      break;
    }

    case 'R': {
      if (pos >= 0)
        curr = remove_at(list, pos);
      else if (op[1] == 'I')
        curr = remove_at_start(list);
      else if (op[1] == 'F')
        curr = remove_at_end(list);
      if (curr.show_id > 0) {
        printf("(R) %s\n", curr.title);
        free_show(&curr);
      }
      break;
    }
    }
  }

  print_list(list);
  free_list(list);

  for (int i = 0; i < show_count; i++) {
    free_show(&shows[i]);
  }
  free(shows);

  return 0;
}
