import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.io.IOException;
// import java.io.BufferedReader;
// import java.io.FileReader;

public class tp2 {

  public static void sort(String[] arr) {
    if (arr == null || arr.length == 0)
      return;
    quickSort(arr, 0, arr.length - 1);
  }

  private static void quickSort(String[] arr, int left, int right) {
    if (left >= right)
      return;

    int pivotIndex = partition(arr, left, right);
    quickSort(arr, left, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, right);
  }

  private static int partition(String[] arr, int left, int right) {
    int mid = left + (right - left) / 2;
    int pivotIndex = medianOfThree(arr, left, mid, right);
    String pivotValue = arr[pivotIndex];

    // Move pivot to end temporarily
    swap(arr, pivotIndex, right);

    int i = left - 1;
    int j = right;

    while (true) {
      do {
        i++;
      } while (i < right && arr[i].compareTo(pivotValue) < 0);
      do {
        j--;
      } while (j > left && arr[j].compareTo(pivotValue) > 0);

      if (i >= j)
        break;
      swap(arr, i, j);
    }

    // Move pivot to its final position
    swap(arr, i, right);
    return i;
  }

  private static int medianOfThree(String[] arr, int a, int b, int c) {
    if (arr[a].compareTo(arr[b]) > 0) {
      if (arr[b].compareTo(arr[c]) > 0)
        return b;
      else if (arr[a].compareTo(arr[c]) > 0)
        return c;
      else
        return a;
    } else {
      if (arr[a].compareTo(arr[c]) > 0)
        return a;
      else if (arr[b].compareTo(arr[c]) > 0)
        return c;
      else
        return b;
    }
  }

