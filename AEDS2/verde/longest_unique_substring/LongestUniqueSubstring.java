import java.util.Scanner;

public class LongestUniqueSubstring {
    private static int longestUniqueSubstring(String s) {
        boolean[] seen = new boolean[128]; // For ASCII characters
        int maxLength = 0;
        int start = 0;

        for (int i = 0; i < s.length(); i++) {
            char current = s.charAt(i);

            // basically doing seen[C] where C gets replaced by its 'C'
            // which is somewhere between 0 and 127
            // if seen[96] > 0 , means we saw it once.
            // need to purge, so we go through the array and delete it.
            while (seen[current]) {
                seen[s.charAt(start)] = false;
                start++;
            }

            // Mark current character as seen
            seen[current] = true;
            maxLength = Math.max(maxLength, i - start + 1);
        }

        return maxLength;
    }

    public static void main (String[] args) {
        Scanner scanner = new Scanner(System.in);
        String line;
        while (!(line = scanner.nextLine()).equals("FIM")) {
            System.out.println(longestUniqueSubstring(line));
        }
        scanner.close();
    }
}
