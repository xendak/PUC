import java.util.Scanner;

public class DigitSum {

    public static int sumDigits(int number) {
        if (number == 0) {
            return 0;
        }
        return number % 10 + sumDigits(number / 10);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            int number = Integer.parseInt(line);
            int result = sumDigits(number);
            System.out.println(result);
        }

        scanner.close();
    }
}
