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

    for (Character c: line.toCharArray()) {
      if (!inside_quotes && c == ',' || c == '\n') {
        if (temp.length() == 0) {
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
          result.setTitle(temp.toString());
          break;
        case 3:
          result.setDirector(temp.toString());
          break;
        case 4:
          String cast = temp.toString();
          result.setCast(cast.trim().split(", "));
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

  static class Node {
    public boolean color;
    public Show key;
    public Node left, right;

    public Node() {
      this(null);
    }

    public Node(Show key) {
      this(key, true, null, null);
    }

    public Node(Show key, boolean color) {
      this(key, color, null, null);
    }

    public Node(Show key, boolean color, Node left, Node right) {
      this.color = color;
      this.key = key;
      this.left = left;
      this.right = right;
    }
  }

  public static class RBTree {
    private Node root;
    private static long globalComparisons = 0;

    public RBTree() {
      root = null;
    }

    private boolean isType4Node(Node curr) {
      return (curr.left != null && curr.right != null && curr.left.color == true && curr.right.color == true);
    }

    public void insert(Show key) {
      if (root == null) {
        root = new Node(key);

      } else if (root.left == null && root.right == null) {
        if (key.getTitle().compareToIgnoreCase(root.key.getTitle()) < 0) {
          root.left = new Node(key);
        } else {
          root.right = new Node(key);
        }

      } else if (root.left == null) {
        if (key.getTitle().compareToIgnoreCase(root.key.getTitle()) < 0) {
          root.left = new Node(key);
        } else if (key.getTitle().compareToIgnoreCase(root.right.key.getTitle()) < 0) {
          root.left = new Node(root.key);
          root.key = key;
        } else {
          root.left = new Node(root.key);
          root.key = root.right.key;
          root.right.key = key;
        }
        root.left.color = root.right.color = false;

      } else if (root.right == null) {
        if (key.getTitle().compareToIgnoreCase(root.key.getTitle()) > 0) {
          root.right = new Node(key);
        } else if (key.getTitle().compareToIgnoreCase(root.left.key.getTitle()) > 0) {
          root.right = new Node(root.key);
          root.key = key;
        } else {
          root.right = new Node(root.key);
          root.key = root.left.key;
          root.left.key = key;
        }
        root.left.color = root.right.color = false;

      } else {
        insert(key, null, null, null, root);
      }
      root.color = false;
    }

    private void balance(Node greatGrandParent, Node grandParent, Node parent, Node curr) {
      if (parent.color == true) {
        if (parent.key.getTitle().compareToIgnoreCase(grandParent.key.getTitle()) > 0) {
          if (curr.key.getTitle().compareToIgnoreCase(parent.key.getTitle()) > 0) {
            grandParent = rotateLeft(grandParent);
          } else {
            grandParent = rotateRightLeft(grandParent);
          }
        } else {
          if (curr.key.getTitle().compareToIgnoreCase(parent.key.getTitle()) < 0) {
            grandParent = rotateRight(grandParent);
          } else {
            grandParent = rotateLeftRight(grandParent);
          }
        }

        if (greatGrandParent == null) {
          root = grandParent;
        } else if (grandParent.key.getTitle().compareToIgnoreCase(greatGrandParent.key.getTitle()) < 0) {
          greatGrandParent.left = grandParent;
        } else {
          greatGrandParent.right = grandParent;
        }

        grandParent.color = false;
        grandParent.left.color = grandParent.right.color = true;
      }
    }

    private void insert(Show key, Node greatGrandParent, Node grandParent, Node parent, Node curr) {
      if (curr == null) {
        if (key.getTitle().compareToIgnoreCase(parent.key.getTitle()) < 0) {
          curr = parent.left = new Node(key, true);
        } else {
          curr = parent.right = new Node(key, true);
        }
        if (parent.color == true) {
          balance(greatGrandParent, grandParent, parent, curr);
        }
      } else {
        if (isType4Node(curr)) {
          curr.color = true;
          curr.left.color = curr.right.color = false;
          if (curr == root) {
            curr.color = false;
          } else if (parent.color == true) {
            balance(greatGrandParent, grandParent, parent, curr);
          }
        }

        int comparison = key.getTitle().compareToIgnoreCase(curr.key.getTitle());
        if (comparison < 0) {
          insert(key, grandParent, parent, curr, curr.left);
        } else if (comparison > 0) {
          insert(key, grandParent, parent, curr, curr.right);
        }
      }
    }

    private Node rotateRight(Node curr) {
      Node leftNode = curr.left;
      Node leftRightNode = leftNode.right;

      leftNode.right = curr;
      curr.left = leftRightNode;

      return leftNode;
    }

    private Node rotateLeft(Node curr) {
      Node rightNode = curr.right;
      Node rightLeftNode = rightNode.left;

      rightNode.left = curr;
      curr.right = rightLeftNode;

      return rightNode;
    }

    private Node rotateRightLeft(Node curr) {
      curr.right = rotateRight(curr.right);
      return rotateLeft(curr);
    }

    private Node rotateLeftRight(Node curr) {
      curr.left = rotateLeft(curr.left);
      return rotateRight(curr);
    }

    public boolean search(String showTitle) {
      System.out.printf("=>raiz  ");
      globalComparisons = 0;
      long startTime = System.nanoTime();
      boolean result = search(this.root, showTitle);
      long endTime = System.nanoTime();
      double executionTime = (endTime - startTime) / 1_000_000_000.0;

      SortLog log = new SortLog(executionTime, globalComparisons);
      logSortPerformance(log);
      return result;
    }

    private boolean search(Node curr, String showTitle) {
      if (curr == null) {
        return false;
      }

      globalComparisons++;
      int comp = showTitle.compareToIgnoreCase(curr.key.getTitle());

      if (comp < 0) {
        System.out.printf("esq ");
        return search(curr.left, showTitle);
      } else if (comp > 0) {
        System.out.printf("dir ");
        return search(curr.right, showTitle);
      } else {
        return true;
      }
    }

    private void logSortPerformance(SortLog log) {
      String LOG_FILE_NAME = "875628_avinegra.txt";
      try (PrintWriter writer = new PrintWriter(new FileWriter(LOG_FILE_NAME))) {
        writer.printf("875628\t%d\t%.6f\n", log.comparisonCount, log.executionTime);
      } catch (IOException e) {
        System.out.println("Warning: Could not open log file: " + e.getMessage());
      }
    }
  }

  public static void doQuestion(Show[] shows) {
    Scanner input = new Scanner(System.in);
    String line = input.nextLine();

    RBTree tree = new RBTree();

    while (!line.equals("FIM")) {
      int sid = Integer.parseInt(line.substring(1));
      if (sid > 0 && sid <= shows.length && shows[sid - 1] != null) {
        tree.insert(shows[sid - 1].clone());
      }
      line = input.nextLine();
    }

    line = input.nextLine();
    while (!line.equals("FIM")) {
      System.out.printf("%s\n", tree.search(line) ? "SIM" : "NAO");
      line = input.nextLine();
    }

    input.close();
  }

  public static void main(String[] args) {
    String showFile = "/tmp/disneyplus.csv";
    long n = countLines(showFile);
    Show[] shows = parseFile(showFile, (int) n);
    doQuestion(shows);
  }
}
