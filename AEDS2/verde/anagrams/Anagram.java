import java.util.Scanner;
import java.util.Arrays;
import java.util.regex.Pattern;

public class AnagramChecker {
    public static boolean checkAnagrams(String str1, String str2) {
        str1 = str1.replaceAll("\\s", "").toLowerCase();
        str2 = str2.replaceAll("\\s", "").toLowerCase();
        String bStr, sStr;

        if (str1.length() >= str2.length()) {
            bStr = str1;
            sStr = str2;
        } else {
            bStr = str2;
            sStr = str1;

        }
        for (int i = 0; i < bStr.length(); i++) {
            //sStr = sStr.replaceFirst(Pattern.quote("" + bStr.charAt(i)), "");
            // this can be done without the pattern, but then we lose the control
            // over regex MATCHES like * or .
            sStr = sStr.replaceFirst("" + bStr.charAt(i), "");
        }
        
        return sStr.equals("");
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

