import java.util.Scanner;

public class q1 {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int n = input.nextInt();
    int m = input.nextInt();
    input.nextLine(); // skip line.

    do {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          
        }
        input.nextLine();
      }
      int n = input.nextInt();
      int m = input.nextInt();
      input.nextLine(); // skip line.
    } while (n > 0 && m > 0);
    input.close();
  }
}
