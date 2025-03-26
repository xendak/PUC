import java.util.Scanner;

public class q1 {
  public static class Research {
    private int rabbit;
    private int rat;
    private int frog;

    Research() {
      this.rabbit = 0;
      this.rat = 0;
      this.frog = 0;
    }

    public void addRabbit(int r) { this.rabbit += r; }
    public void addRat(int r) { this.rat += r; }
    public void addFrog(int f) { this.frog += f; }

    public int getRabbit() { return this.rabbit; }
    public int getRat() { return this.rat; }
    public int getFrog() { return this.frog; }
    public int getTotal() { return this.rat + this.frog + this.rabbit; }
  }  

  public static double getPercentage(int count, int total) {
    return (double) (count * 100/ (double) total);
  }

  public static void main(String[] args) {
      Scanner input = new Scanner(System.in);
      int n = input.nextInt();
      input.nextLine();
      Research re = new Research(); 
      String line;
      for (int i = 0; i < n; i++) {
        line = input.nextLine();
        String[] temp = line.split("\\s");
        int animals = Integer.parseInt(temp[0]);
        if (temp[1].charAt(0) == 'C') re.addRabbit(animals);
        else if (temp[1].charAt(0) == 'R') re.addRat(animals);
        else if (temp[1].charAt(0) == 'S') re.addFrog(animals);
      }

      System.out.println("Total: " + re.getTotal() + " cobaias");
      System.out.println("Total de coelhos: " + re.getRabbit());
      System.out.println("Total de ratos: " + re.getRat());
      System.out.println("Total de sapos: " + re.getFrog());
      System.out.printf("Percentual de coelhos: %.2f %%\n", getPercentage(re.getRabbit(), re.getTotal()));
      System.out.printf("Percentual de ratos: %.2f %%\n", getPercentage(re.getRat(), re.getTotal()));
      System.out.printf("Percentual de sapos: %.2f %%\n", getPercentage(re.getFrog(), re.getTotal()));
      input.close();
  }
}
