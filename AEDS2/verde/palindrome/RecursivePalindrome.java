import java.util.Scanner;

public class RecursivePalindrome {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            System.out.println(isPalindrome(line) ? "SIM" : "NAO");
        }
        scanner.close();
    }

    public static boolean recIsPalindrome(String s, int i, int sz, boolean palindrome) {
        if (sz == 0) { return false; }
        else if (s.charAt(i) != s.charAt(sz - i)) { return false; }
        else if ((int)(sz/2) == i) { return palindrome; }
        recIsPalindrome(s, i+1, sz, palindrome);
    }

    public static boolean isPalindrome(String s) {
        boolean res = true;
        res = recIsPalindrome(s, 0, s.length() - 1, res);
        return res;
    }
}
