import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class WebPageAnalyzer {
    public static void main(String[] args) {
        try {
            List<String> inputLines = Files.readAllLines(Paths.get("in.txt"));
            List<String> outputLines = new ArrayList<>();

            int i = 0;
            while (i < inputLines.size()) {
                String name = inputLines.get(i);
                if (name.equals("FIM")) {
                    break;
                }
                i++;
                if (i >= inputLines.size()) break; // Prevent IndexOutOfBounds
                String url = inputLines.get(i);
                i++;

                String content = fetchWebContent(url);
                if (content == null) {
                    outputLines.add(formatOutput(new int[23], 0, 0, name));
                    continue;
                }

                int[] counts = countCharacters(content);
                int brCount = countOccurrences(content, "<br>");
                int tableCount = countOccurrences(content, "<table>");

                outputLines.add(formatOutput(counts, brCount, tableCount, name));
            }

            Files.write(Paths.get("out.txt"), outputLines);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String fetchWebContent(String urlString) throws IOException {
        URL url = new URL(urlString);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        conn.setConnectTimeout(5000);
        conn.setReadTimeout(5000);

        try {
            int responseCode = conn.getResponseCode();
            if (responseCode != HttpURLConnection.HTTP_OK) {
                return null;
            }
        } catch (IOException e) {
            return null;
        }

        StringBuilder content = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(
                new InputStreamReader(conn.getInputStream(), StandardCharsets.UTF_8))) {
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line);
            }
        }
        return content.toString();
    }

    private static int[] countCharacters(String content) {
        int[] counts = new int[23]; // Index 22 is for consonants

        int a = 0, e = 0, i = 0, o = 0, u = 0;
        int a_acute = 0, e_acute = 0, i_acute = 0, o_acute = 0, u_acute = 0;
        int a_grave = 0, e_grave = 0, i_grave = 0, o_grave = 0, u_grave = 0;
        int a_tilde = 0, o_tilde = 0;
        int a_circumflex = 0, e_circumflex = 0, i_circumflex = 0, o_circumflex = 0, u_circumflex = 0;
        int consonantCount = 0;

        for (char c : content.toCharArray()) {
            char cLower = Character.toLowerCase(c);
            switch (cLower) {
                case 'a': a++; break;
                case 'e': e++; break;
                case 'i': i++; break;
                case 'o': o++; break;
                case 'u': u++; break;
                case 'á': a_acute++; break;
                case 'é': e_acute++; break;
                case 'í': i_acute++; break;
                case 'ó': o_acute++; break;
                case 'ú': u_acute++; break;
                case 'à': a_grave++; break;
                case 'è': e_grave++; break;
                case 'ì': i_grave++; break;
                case 'ò': o_grave++; break;
                case 'ù': u_grave++; break;
                case 'ã': a_tilde++; break;
                case 'õ': o_tilde++; break;
                case 'â': a_circumflex++; break;
                case 'ê': e_circumflex++; break;
                case 'î': i_circumflex++; break;
                case 'ô': o_circumflex++; break;
                case 'û': u_circumflex++; break;
                default:
                    if (Character.isLetter(cLower)) {
                        consonantCount++;
                    }
                    break;
            }
        }

        counts[0] = a;
        counts[1] = e;
        counts[2] = i;
        counts[3] = o;
        counts[4] = u;
        counts[5] = a_acute;
        counts[6] = e_acute;
        counts[7] = i_acute;
        counts[8] = o_acute;
        counts[9] = u_acute;
        counts[10] = a_grave;
        counts[11] = e_grave;
        counts[12] = i_grave;
        counts[13] = o_grave;
        counts[14] = u_grave;
        counts[15] = a_tilde;
        counts[16] = o_tilde;
        counts[17] = a_circumflex;
        counts[18] = e_circumflex;
        counts[19] = i_circumflex;
        counts[20] = o_circumflex;
        counts[21] = u_circumflex;
        counts[22] = consonantCount;

        return counts;
    }

    private static int countOccurrences(String content, String substring) {
        int count = 0;
        int index = 0;
        while ((index = content.indexOf(substring, index)) != -1) {
            count++;
            index += substring.length();
        }
        return count;
    }

    private static String formatOutput(int[] counts, int br, int table, String name) {
        return String.format(
                "a(%d) e(%d) i(%d) o(%d) u(%d) á(%d) é(%d) í(%d) ó(%d) ú(%d) à(%d) è(%d) ì(%d) ò(%d) ù(%d) ã(%d) õ(%d) â(%d) ê(%d) î(%d) ô(%d) û(%d) consoante(%d) <br>(%d) <table>(%d) %s",
                counts[0], counts[1], counts[2], counts[3], counts[4],
                counts[5], counts[6], counts[7], counts[8], counts[9],
                counts[10], counts[11], counts[12], counts[13], counts[14],
                counts[15], counts[16], counts[17], counts[18], counts[19],
                counts[20], counts[21], counts[22], br, table, name
        );
    }
}
