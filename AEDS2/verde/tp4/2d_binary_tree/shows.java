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
    for (int curr = left + 1; curr <= right; curr++) {
      String key = arr[curr];
      int j = curr - 1;
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

    swap(arr, pivotIndex, right);

    int curr = left - 1;
    int j = right;

    while (true) {
      do {
        curr++;
      } while (arr[curr].compareTo(pivotValue) < 0);

      do {
        j--;
      } while (j > left && arr[j].compareTo(pivotValue) > 0);
      if (curr >= j)
        break;

      swap(arr, curr, j);
    }

    swap(arr, curr, right);
    return curr;
  }

  private static int medianOfThree(String[] arr, int a, int b, int c) {
    boolean compAB = arr[a].compareTo(arr[b]) > 0;
    boolean compBC = arr[b].compareTo(arr[c]) > 0;
    boolean compAC = arr[a].compareTo(arr[c]) > 0;

    if (compAB == compBC) {
      return b;
    } else if (compAC == compBC) {
      return c;
    } else {
      return a;
    }
  }

  private static void swap(String[] arr, int curr, int j) {
    String temp = arr[curr];
    arr[curr] = arr[j];
    arr[j] = temp;
  }

  public static class Show {
    static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("MMMM d, u");

    private String show_id;
    private String type;
    private String title;
    private String rightector;
    private String[] cast;
    private String country;
    private LocalDate date_added;
    private int release_year;
    private String rating;
    private String duration;
    private String[] listed_in;
    private String description;

    Show() {
      this.show_id = "";
      this.type = "";
      this.title = "";
      this.cast = new String[0];
      this.country = "";
      this.date_added = null;
      this.release_year = 0;
      this.rating = "";
      this.duration = "";
      this.listed_in = new String[0];
      this.description = "";
    }

    Show(String show_id, String type, String title, String rightector,
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
      result.rightector = this.rightector;
      result.cast = (this.cast != null) ? Arrays.copyOf(this.cast, this.cast.length) : new String[0];
      result.country = this.country;
      result.date_added = this.date_added;
      result.release_year = this.release_year;
      result.rating = this.rating;
      result.duration = this.duration;
      result.listed_in = (this.listed_in != null) ? Arrays.copyOf(this.listed_in, this.listed_in.length) :
        new String[0];
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

    public void setrightector(String rightector) {
      this.rightector = (rightector != null) ? rightector : "";
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
      if (date != null && !date.isEmpty() && !date.equals("NaN")) {
        if (date.charAt(0) == '"')
          date = date.replaceAll("^\"|\"$", "");
        this.date_added = LocalDate.parse(date.trim(), Show.DATE_TIME_FORMATTER);
      }
    }

    public void setDateAdded(LocalDate date_added) {
      this.date_added = date_added;
    }

    public void setReleaseYear(int release_year) {
      this.release_year = release_year;
    }

    public void setReleaseYear(String release_year) {
      this.release_year = Integer.parseInt(release_year.trim());
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
    public String getrightector() {
      return this.rightector;
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
      StringBuilder result = new StringBuilder();
      result.append("=> ").append(this.show_id).append(" ## ").append(this.title).append(" ## ").append(this.type)
        .append(" ## ").append(this.rightector).append(" ## [");
      if (this.cast != null && this.cast.length > 0) {
        result.append(String.join(", ", this.cast));
      }
      result.append("] ## ").append(country).append(" ## ").append(this.getDateAdded()).append(" ## ")
        .append(release_year).append(" ## ").append(rating).append(" ## ").append(duration).append(" ## [");
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
    if (line == null || line.isEmpty()) return result;

    int n = 0;
    StringBuilder temp = new StringBuilder();

    for (int curr = 0; curr < line.length(); curr++) {
      char c = line.charAt(curr);

      if (c == '\"') {
        inside_quotes = !inside_quotes;
      } else if (c == ',' && !inside_quotes) {
        String value = temp.toString().isEmpty() ? "NaN" : temp.toString();
        setField(result, n, value);
        temp.setLength(0);
        n++;
      } else {
        temp.append(c);
      }
    }
    // Set the last field
    setField(result, n, temp.toString());

    return result;
  }

  private static void setField(Show show, int fieldIndex, String value) {
    switch (fieldIndex) {
    case 0:
      show.setShowId(value);
      break;
    case 1:
      show.setType(value);
      break;
    case 2:
      show.setTitle(value);
      break;
    case 3:
      show.setrightector(value);
      break;
    case 4:
      show.setCast(value);
      break;
    case 5:
      show.setCountry(value);
      break;
    case 6:
      show.setDateAdded(value);
      break;
    case 7:
      show.setReleaseYear(value);
      break;
    case 8:
      show.setRating(value);
      break;
    case 9:
      show.setDuration(value);
      break;
    case 10:
      show.setListedIn(value);
      break;
    case 11:
      show.setDescription(value);
      break;
    }
  }

  public static long countLines(String fileName) {
    long lines = 0;
    try (InputStream is = new BufferedInputStream(new FileInputStream(fileName))) {
      byte[] c = new byte[1024];
      int count = 0;
      int readChars = 0;
      boolean endsWithoutNewLine = false;
      while ((readChars = is.read(c)) != -1) {
        for (int curr = 0; curr < readChars; ++curr) {
          if (c[curr] == '\n')
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

  public static class SortLog {
    double executionTime;
    long comparisonCount;

    public SortLog(double executionTime, long comparisonCount) {
      this.executionTime = executionTime;
      this.comparisonCount = comparisonCount;
    }
  }

  public static class InnerNode {
    String title;
    InnerNode left;
    InnerNode right;

    public InnerNode(String title) {
      this(title, null, null);
    }

    public InnerNode(String title, InnerNode left, InnerNode right) {
      this.title = title;
      this.left = left;
      this.right = right;
    }
  }

  public static class BinTree {
    InnerNode root;

    public BinTree() {
      this.root = null;
    }

    public void insert(String title) {
      this.root = insert(this.root, title);
    }

    private InnerNode insert(InnerNode curr, String title) {
      if (curr == null) {
        curr = new InnerNode(title);
      } else if (title.compareTo(curr.title) < 0) {
        curr.left = insert(curr.left, title);
      } else if (title.compareTo(curr.title) > 0) {
        curr.right = insert(curr.right, title);
      }
      return curr;
    }

    public boolean search(String title) {
      return search(this.root, title);
    }

    private boolean search(InnerNode curr, String title) {
      if (curr == null) {
        return false;
      }
      TreeOfTrees.globalComparisons++;
      if (title.equals(curr.title)) {
        return true;
      }
      TreeOfTrees.globalComparisons++;
      if (title.compareTo(curr.title) < 0) {
        System.out.print("esq ");
        return search(curr.left, title);
      } else {
        System.out.print("dir ");
        return search(curr.right, title);
      }
    }
  }

  public static class OuterNode {
    Integer year_mod;
    OuterNode left;
    OuterNode right;
    BinTree tree;

    public OuterNode(Integer year_mod) {
      this(year_mod, null, null, new BinTree());
    }

    public OuterNode(Integer year_mod, OuterNode left, OuterNode right, BinTree tree) {
      this.year_mod = year_mod;
      this.left = left;
      this.right = right;
      this.tree = tree;
    }
  }

  public static class TreeOfTrees {
    OuterNode root;
    static long globalComparisons = 0;

    public TreeOfTrees() {
      this.root = null;
      int[] keys = {
        7,
        3,
        11,
        1,
        5,
        9,
        13,
        0,
        2,
        4,
        6,
        8,
        10,
        12,
        14
      };

      for (int key: keys) {
        this.root = insertKey(this.root, key);
      }
    }

    private OuterNode insertKey(OuterNode curr, int key) {
      if (curr == null) {
        curr = new OuterNode(key);
      } else if (key < curr.year_mod) {
        curr.left = insertKey(curr.left, key);
      } else if (key > curr.year_mod) {
        curr.right = insertKey(curr.right, key);
      }
      return curr;
    }

    public void insertShow(Show show) {
      int key = show.getReleaseYear() % 15;
      String title = show.getTitle();
      insertShow(this.root, key, title);
    }

    private void insertShow(OuterNode curr, int key, String title) {
      if (curr == null) {
        return;
      }
      if (key == curr.year_mod) {
        curr.tree.insert(title);
      } else if (key < curr.year_mod) {
        insertShow(curr.left, key, title);
      } else {
        insertShow(curr.right, key, title);
      }
    }

    public boolean search(String title) {
      globalComparisons = 0;
      long startTime = System.nanoTime();

      System.out.print("raiz ");
      boolean result = search(this.root, title);

      long endTime = System.nanoTime();
      double executionTime = (endTime - startTime) / 1_000_000_000.0;

      SortLog log = new SortLog(executionTime, globalComparisons);
      logSortPerformance(log);

      return result;
    }

    private boolean search(OuterNode curr, String title) {
      if (curr == null) {
        return false;
      }

      boolean found = curr.tree.search(title);

      if (!found) {
        System.out.print(" ESQ ");
        found = search(curr.left, title);
      }

      if (!found) {
        System.out.print(" DIR ");
        found = search(curr.right, title);
      }

      return found;
    }

    private void logSortPerformance(SortLog log) {
      String LOG_FILE_NAME = "875628_arvoreArvore.txt";
      try (PrintWriter writer = new PrintWriter(new FileWriter(LOG_FILE_NAME))) {
        writer.printf("875628\t%d\t%.6f\n", log.comparisonCount, log.executionTime);
      } catch (IOException e) {
        System.out.println("Warning: Could not open log file: " + e.getMessage());
      }
    }
  }

  public static void doQuestion(Show[] shows) {
    Scanner input = new Scanner(System.in);
    TreeOfTrees treeOfTrees = new TreeOfTrees();

    String line = input.nextLine();
    while (!line.equals("FIM")) {
      int sid = Integer.parseInt(line.substring(1));
      if (sid - 1 < shows.length && sid - 1 >= 0 && shows[sid - 1] != null) {
        treeOfTrees.insertShow(shows[sid - 1]);
      }
      line = input.nextLine();
    }

    line = input.nextLine();
    while (!line.equals("FIM")) {
      System.out.printf("%s\n", treeOfTrees.search(line) ? " SIM" : " NAO");
      line = input.nextLine();
    }

    input.close();
  }

  public static void main(String[] args) {
    String showFile = "/tmp/disneyplus.csv";
    long n = countLines(showFile);
    Show[] shows = parseFile(showFile, (int) n - 1);
    doQuestion(shows);
  }
}
