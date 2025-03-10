import java.util.Scanner;

public class ValidatePassword {
    public static boolean validatePassword(String pw) {
        boolean hasLength  = pw.length() > 8;
        boolean hasUpper   = false;
        boolean hasLower   = false;
        boolean hasNumber  = false;
        boolean hasSpecial = false;

        for (char c : pw.toCharArray()) {
            if (Character.isUpperCase(c)) { hasUpper = true; }
            else if (Character.isLowerCase(c)) { hasLower = true; }
            else if (Character.isDigit(c)) { hasNumber = true; }
            else { hasSpecial = true; }
        }



        return hasLength && hasUpper && hasLower && hasNumber && hasSpecial;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            boolean result = validatePassword(line);
            System.out.println(result ? "SIM" : "NÃO");
        }
        scanner.close();
    }
}