  private static void swap(String[] arr, int i, int j) {
    String temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  public static class SHOW {
    private int DEFAULT_SIZE = 100;
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private int cast_capacity;
    private String country;
    private LocalDate date_added;
    private int release_year;
    private String rating;
    private String duration;
    private String[] listed_in;
    private int listed_in_capacity;
    private String description;

    public void setShowId(String show_id) {
      this.show_id = show_id;
    }

    public void setType(String type) {
      this.type = type;
    }

    public void setTitle(String title) {
      this.title = title;
    }

    public void setDirector(String director) {
      this.director = director;
    }

    public void setCast(String cast) {
      this.cast = new String[DEFAULT_SIZE];
      this.cast_capacity = 1;
      this.cast[0] = cast.trim();
    }

    public void setCast(String[] cast) {
      int len = cast.length > DEFAULT_SIZE ? cast.length : DEFAULT_SIZE;
      this.cast_capacity = cast.length;
      this.cast = new String[len];
      sort(cast);
      for (int i = 0; i < cast.length; i++) {
        this.cast[i] = cast[i];
      }
    }

    public void setCountry(String country) {
      this.country = country;
    }

    // MONTH DAY, YEAR
    public void setDateAdded(String date) {
      if (date.charAt(0) == '"')
        date = date.replaceAll("^\"|\"$", "");
      DateTimeFormatter dtf = DateTimeFormatter.ofPattern("MMMM d, u");
      this.date_added = LocalDate.parse(date, dtf);
    }

    public void setReleaseYear(String release_year) {
      this.release_year = Integer.parseInt(release_year);
    }

    public void setReleaseYear(int release_year) {
      this.release_year = release_year;
    }

    public void setRating(String rating) {
      this.rating = rating;
    }

    public void setDuration(String duration) {
      this.duration = duration;
    }

    public void setListedIn(String listed_in) {
      this.listed_in = new String[DEFAULT_SIZE];
      this.listed_in_capacity = 1;
      this.listed_in[0] = listed_in.trim();
    }

    public void setListedIn(String[] listed_in) {
      int len = listed_in.length > DEFAULT_SIZE ? listed_in.length : DEFAULT_SIZE;
      this.listed_in_capacity = listed_in.length;
      this.listed_in = new String[len];
      sort(listed_in);
      for (int i = 0; i < listed_in.length; i++) {
        this.listed_in[i] = listed_in[i];
      }
    }

    public void setDescription(String description) {
      this.description = description;
    }

    public String getShowId() {
      return this.show_id;
    }

    public String getType() {
      return this.type;
    }

    public String getTitle() {
      return this.title;
    }

    public String getDirector() {
      return this.director;
    }

    public String[] getCast() {
      return this.cast;
    }

    public String getCountry() {
      return this.country;
    }

    public String getDateAdded() {
      DateTimeFormatter dtf = DateTimeFormatter.ofPattern("MMMM d, u");
      return this.date_added == null ? "NaN" : dtf.format(this.date_added);
    }

    public int getReleaseYear() {
      return this.release_year;
    }

    public String getRating() {
      return this.rating;
    }

    public String getDuration() {
      return this.duration;
    }

    public String[] getListedIn() {
      return this.listed_in;
    }

    public String getDescription() {
      return this.description;
    }

    public int getCastSize() {
      return this.cast_capacity;
    }

    public int getListedInSize() {
      return this.listed_in_capacity;
    }

    public String print() {
      // [=> id ## type ## title ## director ## [cast] ## country ## date added ##
      // release year ## rating ## duration ## [listed in].
      // TODO: verde says title then type, rather than what is written in .pdf
      StringBuilder result = new StringBuilder();
      result.append("=> ");
      result.append(this.show_id);
      result.append(" ## ");

      result.append(this.title);
      result.append(" ## ");

      result.append(this.type);
      result.append(" ## ");

      result.append(this.director);
      result.append(" ## [");

      for (int i = 0; i < this.cast_capacity; i++) {
        result.append(this.cast[i]);
        if (i != this.cast_capacity - 1)
          result.append(", ");
      }
      result.append("] ## ");

      result.append(country);
      result.append(" ## ");

      result.append(this.getDateAdded());
      result.append(" ## ");

      result.append(release_year);
      result.append(" ## ");

      result.append(rating);
      result.append(" ## ");

      result.append(duration);
      result.append(" ## [");

      for (int i = 0; i < this.listed_in_capacity; i++) {
        result.append(this.listed_in[i]);
        if (i != this.listed_in_capacity - 1)
          result.append(", ");
      }

      result.append("] ##");

      return result.toString();
    }
  }

  public static SHOW parseLine(String line) {
    boolean inside_quotes = false;
    SHOW result = new SHOW();
    int n = 0;
    StringBuilder temp = new StringBuilder();
    boolean isEmpty = false;

    for (Character c : line.toCharArray()) {
      if (!inside_quotes && c == ',' || c == '\n') {
        if (temp.isEmpty()) {
          temp.append("NaN");
          isEmpty = true;
        }

        switch (n) {
          case 0:
            result.setShowId(temp.toString());
            break;
          case 1:
            result.setType(temp.toString().replaceAll("\"", ""));
            break;
          case 2:
            // need to remove Double Quotes here in Verde, for some reason?
            result.setTitle(temp.toString().replaceAll("\"",""));
            break;
          case 3:
            result.setDirector(temp.toString().replaceAll("\"", ""));
            break;
          case 4:
            if (temp.charAt(0) == '\"') {
              String cast = temp.toString().replaceAll("\"", "");
              result.setCast(cast.trim().split(", "));
            } else {
              result.setCast(temp.toString());
            }
            break;
          case 5:
            result.setCountry(temp.toString().replaceAll("\"", ""));
            break;
          case 6:
            if (!isEmpty)
              result.setDateAdded(temp.toString());
            break;
          case 7:
            result.setReleaseYear(temp.toString());
            break;
          case 8:
            result.setRating(temp.toString());
            break;
          case 9:
            result.setDuration(temp.toString());
            break;
          case 10:
            if (temp.charAt(0) == '\"') {
              String listed_in = temp.toString().replaceAll("\"", "");
              result.setListedIn(listed_in.split(", "));
            } else {
              result.setListedIn(temp.toString());
            }
            break;
          case 11:
            result.setDescription(temp.toString());
            break;
          default:
            System.out.println("shouldnt reach here");
            break;
        }
        temp.setLength(0);
        n++;
      } else {
        inside_quotes = c == '\"' ? !inside_quotes : inside_quotes;
        temp.append(c);
      }
      isEmpty = false;
    }

    return result;
  }

  public static long countLines(String fileName) {

    long lines = 0;

    try (InputStream is = new BufferedInputStream(new FileInputStream(fileName))) {
      byte[] c = new byte[1024];
      int count = 0;
      int readChars = 0;
      boolean endsWithoutNewLine = false;
      while ((readChars = is.read(c)) != -1) {
        for (int i = 0; i < readChars; ++i) {
          if (c[i] == '\n')
            ++count;
        }
        endsWithoutNewLine = (c[readChars - 1] != '\n');
      }
      if (endsWithoutNewLine) {
        ++count;
      }
      lines = count;
    } catch (IOException e) {
      e.printStackTrace();
    }

    return lines;
  }

  public static SHOW[] parseFile(String fileName, int n) {
    SHOW[] result = new SHOW[n];
    try (InputStream is = new BufferedInputStream(new FileInputStream(fileName))) {
      byte[] buffer = new byte[8192]; // 8KB buffer (adjustable)
      int bytesRead;
      StringBuilder lineBuilder = new StringBuilder();

      int j = -1;
      while ((bytesRead = is.read(buffer)) != -1) {
        for (int i = 0; i < bytesRead; i++) {
          char c = (char) buffer[i];
          if (c == '\n') {
            // Process the line when newline is found
            if (j >= 0) {
              result[j] = parseLine(lineBuilder.toString());
            }
            lineBuilder.setLength(0); // Reset for next line
            j++;
          } else {
            lineBuilder.append(c);
          }
        }
      }

      if (lineBuilder.length() > 0) {
        result[j] = parseLine(lineBuilder.toString());
      }
    } catch (IOException e) {
      System.err.println("Error reading file: " + e.getMessage());
    }
    return result;
  }

  // trying out a different method
  // public static SHOW[] readFile(String fpath, long n) {
  //   SHOW[] result = new SHOW[(int) n];
  //   int i = 0;

  //   try (BufferedReader br = new BufferedReader(new FileReader(fpath))) {
  //     String line;
  //     br.readLine(); // skip first line;
  //     while ((line = br.readLine()) != null) {
  //       result[i] = parseLine(line);
  //       i++;
  //     }
  //   } catch (IOException e) {
  //     System.err.println("Error reading the file: " + e.getMessage());
  //   }

  //   return result;

  // }

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);

    String showFile = "/tmp/disneyplus.csv";

    long n = countLines(showFile);

    String line = input.nextLine();
    SHOW[] shows = parseFile(showFile, (int) n);
    do {
      int sid = Integer.parseInt(line.substring(1));

      System.out.println(shows[sid-1].print());
      line = input.nextLine();
    } while (!line.equals("FIM"));
    input.close();
  }
}
