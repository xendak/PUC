import java.util.Scanner;

public class palindrome {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            System.out.println(isPalindrome(line) ? "SIM" : "NAO");
        }
        scanner.close();
    }

    public static boolean isPalindrome(String s) {
        boolean res = true;
        for (int i = 0; i < s.length() / 2; i++) {
            if (s.charAt(i) != s.charAt(s.length() - i - 1)) {
                res = false;
            }
        }
        return res;
    }
}
