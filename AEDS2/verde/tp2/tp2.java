import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class tp2 {

  public static void sort(String[] arr) {
    // quick
    quickSort(arr, 0, arr.length - 1); 
  }

  public static void swap(String[] arr, int dst, int src) {
    String aux = arr[src];
    arr[src] = arr[dst];
    arr[dst] = aux;
  }
  
  public static int getRandomNumber(int min, int max) {
      return (int) ((Math.random() * (max - min)) + min);
  }

  public static int getPivotMedian(String[] arr) {
    int a = 0;
    int b = arr.length - 1;
    int c = getRandomNumber(a + 1, b - 1);
    System.out.println("a: " + arr[a] + "\tb: " + arr[b] + "\tcomp: " + arr[a].compareTo(arr[b]));
    if (arr[a].compareTo(arr[b]) <= 0)
      return arr[a].compareTo(arr[c]) > 0 ? a : c;
    else
      return arr[b].compareTo(arr[c]) > 0 ? b : c;
  }

  public static int getPivot(String[] arr, int left, int right) {
    int res = 0;
    int pivot = getPivotMedian(arr);
    while (left < pivot && arr[left].compareTo(arr[pivot]) < 0)
      left--;
    swap(arr, left, pivot);
    while (right > pivot && arr[right].compareTo(arr[pivot]) > 0)
      right--;
    swap(arr, right, pivot);

    return pivot;
  }

  public static void quickSort(String[] arr, int left, int right) {
    if (left < right) {
      int pivot = getPivot(arr, left, right);
      quickSort(arr, left, pivot - 1);
      quickSort(arr, pivot + 1, right);
    }
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

    public void setShowId(String show_id) { this.show_id = show_id; }
    public void setType(String type) { this.type = type; }
    public void setTitle(String title) { this.title = title; }
    public void setDirector(String director) { this.director = director; }

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
      for (int i = 0; i < cast.length; i++) { this.cast[i] = cast[i]; }
    }

    public void setCountry(String country) { this.country = country; }
    // MONTH DAY, YEAR
    public void setDateAdded(String date) { 
      if (date.charAt(0) == '"') date = date.replaceAll("^\"|\"$", "");
      DateTimeFormatter dtf = DateTimeFormatter.ofPattern("MMMM d, u");
      this.date_added = LocalDate.parse(date, dtf); 
    }
    public void setReleaseYear(String release_year) { this.release_year = Integer.parseInt(release_year); }
    public void setReleaseYear(int release_year) { this.release_year = release_year; }

    public void setRating(String rating) { this.rating = rating; }
    public void setDuration(String duration) { this.duration = duration; }

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
      for (int i = 0; i < listed_in.length; i++) { this.listed_in[i] = listed_in[i]; }
    }

    public void setDescription(String description) { this.description = description; }

    public String getShowId() { return this.show_id; }
    public String getType() { return this.type; }
    public String getTitle() { return this.title; }
    public String getDirector() { return this.director; }
    public String[] getCast() { return this.cast; }
    public String getCountry() { return this.country; }
    public String getDateAdded() { 
      DateTimeFormatter dtf = DateTimeFormatter.ofPattern("MMMM d, u");
      return dtf.format(this.date_added); 
    }
    public int getReleaseYear() { return this.release_year; }
    public String getRating() { return this.rating; }
    public String getDuration() { return this.duration; }
    public String[] getListedIn() { return this.listed_in; }
    public String getDescription() { return this.description; }
    public int getCastSize() { return this.cast_capacity; }
    public int getListedInSize() { return this.listed_in_capacity; }

    public String print() {
      // [=> id ## type ## title ## director ## [cast] ## country ## date added ##
      // release year ## rating ## duration ## [listed in].
      StringBuilder result = new StringBuilder();
      result.append("=> ");
      result.append(this.show_id);
      result.append(" ## ");

      result.append(this.type);
      result.append(" ## ");
      
      result.append(this.title);
      result.append(" ## ");
      
      result.append(this.director);
      result.append(" ## [");
      
      for(int i = 0; i < this.cast_capacity; i++) {
        result.append(this.cast[i]);
        if (i != this.cast_capacity - 1) result.append(", ");
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
      
      for(int i = 0; i < this.listed_in_capacity; i++) {
        result.append(this.listed_in[i]);
        if (i != this.listed_in_capacity - 1) result.append(',');
      }
      result.append("]");
      
      return result.toString();
    }
  }

  public static SHOW parseLine(String line) {
    boolean inside_quotes = false;
    SHOW result = new SHOW();
    int n = 0;
    StringBuilder temp = new StringBuilder();

    for (Character c : line.toCharArray()) {
      if (!inside_quotes && c == ',' || c =='\n') {
        if (temp.isEmpty()) temp.append("NaN");

        switch (n) {
          case 0:  result.setShowId(temp.toString()); break;
          case 1:  result.setType(temp.toString()); break;
          case 2:  result.setTitle(temp.toString()); break;
          case 3:  result.setDirector(temp.toString()); break;
          case 4:  
            if(temp.charAt(0) == '\"') {
              String cast = temp.toString().replaceAll("\"", "");
              result.setCast(cast.trim().split(", "));
            } else {
              result.setCast(temp.toString()); 
            }
            break;
          case 5:  result.setCountry(temp.toString()); break;
          case 6:  result.setDateAdded(temp.toString()); break;
          case 7:  result.setReleaseYear(temp.toString()); break;
          case 8:  result.setRating(temp.toString()); break;
          case 9:  result.setDuration(temp.toString()); break;
          case 10: 
            if(temp.charAt(0) == '\"') {
              String listed_in = temp.toString().replaceAll("\"", "");
              result.setListedIn(listed_in.split(", "));
            } else {
              result.setListedIn(temp.toString()); 
            }
            break;
          case 11: result.setDescription(temp.toString()); break;
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
    }

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

      System.out.println(shows[i].print());
      i++;
      line = "FIM";
      input.nextLine();
    }
    input.close();
  }
}
