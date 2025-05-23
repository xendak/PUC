import java.util.Scanner;
public class CheckString {

    public static boolean[] validateString(String str) {
        boolean[] res = { true, true, true, true };

        res[0] = myIsVowel(str);
        res[1] = myIsConsonant(str);
        res[2] = myIsDigit(str);
        res[3] = myIsNumber(str);

        return res;
    }

    public static boolean myIsConsonant(String str) {
        boolean res = false;
        String cts = "bcdfghjklmnpqrstvwxyzçBCDFGHJKLMNPQRSTVWXYZÇ";
        for (int i = 0; i < str.length(); i++) {
            boolean aux = false;
            if (res) {
                for (int j = 0; j < cts.length(); j++) {
                    if (str.charAt(i) == cts.charAt(j)) {
                        aux = true;
                    }
                }
            }
            if (aux == false) {
                // we went through everything and didnt find a match for
                // this character, therefore it can't be all consonant.
                // return / break here would also work.
                res = false;
            }
        }
        return res;
    }

    public static boolean myIsVowel(String str) {
        boolean res = true;
        String vws = "aeiouAEIOU";//ÁÉíáéÍóÓàÀêÊãÃÂÔÕâôõ";
        for (int i = 0; i < str.length(); i++) {
            boolean aux = false;
            if (res) {
                for (int j = 0; j < vws.length(); j++) {
                    if (str.charAt(i) == vws.charAt(j)) {
                        aux = true;
                    }
                }
            }
            if (aux == false) {
                // we went through everything and didnt find a match for
                // this character, therefore it can't be all consonant.
                // return / break here would also work.
                res = false;
            }
        }
        return res;
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

