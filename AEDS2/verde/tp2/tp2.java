import java.time.LocalDateTime;
import java.util.Scanner;

public class tp2 {
  public static class SHOW {
    String show_id;
    String type;
    String title;
    String director;
    String[] cast;
    String country;
    LocalDateTime date_addded;
    int release_year;
    String rating;
    String duration;
    String[] listed_in;
    String description;

  }

  public static SHOW parseLine(String line) {
    boolean inside_quotes = false;
    SHOW result = new SHOW();
    int n = 0;
    StringBuilder temp = new StringBuilder();
    String[] args = new String[12];
    for (int i = 0; i < line.length(); i++) {
      Character c = line.charAt(i);
      if (c == ',' && !inside_quotes) {
        args[n] = temp.length() == 0 ? "NaN" : temp.toString();
        temp.setLength(0);
        n++;
      } else {
        inside_quotes = c == '\"' ? !inside_quotes : inside_quotes;
        temp.append(c);
      }
    }

    args[n] = temp.length() == 0 ? "NaN" : temp.toString();
    result.show_id = args[0];
    result.title = args[1];
    result.type = args[2];
    result.title = args[3];
    result.director = args[4];
    result.cast = parseStringToArray(args[5]);
    result.country = args[6];
    result.date_added = parseDate(args[7]);
    result.release_year = parseInt(args[8]);
    result.rating = args[9];
    result.duration = args[10];
    result.listed_in = parseStringToArray(args[11]);
    result.description = args[12];

    return result;
  }

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);

    // skip first line as its the table's titles.
    input.nextLine();
    String line = input.nextLine();
    SHOW[] shows = new SHOW[10000];
    int i = 0;
    while (!line.equals("FIM")) {
      System.out.println("line: " + line);
      shows[i] = parseLine(line);

      i++;
      line = "FIM";input.nextLine();
    }
    input.close();
  }
}
