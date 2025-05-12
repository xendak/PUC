import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.ArrayList;

public class files {
  public static class Path {
    int start;
    int end;
  }

  public static boolean isConnected(Path a, Path b) {
    return (b.start >= a.start && b.start <= a.end);
  }

  public static void unifyPath(ArrayList<Path> arr, Path b) {
    int sz = arr.size() - 1;
    if (arr.get(sz).end < b.end)
      arr.get(sz).end = b.end;
  }

  public static void main(String[] args) {
    FileWriter wt = null;
    try {
      File res = new File("./my.out");
      if (res.exists())
        res.delete();

      res.createNewFile();
      wt = new FileWriter(res, true);
    } catch (IOException e) {
      e.printStackTrace();
      return;
    }

    try {
      File f = new File("./pub.in");
      Scanner input = new Scanner(f);
      int b = input.nextInt();
      int s = input.nextInt();
      while (b != 0) {
        ArrayList<Path> arr = new ArrayList<>();

        for (int i = 0; i < s; i++) {
          Path p = new Path();
          p.start = input.nextInt();
          p.end = input.nextInt();
          if (arr.isEmpty()) {
            arr.add(p);
          } else {
            int sz = arr.size();
            if (isConnected(arr.get(sz - 1), p)) {
              unifyPath(arr, p);
            } else {
              arr.add(p);
            }
          }
        }

        for (Path p : arr) {
          wt.write(String.format("[%d, %d] ", p.start, p.end));
        }
        wt.write("\n");

        b = input.nextInt();
        s = input.nextInt();
      }
      input.close();
    } catch (FileNotFoundException e) {
      System.out.println("error");
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    } finally {
      try {
        if (wt != null) {
          wt.close();
        }
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }
}
