#include <stdio.h>
#include <locale.h>
#include <sys/types.h>
#include <string.h>

#define MAX 1000

int mystr_cmp(char*, char*);
int mystr_len(char*);
int mychar_cmp(char, char);
char mychar_to_lower(char);

#define SWP(x,y) ((x)^=(y), (y)^=(x), (x)^=(y))
void strrev(char *p);
void strrev_utf8(char *p);

void check_palindrome(char*);


int main() {

    setlocale(LC_ALL, "pt_BR_utf8");
    char line[MAX];
    scanf("%[^\n]", line);

    while (mystr_cmp(line, "FIM")) {
        /*printf("%s\t", line);*/
        check_palindrome(line);
        scanf(" %[^\n]", line);
    }
}

int mychar_cmp(char a, char b) {
    return (mychar_to_lower(a) - 'A') - (mychar_to_lower(b) - 'A'); 
}

char mychar_to_lower(char c) {
    char r = c;
    if (c >= 'A' && c <= 'Z')
       r ^= 'a' - 'A'; 
    return r;
}

int mystr_cmp(char* a, char* b) {
    int asz = mystr_len(a);
    int bsz = mystr_len(b);
    int min = asz >= bsz ? bsz : asz;
    int val = asz - bsz;

    int i = 0;
    do  {
        val = mychar_cmp(a[i], b[i]);
        i++;
    } while (i < min && a[i] == b[i]);

    return val;
}

int mystr_len(char* s) {
    int sz = 0;
    while(s[sz++])
        ;;
    return sz;
}

int is_even(int n) {
    int c[2] = {0, 1};
    return c[n & 1];
}


void strrev(char *p)
{
  char *q = p;
  while(q && *q) ++q; /* find eos */
  for(--q; p < q; ++p, --q) SWP(*p, *q);
}

void strrev_utf8(char *p)
{
  char *q = p;
  strrev(p); /* call base case */

  /* Ok, now fix bass-ackwards UTF chars. */
  while(q && *q) ++q; /* find eos */
  while(p < --q)
    switch( (*q & 0xF0) >> 4 ) {
    case 0xF: /* U+010000-U+10FFFF: four bytes. */
      SWP(*(q-0), *(q-3));
      SWP(*(q-1), *(q-2));
      q -= 3;
      break;
    case 0xE: /* U+000800-U+00FFFF: three bytes. */
      SWP(*(q-0), *(q-2));
      q -= 2;
      break;
    case 0xC: /* fall-through */
    case 0xD: /* U+000080-U+0007FF: two bytes. */
      SWP(*(q-0), *(q-1));
      q--;
      break;
    }
}
void check_palindrome(char* s) {
    int sz = mystr_len(s) - 2;
    sz = is_even(sz) == 0 ? sz : sz + 1;
    int i = 0;
    int pal = 1;
    while (i < (int)(sz/2) && pal) {
        if (s[i] != s[sz-i]) { pal = 0; }
        i++;
    }

    sz = strlen(s);
    char* rev; 
    memcpy(rev, s, sizeof(s));


    printf("\n%s\n", rev);
    char* palindrome[2] = {"NAO", "SIM"};
    printf("%s\n", palindrome[pal]);
}

