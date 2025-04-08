import java.util.Scanner;

public class ValidatePassword {

    // ascii 0-127
    // 'A' - 'Z'
    // 'a' - 'z'
    // digit 0123456789
    // else special
    public static boolean myIsUpperCase(Character c) {
        return c >= 'A' && c <= 'Z';
    }
    public static boolean myIsLowerCase(Character c) {
        return c >= 'a' && c <= 'z';
    }
    public static boolean myIsDigit(Character c) {
        return (int) c >= 48 && (int) c <= 57;
    }

    public static boolean validatePassword(String pw) {
        boolean hasLength  = pw.length() > 8;
        boolean hasUpper   = false;
        boolean hasLower   = false;
        boolean hasNumber  = false;
        boolean hasSpecial = false;

        for (char c : pw.toCharArray()) {
            if (myIsUpperCase(c)) { hasUpper = true; }
            else if (myIsLowerCase(c)) { hasLower = true; }
            else if (myIsDigit(c)) { hasNumber = true; }
            else { hasSpecial = true; }
        }



        return hasLength && hasUpper && hasLower && hasNumber && hasSpecial;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            boolean result = validatePassword(line);
            System.out.println(result ? "SIM" : "NAO");
        }
        scanner.close();
    }
}
