import java.util.Scanner;
import java.util.Arrays;

public class AnagramChecker {

    // Method to check if two strings are anagrams
    public static boolean checkAnagrams(String str1, String str2) {
        str1 = str1.replace(" ", "");
        str2 = str2.replace(" ", "");
        
        //if (str1.length() != str2.length()) {
        //    return false;
        //}

        char[] charArray1 = str1.toCharArray();
        char[] charArray2 = str2.toCharArray();
        Arrays.sort(charArray1);
        Arrays.sort(charArray2);
        
        return Arrays.equals(charArray1, charArray2);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            String[] words = line.split("-");
            String str1 = words[0].trim();  // Trim spaces around the words
            String str2 = words[1].trim();

            boolean result = checkAnagrams(str1, str2);
            System.out.println(result ? "SIM" : "NAO");
        }

        scanner.close();
    }
}

