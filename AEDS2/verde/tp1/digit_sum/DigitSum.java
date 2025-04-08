import java.util.Scanner;

public class DigitSum {

    public static int sumDigits(int number) {
        int res = 0;
        
        while(number > 0) {
            res += number % 10;
            number = number / 10;
        }
        return res;
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
