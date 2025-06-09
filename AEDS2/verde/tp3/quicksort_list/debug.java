import java.text.Normalizer;

public class debug {
  public static void main(String[] args) {
    String a = "Lab Rats";
    String b = "LEGO Star Wars: The Freemaker Adventures";
    String c = "LEGO Star Wars: The Freemaker Adventures (Shorts)";
    String d = "LEGO Star Wars:\u00A0The New Yoda Chronicles – Duel of the Skywalkers"; // With non-breaking space

    compare("Lab vs LEGO Freemaker", a, b);
    compare("Lab vs LEGO Freemaker Shorts", a, c);
    compare("Lab vs LEGO New Yoda", a, d);
  }

  private static void compare(String label, String a, String b) {
    String na = normalize(a);
    String nb = normalize(b);
    int result = na.compareTo(nb);
    System.out.printf("%s:\n  [%s]\n  [%s]\n  => Result: %d\n\n", label, na, nb, result);
  }

  private static String normalize(String s) {
    return Normalizer.normalize(s, Normalizer.Form.NFKC)
        .replace('\u00A0', ' ')
        .replace('\u2013', '-')
        .trim();
  }
}
