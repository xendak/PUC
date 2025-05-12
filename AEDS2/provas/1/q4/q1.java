import java.util.Scanner;
import java.util.ArrayList;

public class q1 {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int n = input.nextInt();
    int k = input.nextInt();
    input.nextLine();
    do {

      Exam ex = new Exam();

      for (int i = 0; i < n; i++) {
        int temp = input.nextInt();
        ex.addScore(temp);
      }
      input.nextLine();

      sort(ex);
      findMinScore(ex, k);

      System.out.println(ex.min_score);
      n = input.hasNextInt() ? input.nextInt() : 0;
      k = input.hasNextInt() ? input.nextInt() : 0;
      if (input.hasNextLine()) { input.nextLine(); }
    } while (n > 0 && k > 0);
    input.close();
  }

  public static void findMinScore(Exam ex, int people) {
    int temp = 0; int min = 0;
    for (int i = ex.scores.size() - 1; i > 0; i--) {
      Scores curr = ex.scores.get(i);
      if (temp < people) temp += curr.count;
      if (min == 0 && temp >= people) min = curr.score;
    }
    ex.min_score = min;
  }

  public static void swap(Exam ex, int src, int dst) {
    Scores aux = ex.scores.get(dst);
    Scores temp = new Scores(aux.score, aux.count);

    Scores i = ex.scores.get(src);
    Scores j = ex.scores.get(dst);
    j.score = i.score;
    j.count = i.count;
    i.score = temp.score;
    i.count = temp.count;

  }

  public static void sort(Exam ex) {
    for (int i = 0; i < ex.scores.size(); i++) {
      int temp = i;
      for (int j = i + 1; j < ex.scores.size(); j++)
        if (ex.scores.get(j).score < ex.scores.get(temp).score)
          temp = j;
      if (i != temp)
        swap(ex, i, temp);

    }
  }

  public static class Scores {
    public int score;
    public int count;

    Scores() {
      this.score = 0;
      this.count = 0;
    }

    Scores(int s) {
      this.score = s;
      this.count = 1;
    }

    Scores(int s, int c) {
      this.score = s;
      this.count = c;
    }
  }

  public static class Exam {
    public ArrayList<Scores> scores;
    public int min_score;

    Exam() {
      this.scores = new ArrayList<Scores>();
      this.min_score = 0;
    }

    public void addScore(int num) {
      boolean new_member = true;
      int i = 0;
      while (i < this.scores.size() && new_member) {
        if (this.scores.get(i).score == num) {
          new_member = false;
          Scores s = this.scores.get(i);
          s.count++;
        }
        i++;
      }
      if (new_member)
        this.scores.add(new Scores(num));
      
    }
  }
}
