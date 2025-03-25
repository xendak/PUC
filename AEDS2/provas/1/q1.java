import java.util.Scanner;

public class medal {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        int[][] medals = new int[n][3];
        String[] country = new String[n];
        input.skip("\n");

        for (int i = 0; i < n; i++) {
            String aux = input.nextLine();
            //System.out.println(aux);
            if (aux.length() > 0) {
                country[i] = parseLine(aux);
                int help = aux.indexOf(' ');
                medals[i] = getMedals(aux, n, help+1);
            }
        }
        //System.out.println("Done main, country list");
        //for (String i : country) {
        //    System.out.println(i);
        //}
        sortOrder(medals, country, n);

        input.close();
    }
    
    public static void swapString(String[] c, int src, int dst) {
        String aux = c[dst];
        c[dst] = c[src];
        c[src] = aux;   
    }
    
    public static void swapInt(int[][] c, int src, int dst) {
        // gold
        int aux = c[dst][0];
        c[dst][0] = c[src][0];
        c[src][0] = aux;
        
        // silver
        aux = c[dst][1];
        c[dst][1] = c[src][1];
        c[src][1] = aux;

        // copper
        aux = c[dst][2];
        c[dst][2] = c[src][2];
        c[src][2] = aux; 
    }  
            

    public static void sortOrder(int[][] medals, String[] country, int n) {
        // gold
        for (int i = 0; i < n; i++) {
            int goldi = medals[i][0]; // ouro
            int silveri = medals[i][1]; // prata
            int copperi = medals[i][2]; // bronze
            String countryi = country[i]; // pais
            // move left
            for (int j = 0; j < n; j++) {
                int goldj = medals[j][0]; // ouro
                int silverj = medals[j][1]; // prata
                int copperj = medals[j][2]; // bronze
                String countryj = country[j]; // pais

                boolean toSwap = false;

                if (goldi != goldj) { // j -> i
                    toSwap = goldj > goldi;
                } else if (silveri != silverj) {
                    toSwap = silverj > silveri;
                } else if (copperi == copperj) {
                    toSwap = copperj > copperi;
                } else if (copperi == copperj) {
                    toSwap = countryj.compareTo(countryi) < 0;
                }

                if (toSwap) {
                    swapString(country, j, i);
                    swapInt(medals, j, i);
                }
            }
        }

        for (int c = n-1; c >= 0; c--) {
            System.out.printf("%s %d %d %d\n", country[c], medals[c][0], medals[c][1], medals[c][2]);
        }
    }


    public static int toNumber(String num) {
        int decimalCase;
        if (num.length() == 1)
            decimalCase = 1;
        else
            decimalCase = 10 * (num.length() - 1);
        //System.out.println("o: " + num.length() + "\tn: " + decimalCase);
        int res = -1;
        for (int i = 0; i < num.length(); i++) {
            res = (int) (num.charAt(i) - '0') * (decimalCase);
            decimalCase = decimalCase / 10;
        }
        //System.out.println("f: " + res);
        return res;
    }

    public static int[] getMedals(String line, int n, int start) {
            int[] res = {-1, -1, -1};
            StringBuilder aux = new StringBuilder();
            int spaceCount = 0;
            int medals = 0;
            System.out.println(line + ": " + start + ": " + line.charAt(8));
            for (int i = 0; i < line.length(); i++) {
                Character c = line.charAt(i);
                if (c == ' ' && spaceCount == 0) {
                    spaceCount++;
                } else if (c == ' ' && spaceCount > 0) {
                    // TODO: resolve finished string
                    res[medals] = Integer.parseInt(aux.toString());   // toNumber(aux.toString());
                    medals++;
                    aux.setLength(0);
                } else if (spaceCount > 0)
                    aux.append(c);
            }
            res[medals] = toNumber(aux.toString());
            return res;
    }

    public static String parseLine(String line) {
        StringBuilder res = new StringBuilder();
        int i = 0;
        Character c = line.charAt(i);
        while (c != ' ') {
            res.append(c);
            i++;
            c = line.charAt(i);
        }
        return res.toString();
    }
}

