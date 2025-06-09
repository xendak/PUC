import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.Arrays;

public class shows {

  static final int INSERTION_SORT_CUTOFF = 10;

  public static void sort(String[] arr) {
    if (arr == null || arr.length == 0)
      return;
    quickSort(arr, 0, arr.length - 1);
  }

  private static void quickSort(String[] arr, int left, int right) {
    int len = right - left + 1;

    if (len <= INSERTION_SORT_CUTOFF) {
      insertionSort(arr, left, right);
      return;
    }

    int pivotIndex = partition(arr, left, right);
    quickSort(arr, left, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, right);
  }

  private static void insertionSort(String[] arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
      String key = arr[i];
      int j = i - 1;
      while (j >= left && arr[j].compareTo(key) > 0) {
        arr[j + 1] = arr[j];
        j = j - 1;
      }
      arr[j + 1] = key;
    }
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
      } while (arr[i].compareTo(pivotValue) < 0);

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
    boolean compAB = arr[a].compareTo(arr[b]) > 0;
    boolean compBC = arr[b].compareTo(arr[c]) > 0;
    boolean compAC = arr[a].compareTo(arr[c]) > 0;

    if (compAB == compBC) {
      // a > b > c OR c > b > a
      return b;
    } else if (compAC == compBC) {
      // b > c > a OR a > c > b
      return c;
    } else {
      // b > a > c OR c > a > b
      return a;
    }
  }

  private static void swap(String[] arr, int i, int j) {
    String temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  public static class SHOW {
    static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("MMMM d, u");

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

    // CONSTRUCTORS
    SHOW() {
      this.show_id = "";
      this.type = "";
      this.title = "";
      this.cast = new String[0];
      this.country = "";
      this.date_added = LocalDate.now();
      this.release_year = 0;
      this.rating = "";
      this.duration = "";
      this.listed_in = new String[0];
      this.description = "";
    }

    SHOW(String show_id, String type, String title, String director,
        String[] cast, String country, LocalDate date_added, int release_year,
        String rating, String duration, String[] listed_in, String description) {
      this.show_id = show_id;
      this.type = type;
      this.title = title;
      this.cast = (cast != null) ? Arrays.copyOf(cast, cast.length) : new String[0];
      this.country = country;
      this.date_added = date_added;
      this.release_year = release_year;
      this.rating = rating;
      this.duration = duration;
      this.listed_in = (listed_in != null) ? Arrays.copyOf(listed_in, listed_in.length) : new String[0];
      this.description = description;
    }

    public SHOW clone() {
      SHOW result = new SHOW();
      result.show_id = this.show_id;
      result.type = this.type;
      result.title = this.title;
      result.director = this.director;
      result.cast = (this.cast != null) ? Arrays.copyOf(this.cast, this.cast.length) : new String[0];
      result.country = this.country;
      result.date_added = this.date_added;
      result.release_year = this.release_year;
      result.rating = this.rating;
      result.duration = this.duration;
      result.listed_in = (this.listed_in != null) ? Arrays.copyOf(this.listed_in, this.listed_in.length)
          : new String[0];
      result.description = this.description;
      return result;
    }

    // SETTERS
    public void setShowId(String show_id) {
      this.show_id = (show_id != null) ? show_id : "";
    }

    public void setType(String type) {
      this.type = (type != null) ? type : "";
    }

    public void setTitle(String title) {
      this.title = (title != null) ? title : "";
    }

    public void setDirector(String director) {
      this.director = (director != null) ? director : "";
    }

    public void setCast(String cast) {
      if (cast != null) {
        String[] cast_array = cast.trim().split(", ");
        sort(cast_array);
        this.cast = cast_array;
      }
    }

    public void setCast(String[] cast) {
      this.cast = (cast != null) ? cast : new String[0];
      sort(this.cast);
    }

    public void setCountry(String country) {
      this.country = (country != null) ? country : "";
    }

    public void setDateAdded(String date) {
      if (date.charAt(0) == '"')
        date = date.replaceAll("^\"|\"$", "");
      this.date_added = LocalDate.parse(date, SHOW.DATE_TIME_FORMATTER);
    }

    public void setDateAdded(LocalDate date_added) {
      this.date_added = date_added;
    }

    public void setReleaseYear(int release_year) {
      this.release_year = release_year;
    }

    public void setReleaseYear(String release_year) {
      this.release_year = Integer.parseInt(release_year);
    }

    public void setRating(String rating) {
      this.rating = (rating != null) ? rating : "";
    }

    public void setDuration(String duration) {
      this.duration = (duration != null) ? duration : "";
    }

    public void setListedIn(String listed_in) {
      if (listed_in != null) {
        String[] listed_in_array = listed_in.trim().split(", ");
        sort(listed_in_array);
        this.listed_in = listed_in_array;
      }
    }

    public void setListedIn(String[] listed_in) {
      this.listed_in = (listed_in != null) ? listed_in : new String[0];
      sort(this.listed_in);
    }

    public void setDescription(String description) {
      this.description = (description != null) ? description : "";
    }

    // GETTERS
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
      return this.date_added == null ? "NaN" : SHOW.DATE_TIME_FORMATTER.format(this.date_added);
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

      if (this.cast != null && this.cast.length > 0) {
        result.append(String.join(", ", this.cast));
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

      if (this.listed_in != null && this.listed_in.length > 0) {
        result.append(String.join(", ", this.listed_in));
      }
      result.append("] ## ");

      return result.toString();
    }
  }

  public static SHOW parseLine(String line) {
    boolean inside_quotes = false;
    SHOW result = new SHOW();
    if (line == null || line.isEmpty())
      return result;

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
            result.setType(temp.toString());
            break;
          case 2:
            // need to remove Double Quotes here in Verde, for some reason?
            result.setTitle(temp.toString());
            break;
          case 3:
            result.setDirector(temp.toString());
            break;
          case 4:
            // if (temp.charAt(0) == '\"') {
            String cast = temp.toString();
            result.setCast(cast.trim().split(", "));
            // } else {
            // result.setCast(temp.toString());
            // }
            break;
          case 5:
            result.setCountry(temp.toString());
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
            // if (temp.charAt(0) == '\"') {
            result.setListedIn(temp.toString().split(", "));
            // } else {
            // result.setListedIn(temp.toString());
            // }
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
        if (c == '\"') {
          inside_quotes = !inside_quotes;
        } else {
          temp.append(c);
        }
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
      byte[] buffer = new byte[8192];
      int bytesRead;
      StringBuilder lineBuilder = new StringBuilder();

      int j = -1;
      while ((bytesRead = is.read(buffer)) != -1) {
        for (int i = 0; i < bytesRead; i++) {
          char c = (char) buffer[i];
          if (c == '\n') {
            if (j >= 0) {
              result[j] = parseLine(lineBuilder.toString());
            }
            lineBuilder.setLength(0);
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

  public static class SequentialList {
    SHOW[] shows;
    int n;
    private static final int MAX_SIZE = 10000;

    public SequentialList() {
      this.shows = new SHOW[MAX_SIZE];
      this.n = 0;
    }

    public SequentialList(int size) {
      this.shows = new SHOW[size];
      this.n = 0;
    }

    public boolean insertAt(SHOW s, int pos) {
      if (pos < 0 || pos > this.n)
        return false;

      if (this.n >= this.shows.length)
        return false;

      for (int i = this.n; i > pos; i--) {
        this.shows[i] = this.shows[i - 1];
      }

      this.shows[pos] = s;
      this.n++;

      return true;
    }

    public boolean insertAtStart(SHOW s) {
      if (n >= this.shows.length)
        return false;

      for (int i = n; i > 0; i--) {
        this.shows[i] = this.shows[i - 1];
      }

      this.shows[0] = s;
      this.n++;

      return true;
    }

    public boolean insertAtEnd(SHOW s) {
      if (this.n >= this.shows.length)
        return false;

      this.shows[this.n] = s;
      this.n++;

      return true;
    }

    public SHOW removeAt(int pos) {
      if (n == 0)
        return null;
      if (pos < 0 || pos >= this.n)
        return null;

      SHOW removed = this.shows[pos];
      this.n--;

      for (int i = pos; i < this.n; i++) {
        this.shows[i] = this.shows[i + 1];
      }

      this.shows[this.n] = null;
      printSingle(removed.title);
      return removed;
    }

    public SHOW removeAtStart() {
      if (n == 0)
        return null;

      SHOW removed = this.shows[0];
      this.n--;

      for (int i = 0; i < this.n; i++) {
        this.shows[i] = this.shows[i + 1];
      }

      this.shows[this.n] = null;
      printSingle(removed.title);
      return removed;
    }

    public SHOW removeAtEnd() {
      if (this.n <= 0)
        return null;

      this.n--;
      SHOW removed = this.shows[this.n];
      this.shows[n] = null;

      printSingle(removed.title);
      return removed;

    }

    public void printSingle(String title) {
      System.out.printf("(R) %s\n", title);
    }

    public void print() {
      for (int i = 0; i < n; i++) {
        System.out.println(shows[i].print());
      }
    }
  }

  public static void doQuestion(SHOW[] shows) {
    Scanner input = new Scanner(System.in);
    String line = input.nextLine();
    SequentialList list = new SequentialList();

    do {
      int sid = Integer.parseInt(line.substring(1));
      if (sid - 1 <= shows.length) {

        list.insertAtEnd(shows[sid - 1].clone());
      }
      line = input.nextLine();
    } while (!line.equals("FIM"));

    int count = input.nextInt();
    input.nextLine();

    for (int i = 0; i < count; i++) {
      line = input.nextLine();
      String[] parts = line.split(" ");
      String op = parts[0];
      int sid = -1;
      int position = -1;

      if (parts.length > 2) {
        sid = Integer.parseInt(parts[2].substring(1));
        position = Integer.parseInt(parts[1]);
      } else if (parts.length == 2) {
        if (op.charAt(0) == 'I')
          sid = Integer.parseInt(parts[1].substring(1));
        else
          sid = Integer.parseInt(parts[1]);
      }

      switch (op.charAt(0)) {
        case 'R': {
          switch (op.charAt(1)) {
            case 'I':
              list.removeAtStart();
              break;
            case 'F':
              list.removeAtEnd();
              break;
            case '*':
              list.removeAt(sid);
              break;
            default:
              break;
          }
          break;
        }
        case 'I': {
          switch (op.charAt(1)) {
            case 'I':
              list.insertAtStart(shows[sid - 1]);
              break;
            case 'F':
              list.insertAtEnd(shows[sid - 1]);
              break;
            case '*':
              list.insertAt(shows[sid - 1], position);
              break;
            default:
              break;
          }
          break;
        }

      }
    }

    list.print();

    input.close();
  }

  public static void main(String[] args) {

    String showFile = "/tmp/disneyplus.csv";

    long n = countLines(showFile);
    SHOW[] shows = parseFile(showFile, (int) n);
    // START OF EACH SECTION.
    doQuestion(shows);
  }
}
