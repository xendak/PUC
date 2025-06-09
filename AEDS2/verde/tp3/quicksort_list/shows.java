import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.Normalizer;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.List;
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

  public static class Show {
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
    Show() {
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

    Show(String show_id, String type, String title, String director,
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

    public Show clone() {
      Show result = new Show();
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
      this.date_added = LocalDate.parse(date, Show.DATE_TIME_FORMATTER);
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
      return this.date_added == null ? "NaN" : Show.DATE_TIME_FORMATTER.format(this.date_added);
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
      result.append("] ##");

      return result.toString();
    }
  }

  public static Show parseLine(String line) {
    boolean inside_quotes = false;
    Show result = new Show();
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
            result.setListedIn(temp.toString().split(", "));
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

  public static Show[] parseFile(String fileName, int n) {
    Show[] result = new Show[n];
    try (BufferedReader reader = new BufferedReader(
        new InputStreamReader(new FileInputStream(fileName), StandardCharsets.UTF_8))) {

      String line;
      int j = 0;

      reader.readLine();

      while ((line = reader.readLine()) != null && j < n) {
        result[j] = parseLine(line);
        j++;
      }

    } catch (IOException e) {
      System.err.println("Error reading file: " + e.getMessage());
    }
    return result;
  }

  public static class Node {
    Show data;
    Node prev;
    Node next;

    public Node(Show data) {
      this.data = data != null ? data.clone() : new Show();
      this.prev = null;
      this.next = null;
    }
  }

  public static class SortLog {
    double executionTime;
    long comparisonCount;

    public SortLog(double executionTime, long comparisonCount) {
      this.executionTime = executionTime;
      this.comparisonCount = comparisonCount;
    }
  }

  public static class List {
    private Node head;
    private Node tail;
    private int length;
    private static long globalComparisons = 0;

    public List() {
      this.head = null;
      this.tail = null;
      this.length = 0;
    }

    public boolean append(Show show) {
      Node toAdd = new Node(show);

      toAdd.next = null;
      toAdd.prev = tail;

      if (tail != null) {
        tail.next = toAdd;
      }

      tail = toAdd;

      if (head == null) {
        head = toAdd;
      }

      length++;
      return true;
    }

    public Show removeAt(int pos) {
      if (pos < 0 || pos >= length || head == null) {
        return new Show();
      }

      Node toRemove;

      if (pos == 0) {
        toRemove = head;
        head = toRemove.next;
        if (head != null) {
          head.prev = null;
        } else {
          tail = null;
        }
      } else if (pos == length - 1) {
        toRemove = tail;
        tail = toRemove.prev;
        if (tail != null) {
          tail.next = null;
        } else {
          head = null;
        }
      } else {
        Node curr = head;
        for (int i = 0; i < pos; i++) {
          curr = curr.next;
        }
        toRemove = curr;
        toRemove.prev.next = toRemove.next;
        toRemove.next.prev = toRemove.prev;
      }

      Show removedShow = toRemove.data.clone();
      length--;
      return removedShow;
    }

    public Show removeAtStart() {
      return removeAt(0);
    }

    public Show remove() {
      return removeAt(length - 1);
    }

    // Print the list
    public void print() {
      Node curr = head;
      while (curr != null) {
        System.out.println(curr.data.print());
        curr = curr.next;
      }
    }

    public int getLength() {
      return length;
    }

    private static int compareShowsByTitle(Show a, Show b) {
      globalComparisons++;
      return a.getTitle().compareToIgnoreCase(b.getTitle());
    }

    private static int compareShows(Show a, Show b) {
      globalComparisons++;
      int res = a.date_added.compareTo(b.date_added);
      if (res != 0)
        return res;
      return a.getTitle().compareToIgnoreCase(b.getTitle());
    }

    private static void swapShows(Node a, Node b) {
      Show temp = a.data;
      a.data = b.data;
      b.data = temp;
    }

    private Node partitionListSort(Node low, Node high) {
      if (low == null || high == null || low == high) {
        return low;
      }

      Show pivot = high.data;
      Node i = low.prev;

      for (Node j = low; j != high; j = j.next) {
        if (compareShows(j.data, pivot) <= 0) {
          i = (i == null) ? low : i.next;
          swapShows(i, j);
        }
      }

      i = (i == null) ? low : i.next;
      swapShows(i, high);

      return i;
    }

    private void quicksortRecursive(Node low, Node high) {
      if (low != null && high != null && low != high && low != high.next) {
        Node pivot = partitionListSort(low, high);

        if (pivot != null && pivot.prev != null) {
          quicksortRecursive(low, pivot.prev);
        }
        if (pivot != null && pivot.next != null) {
          quicksortRecursive(pivot.next, high);
        }
      }
    }

    private Node getLastNode() {
      Node curr = head;
      while (curr != null && curr.next != null) {
        curr = curr.next;
      }
      return curr;
    }

    public void quicksortList() {
      if (head == null || length <= 1) {
        return;
      }

      globalComparisons = 0;
      long startTime = System.nanoTime();

      Node last = getLastNode();
      quicksortRecursive(head, last);

      long endTime = System.nanoTime();
      double executionTime = (endTime - startTime) / 1_000_000_000.0;

      SortLog log = new SortLog(executionTime, globalComparisons);
      logSortPerformance(log);
    }

    private void logSortPerformance(SortLog log) {
      String LOG_FILE_NAME = "875628_quicksort.txt";

      try (PrintWriter writer = new PrintWriter(new FileWriter(LOG_FILE_NAME))) {
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        writer.printf("875628\t%d\t%.6f\n", log.comparisonCount, log.executionTime);
      } catch (IOException e) {
        System.out.println("Warning: Could not open log file");
      }
    }
  }

  public static void doQuestion(Show[] shows) {
    Scanner input = new Scanner(System.in);
    String line = input.nextLine();
    List list = new List();

    do {
      int sid = Integer.parseInt(line.substring(1));
      if (sid - 1 <= shows.length) {

        list.append(shows[sid - 1].clone());
      }
      line = input.nextLine();
    } while (!line.equals("FIM"));

    list.quicksortList();

    list.print();

    input.close();
  }

  public static void main(String[] args) {

    String showFile = "/tmp/disneyplus.csv";

    long n = countLines(showFile);
    Show[] shows = parseFile(showFile, (int) n);
    // START OF EACH SECTION.
    doQuestion(shows);
  }
}
