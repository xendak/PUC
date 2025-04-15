#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096

typedef struct {
  int day;
  int month;
  int year;
} DATE;

typedef struct {
  char* show_id;
  char* type;
  char* title;
  char* director;
  char** cast;
  int cast_size;
  char* country;
  DATE date_added;
  int release_year;
  char* rating;
  char* duration;
  char** listed_in;
  int listed_in_size;
  char* description;
} SHOW;

void swap(char** arr, int i, int j) {
  char* temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

int median_of_three(char** arr, int a, int b, int c) {
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

int partition(char** arr, int left, int right) {
  int mid = left + (right - left) / 2;
  int pivot_idx = median_of_three(arr, left, mid, right);
  char* pivot = arr[pivot_idx];
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

void quicksort(char** arr, int left, int right) {
  if (left >= right)
    return;
  int pivot = partition(arr, left, right);
  quicksort(arr, left, pivot - 1);
  quicksort(arr, pivot + 1, right);
}

int parse_month(const char* month) {
  if (strlen(month) < 3)
    return 0;
  const char *months[] = {"January",   "February", "March",    "April",
                          "May",       "June",     "July",     "August",
                          "September", "October",  "November", "December"};
  for (int i = 0; i < 12; i++)
    if (strncmp(month, months[i], 3) == 0)
      return i + 1;
  return 0;
}

// an idea for future speed ups.
// int parse_month(const char *month) {
//   if (strlen(month) < 3)
//     return 0;

//   switch (month[0]) {
//   case 'J':
//     if (month[1] == 'a')
//       return 1; // January
//     if (month[2] == 'n')
//       return 6; // June
//     return 7;   // July
//   case 'F':
//     return 2; // February
//   case 'M':
//     if (month[2] == 'r')
//       return 3; // March
//     return 5;   // May
//   case 'A':
//     if (month[1] == 'p')
//       return 4; // April
//     return 8;   // August
//   case 'S':
//     return 9; // September
//   case 'O':
//     return 10; // October
//   case 'N':
//     return 11; // November
//   case 'D':
//     return 12; // December
//   default:
//     return 0;
//   }
// }

DATE parse_date(const char* date_str) {
  DATE result;
  if (strlen(date_str) < 6) {
    result.day = 0;
    result.month = 0;
    result.year = 0;
  } else {
    char month[20], day[3], year[5];
    sscanf(date_str, "%s %[^,], %s", month, day, year);
    result.month = parse_month(month);
    result.day = atoi(day);
    result.year = atoi(year);
  }
  return result;
}

// moving away from string method for now.
// void parse_date(const char *date_str, char *output) {
//   if (strcmp(date_str, "NaN") == 0) {
//     strcpy(output, "NaN");
//     return;
//   }

//   char month[20], day[3], year[5];
//   sscanf(date_str, "%s %[^,], %s", month, day, year);
//   int m = parse_month(month);
//   sprintf(output, "%02d/%02d/%s", m, atoi(day), year);
// }

void trim_spaces(char* str) {
  // Trim leading spaces
  while (*str == ' ')
    str++;

  // Trim trailing spaces
  char* end = str + strlen(str) - 1;
  while (end > str && *end == ' ')
    end--;
  *(end + 1) = '\0';
}

int count_commas(char *str) {
  int i = 0, c = 0;
  while (str[i]) {
    if (str[i] == ',')
      c++;
    i++;
  }
  return c;
}

char* remove_all_quotes(char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = malloc(len + 1);    
    if (!result) return NULL;    

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '"') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';    
    return result;
}

char* process_field_content(char* content, int field_num) {
    char* result;
    
    result = remove_all_quotes(content);
    
    if (!result || strlen(result) == 0) {
        free(result);
        result = strdup("NaN");
    }
    
    return result;
}

SHOW parse_line(char *line) {
  SHOW show = {0};
  char *token, *rest = line;
  int field = 0;
  int in_quotes = 0;
  char buffer[MAX_LINE_LENGTH];
  char* ptr = buffer;

  while (*rest) {
    if (*rest == '"')
      in_quotes = !in_quotes;
    if (*rest == ',' && !in_quotes) {
      *ptr = '\0';
      ptr = buffer;
      char* content = process_field_content(buffer, field);

      switch (field) {
      case 0:
        show.show_id = content;
        break;
      case 1:
        show.type = content;
        break;
      case 2:
        show.title = content;
        break;
      case 3:
        show.director = content;
        break;
      case 4: {
        // Parse cast
        int comma = count_commas(content) + 1;
        char* cast = strtok(content, ",");
        int count = 0;
        char** arr = malloc(comma * sizeof(char *));
        while (cast) {
          if (cast[0] == ' ')
            cast++;
          arr[count++] = strdup(cast);
          cast = strtok(NULL, ",");
        }
        quicksort(arr, 0, count - 1);
        show.cast = arr;
        show.cast_size = count;
        free(content);
        break;
      }
      case 5:
        show.country = content;
        break;
      case 6:
        show.date_added = parse_date(content);
        free(content);
        break;
      case 7:
        show.release_year = atoi(content);
        free(content);
        break;
      case 8:
        show.rating = content;
        break;
      case 9:
        show.duration = content;
        break;
      case 10: {
        // Parse listed_in
        int comma = count_commas(content) + 1;
        char* genre = strtok(content, ",");
        int count = 0;
        char** arr = malloc(comma * sizeof(char *));
        while (genre) {
          if (genre[0] == ' ')
            genre++;
          arr[count++] = strdup(genre);
          genre = strtok(NULL, ",");
        }
        quicksort(arr, 0, count - 1);
        show.listed_in = arr;
        show.listed_in_size = count;
        free(content);
        break;
      }
      case 11:
        show.description = content;
        break;
      }
      field++;
      rest++;
      memset(buffer, 0, sizeof(buffer));
      ptr = buffer;
      continue;
    }
    *ptr++ = *rest++;
  }
  return show;
}

int count_lines(const char* filename) {
  int c = 0;
  FILE* fp = fopen(filename, "rt");
  char line[MAX_LINE_LENGTH];
  while (!feof(fp)) {
    if (fgets(line, MAX_LINE_LENGTH, fp))
      c++;
  }
  fclose(fp);
  return c;
}

SHOW* parse_file(const char* filename, int count) {
  FILE* fp = fopen(filename, "r");
  if (!fp)
    return NULL;

  char line[MAX_LINE_LENGTH];
  SHOW* shows = malloc(count * sizeof(SHOW));
  int i = 0;

  fgets(line, sizeof(line), fp); // Skip header
  while (fgets(line, sizeof(line), fp)) {
    shows[i++] = parse_line(line);
  }
  fclose(fp);
  return shows;
}

char* month_name(int month) {
  char* months[] = {"January",   "February", "March",    "April",
                    "May",       "June",     "July",     "August",
                    "September", "October",  "November", "December"};

  return months[month - 1];
}

char* date_to_string(DATE d) {
  if (d.day <= 0)
    return strdup("NaN");

  size_t size = 50;
  char* buffer = malloc(size);
  if (!buffer)
    return NULL;
  int pos = 0;

  pos += snprintf(buffer + pos, size - pos, "%s %d, %d", month_name(d.month),
                  d.day, d.year);
  return buffer;
}

char* show_to_string(SHOW s) {
  size_t size = MAX_LINE_LENGTH;
  char* buffer = malloc(size);
  if (!buffer)
    return NULL;
  int pos = 0;

  // had to fix this to fit VERDE, original order is title after type.
  pos += snprintf(buffer + pos, size - pos, "=> %s ## %s ## %s ## %s ## [",
                  s.show_id, s.title, s.type, s.director);

  // Cast members
  for (int i = 0; i < s.cast_size; i++) {
    if (i > 0)
      pos += snprintf(buffer + pos, size - pos, ", ");
    pos += snprintf(buffer + pos, size - pos, "%s", s.cast[i]);
  }

  char* date_str = date_to_string(s.date_added);
  pos +=
      snprintf(buffer + pos, size - pos, "] ## %s ## %s ## %d ## %s ## %s ## [",
               s.country, date_str, s.release_year,
               s.rating, s.duration);

  free(date_str);
  
  // Listed_in members
  for (int i = 0; i < s.listed_in_size; i++) {
    if (i > 0)
      pos += snprintf(buffer + pos, size - pos, ", ");
    pos += snprintf(buffer + pos, size - pos, "%s", s.listed_in[i]);
  }

  pos += snprintf(buffer + pos, size - pos, "] ##");

  return buffer;
}

void free_show(SHOW *s) {
  if (!s)
    return;

  free(s->show_id);
  free(s->type);
  free(s->title);
  free(s->director);

  for (int i = 0; i < s->cast_size; i++) {
    free(s->cast[i]);
  }
  free(s->cast);

  free(s->country);
  free(s->rating);
  free(s->duration);

  for (int i = 0; i < s->listed_in_size; i++) {
    free(s->listed_in[i]);
  }
  free(s->listed_in);

  free(s->description);
}

int main() {
  const char* filename = "/tmp/disneyplus.csv";
  int show_count = count_lines(filename) - 1;
  SHOW* shows = parse_file(filename, show_count);

  char input[20];
  do {
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int id = atoi(input + 1);
    if (id > 0 && id <= show_count) {
      char* line = show_to_string(shows[id - 1]);
      printf("%s\n", line);
      free(line);
    }
  } while (strcmp(input, "FIM") != 0);

  // printf("\n%s\n", show_to_string(shows[85]));
  for (int i = 0; i < show_count; i++) {
    free_show(&shows[i]);
  }
  free(shows);
  return 0;
}
