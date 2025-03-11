import java.util.Scanner;
public class RecursiveCheckString {

    public static boolean[] validateString(String str) {
        boolean[] res = { true, true, true, true };

        res[0] = myIsVowel(str, 0);
        res[1] = myIsConsonant(str, 0);
        res[2] = myIsDigit(str, 0);
        res[3] = myIsNumber(str, 0);

        return res;
    }

    public static boolean myIsConsonant(String str, int i) {
        if (i >= str.length()) { return true; }
        return checkConsonant(str.charAt(i), 0) && myIsConsonant(str, i + 1);
    }

    public static boolean checkConsonant(Character c, int i) {
        String cts = "bcdfghjklmnpqrstvwxyzçBCDFGHJKLMNPQRSTVWXYZÇ";
        if (i >= cts.length()) { return false; }
        return (c == cts.charAt(i)) || checkConsonant(c, i + 1);
    }

    public static boolean myIsVowel(String str, int i) {
        if (i >= str.length()) { return true; }
        return checkVowel(str.charAt(i), 0) && myIsVowel(str, i + 1);
    }

    public static boolean checkVowel(Character c, int i) {
        String vws = "aeiouAEIOUÁÉíáéÍóÓàÀêÊãÃÂÔÕâôõ";
        if (i >= vws.length()) { return false; }
        return (c == vws.charAt(i)) || checkVowel(c, i + 1);
    }

    public static boolean myIsDigit(String str) {
        boolean res = true;
        for (int i = 0; i < str.length(); i++) {
            Character c = str.charAt(i);
            if (!((int) c >= 48 && (int) c <= 57)) {
                res = false;
            }
        }
        return res;
    }

    public static boolean myIsNumber(String str) {
        boolean res = true;
        boolean hasDot = false;
        for (int i = 0; i < str.length(); i++) {
            Character c = str.charAt(i);
            boolean isDigit = (int) c >= 48 && (int) c <= 57;
            boolean isCommaDot = (int) c == 44 || (int) c == 46;
            if (hasDot) { // comma and dot ascii
                //System.out.println(c + "\tCommaDot? " + isCommaDot + "\tisDigit? " + isDigit + "\thasDot? " + hasDot);
                if (!isDigit || isCommaDot) { // already saw a dot before, therefore we can't have anymore, therefore its not a number anymore.
                    res = false;
                }
            } else if (!isDigit || isCommaDot) {
                hasDot = true;
                continue;
            }
        }
        return res;

    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            boolean[] res = validateString(line);
            System.out.println(
                    (res[0] ? "SIM" : "NAO") + " " +
                    (res[1] ? "SIM" : "NAO") + " " +
                    (res[2] ? "SIM" : "NAO") + " " +
                    (res[3] ? "SIM" : "NAO")
                    );
        }

        scanner.close();
    }
}

