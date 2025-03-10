import java.util.Scanner;

public class ReverseString {

    public static String inverterString(String str) {
        StringBuilder reversed = new StringBuilder();
        for (int i = str.length() - 1; i >= 0; i--) {
            reversed.append(str.charAt(i));
        }
        
        return reversed.toString();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String linha;
        while (!(linha = scanner.nextLine()).equals("FIM")) {
            String result = inverterString(linha);
            System.out.println(result);
        }

        scanner.close();
    }
}

