#include <stdio.h>

#define MAX 10

int main() {
  int n;
  int k;
  if (scanf("%d %d", &n, &k) != 2)
    return -1;
  do {
    int questions[MAX] = {0};
    // o(1) approach, we only read from input and we have our answer already.
    // or we could do o(n) and iterate thourgh questions to grab our answer;
    int checked[MAX] = {0};

    int ans = 0;
    int temp;

    for (int i = 0; i < n; i++) {
      if (scanf("%d", &temp) != 1) {
        perror("couldn't read input number");
        return -1;
      }
      questions[temp % MAX]++;
      if (checked[temp % MAX] == 0 && questions[temp % MAX] >= k) {
        ans++;
        checked[temp % MAX]++;
      }
    }

    // for(int i = 0; i < MAX; i++) ans = questions[i] >= k ? ans+1 : ans;
    printf("%d\n", ans);

    if (scanf("%d %d", &n, &k) != 2)
      return -1;
  } while (n > 0 && k > 0);

  return 0;
}
