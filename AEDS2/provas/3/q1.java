import java.util.Scanner;


public class q1 {
  private static int MAX = 500;


  public static void printAnswer(int[] rankings, int count) {
    for (int i = 0; i < rankings.length; i++)
      if (rankings[i] == count) System.out.printf("%d ", i);
    System.out.println("");
  }
  
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int n = input.nextInt();
    int m = input.nextInt();
    input.nextLine(); // skip line.

    
    do {
      // there is no rank 0, and java initializes arrays to 0 by default;
      int[] rankings = new int[MAX]; 
      int first = 0;
      int second = 0;

      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          int temp = input.nextInt();
          rankings[temp % MAX]++;
          // System.out.printf("n: %d\ttemp%%MAX: %d\trankings: %d\tfirst, second: %d,%d\n", temp, temp%MAX, rankings[temp % MAX], first, second);
          if (rankings[temp % MAX] > first)
            first = rankings[temp % MAX];
          else if (first > rankings[temp % MAX] && rankings[temp % MAX] > second)
            second = rankings[temp % MAX];
        }
        input.nextLine();
      }

      printAnswer(rankings, second);

      n = input.nextInt();
      m = input.nextInt();
      input.nextLine(); // skip line.
    } while (n > 0 && m > 0);
    input.close();
  }
}
