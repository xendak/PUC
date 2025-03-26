import java.util.ArrayList;
import java.util.Scanner;

public class q1 {
  static class Country {
    private String name;
    private int gold;
    private int silver;
    private int copper;

    Country() {
      this.name = "";
      this.gold = 0;
      this.silver = 0;
      this.copper = 0;
    }

    Country(String name, int gold, int silver, int copper) {
      this.name = name;
      this.gold = gold;
      this.silver = silver;
      this.copper = copper;
    }

    
    // i don't really want to deal with get/setter? seems no place in here.
    // the entire class could've been public.

    public String getName()   { return this.name; }
    public int getGold()   { return this.gold; }
    public int getSilver() { return this.silver; }
    public int getCopper() { return this.copper; }

    public void setName(String name)  { this.name = name; }
    public void setGold(int gold)     { this.gold = gold; }
    public void setSilver(int silver) { this.silver = silver; }
    public void setCopper(int copper) { this.copper = copper; }
  }

  public static int power(int a, int b) {
    int num = 1;
    if (b <= 0) return 1;
    else {
      for (int i = 0; i < b; i++)
        num *= a;
    }
    return num;
  }

  public static int toInt(String str) {
    int len = str.charAt(str.length() - 1) == '\n' ? str.length() - 2 : str.length();
    int num = 0;
    for (int i = 0; i < len; i++) {
      int mult = power(10, len-i-1);
      num += (int) (mult * (char)(str.charAt(i) - '0'));
    }
    return num;
  }

  public static String[] splitOnSpace(String line) {
    StringBuilder temp = new StringBuilder();
    ArrayList<String> parts = new ArrayList<String>();

    for (int i = 0; i < line.length(); i++) {
      Character c = line.charAt(i);
      if (c == ' ') {
        parts.add(temp.toString());
        temp.setLength(0);
      } else {
        temp.append(c);
      }
    }
    parts.add(temp.toString());
    // System.out.println(parts);
    return parts.toArray(new String[0]);
  }

  public static void swap(Country[] c, int src, int dst) {
    Country temp = c[dst];
    c[dst] = c[src];
    c[src] = temp;
  }

  public static int compareString(String a, String b) {
    int len = a.length() > b.length() ? b.length() : a.length();
    int res = 0;
    int i = 0;
    while(i < len && res == 0) {
      res += (int) ((char) b.charAt(i) - a.charAt(i));
      i++;
    }
    return res;
  }
  
  public static boolean compareCountry(Country a, Country b) {
    if (a.gold != b.gold)
      return b.gold > a.gold;
    else if (a.silver != b.silver)
      return b.silver > a.silver;
    else if (a.copper != b.copper)
      return b.copper > a.copper;
    else
      return compareString(b.name, a.name) > 0;
  }
  
  public static void sort(Country[] c) {
    for (int i = 0; i < c.length; i++) {
      int temp = i;
      for (int j = i + 1; j < c.length; j++) {
        if (compareCountry(c[temp], c[j]))
          temp = j;
      }
      if (temp != i)
        swap(c, i, temp);
    }      
  }
  
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int n = toInt(input.nextLine());
    Country[] countries = new Country[n];
    String[] line;

    for (int i = 0; i < n; i++) {
      String currLine = input.nextLine();
      line = splitOnSpace(currLine);
      countries[i] = new Country(line[0], toInt(line[1]), toInt(line[2]), toInt(line[3]));
    }

    sort(countries);
    for (Country c: countries) {
      System.out.printf("%s %d %d %d\n", c.name, c.gold, c.silver, c.copper);
    }
    input.close();
  }
}
