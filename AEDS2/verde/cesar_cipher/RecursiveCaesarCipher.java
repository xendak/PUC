import java.util.Scanner;

public class RecursiveCaesarCipher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String line = "start";
        int end = 0;
        do {
            line = scanner.nextLine();
            if (!line.equals("FIM")) {
                encrypt(line, 3, 0, line.length());
                System.out.println();
            } else {
                end = 1;
            }
        } while (scanner.hasNextLine() && end == 0);
        
        scanner.close();
    }

    public static void encrypt(String str, int shift, int i, int len) {
        if (i < len) {
            if (str.charAt(i) < 128) {
                System.out.printf("%c", (char) (str.charAt(i) + shift) % 128);
            } else {
                System.out.printf("%c", (char) (str.charAt(i)));
            }
            encrypt(str, shift, i+1, len);
        }
    }
}

