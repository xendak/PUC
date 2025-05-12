import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;

public class builtins {
  public static class Path {
    int start;
    int end;

    Path() {
      start = -1;
      end = -1;
    }

    Path(int s, int e) {
      start = s;
      end = e;
    }
    public void joinPath(Path b) {
      if (b.end > this.end) this.end = b.end;
    }
  }

  public static boolean isConnected(Path a, Path b) {
    return (b.start >= a.start && b.start <= a.end);
  }

  public static void coalesce(List<Path> l) {
    Comparator<Path> PathComparator = (p1, p2) -> Integer.compare(p1.start, p2.start);
    l.sort(PathComparator);

    List<Path> res = new ArrayList<>();
    Path curr = l.get(0);

    for (int i = 1; i < l.size(); i++) {
      Path next = l.get(i);

      if(isConnected(curr, next)) {
        curr.joinPath(next);
      } else {
        res.add(curr);
        curr = next;
      }
    }
    res.add(curr);

    for (Path p : res) {
      System.out.printf("[%d, %d]", p.start, p.end);
    }
    System.out.println();

  }

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int b, s;

    b = input.nextInt();
    s = input.nextInt();

    while (b != 0 && s != 0) {
      List<Path> l = new ArrayList<>();
      for (int i = 0; i < s; i++) {
        Path p = new Path();
        p.start = input.nextInt();
        p.end = input.nextInt();
        l.add(p);
      }

      coalesce(l);

      b = input.nextInt();
      s = input.nextInt();
    }
    input.close();
  }
}
