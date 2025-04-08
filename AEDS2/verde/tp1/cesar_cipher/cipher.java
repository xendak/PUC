import java.util.Scanner;

public class CaesarCipher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String line = "start";
        int end = 0;
        do {
            line = scanner.nextLine();
            if (!line.equals("FIM")) {
                System.out.println(encrypt(line, 3));
            } else {
                end = 1;
            }
        } while (scanner.hasNextLine() && end == 0);
        
        scanner.close();
    }

    public static String encrypt(String str, int shift) {
        StringBuilder result = new StringBuilder();
        char[] arr = str.toCharArray();
        for(int i = 0; i < arr.length; i++){
            if (arr[i] < 128) {
            result.append((char) ((arr[i] + shift) % 128));
        } else {
            result.append(arr[i]);
        }
        }
        return result.toString();
    }
}

