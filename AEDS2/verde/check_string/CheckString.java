import java.util.Scanner;
public class CheckString {
    public static boolean vowelsOnly(String str) {
        String vws = "aeiouAEIOU";
        for (int i = 0; i < str.length(); i++) {
            if (vws.indexOf(str.charAt(i)) == -1) {
                return false;
            }
        }
        return true;
    }

    public static boolean consonantsOnly(String str) {
        String cts = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
        for (int i = 0; i < str.length(); i++) {
            if (cts.indexOf(str.charAt(i)) == -1) {
                return false;
            }
        }
        return true;
    }

    public static boolean checkInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static boolean checkFloat(String str) {
        try {
            str = str.replace(',', '.'); // apparently verde checks for commas??
            Double.parseDouble(str);
            return str.contains(".");
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            boolean x1 = vowelsOnly(line);
            boolean x2 = consonantsOnly(line);
            boolean x3 = checkInteger(line);
            boolean x4 = checkFloat(line);

            System.out.println(
                (x1 ? "SIM" : "NAO") + " " +
                (x2 ? "SIM" : "NAO") + " " +
                (x3 ? "SIM" : "NAO") + " " +
                (x4 ? "SIM" : "NAO")
            );
        }

        scanner.close();
    }
}

