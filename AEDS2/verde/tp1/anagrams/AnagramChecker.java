import java.util.Scanner;
import java.util.Arrays;
import java.util.regex.Pattern;

public class AnagramChecker {
    public static boolean checkAnagrams(StringBuilder bStr, StringBuilder sStr) {
        boolean result = false;
        for (int i = 0; i < bStr.length(); i++) {
            //sStr = sStr.replaceFirst(Pattern.quote("" + bStr.charAt(i)), "");
            // this can be done without the pattern, but then we lose the control
            // over regex MATCHES like * or .
            boolean replaced = false;
            for (int j = 0; j < sStr.length(); j++) {
                Character c = sStr.charAt(j); // im not remaking this function, its basically
                Character d = bStr.charAt(i); // just Char - 'A' - 'Z'
                if (Character.toLowerCase(c) == Character.toLowerCase(d)) {
                    sStr.deleteCharAt(j);
                    break;
                }
            }
            //sStr = sStr.replaceFirst("" + bStr.charAt(i), "");
        }
        
        //System.out.println("str1: " + bStr + "\tstr2: " + sStr);
        return sStr.length() == 0;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            StringBuilder str1 = new StringBuilder();
            StringBuilder str2 = new StringBuilder();
            boolean seen = false;
            for (int i = 0; i <= line.length() - 1; i++) {
                Character c = line.charAt(i);
                if (c == ' ') continue;
                else if (c == '-') {
                    seen = true;
                }
                else if (seen) {
                    str2.append(c);
                } else {
                    str1.append(c);
                }
            }
            //System.out.println("str1: " + str1 + "\tstr2: " + str2);
            boolean result = str1.length() == str2.length() ? checkAnagrams(str1, str2) : false;

            System.out.println(result ? "SIM" : "NÃO");
        }

        scanner.close();
    }
}

