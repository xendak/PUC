import java.util.Random;
import java.util.Scanner;

public class RandomLetters {
    public static void main(String[] args) {
        Random gerador = new Random();
        gerador.setSeed(4);

        Scanner scanner = new Scanner(System.in);
        String line;
        
        while (!(line = scanner.nextLine()).equals("FIM")) {
            char c1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
            char c2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
            System.out.println(substituteLetters(line, c1, c2));
        }
        
        scanner.close();
    }

    public static String substituteLetters(String str, char c1, char c2) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            char curr = str.charAt(i);
            if (curr == c1) {
                result.append(c2);
            } else {
                result.append(curr);
            }
        }
        return result.toString();
    }
}

