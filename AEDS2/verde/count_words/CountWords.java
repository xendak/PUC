import java.util.Scanner;

public class CountWords {

    public static int countWords(String str) {
        int words = 1;
        for (int i = 0; i < str.length(); i++) {
            words = str.charAt(i) == ' ' ? words + 1 : words;
        }
        
        return words;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            int wordCount = countWords(line);
            System.out.println(wordCount);
        }

        scanner.close();
    }
}

