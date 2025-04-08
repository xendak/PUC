import java.io.*;

public class ReverseRead {
    public static void main(String[] args) throws IOException {
        // kinda like scanner, but differnt :^)
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // read first line to check the amount of times we need to do things :)
        int num = Integer.parseInt(br.readLine());

        // Write to file while i < n
        RandomAccessFile file = new RandomAccessFile("temp.txt", "rw");
        for (int i = 0; i < num; i++) {
            String line = br.readLine();
            file.writeBytes(line + "\n");
        }
        file.close();

        // Read backwards using seek
        file = new RandomAccessFile("temp.txt", "r");
        long length = file.length();
        long pos = length - 1;
        StringBuilder line = new StringBuilder(); // since strings are immutable in java, we use this.

        while (pos >= 0) {
            file.seek(pos);
            char c = (char) file.readByte();
            if (c == '\n') {
                if (line.length() > 0) {
                    // only reason im reimplement this is because "VERDE" is dumb.
                    // the entry on the original is .200 so should be read as .200
                    // not as .2 like the expected output is.. therefore i must make
                    // my reverse function zzzzzz
                    // System.out.println(line.reverse().toString());
                    reverseLine(line.toString());
                    line.setLength(0);
                }
            } else {
                line.append(c);
            }
            pos--;
        }
        if (line.length() > 0) {
            reverseLine(line.toString());
        }
        file.close();
    }

    public static void reverseLine(String str) {
        boolean hasSeenDigit = false;
        int sz = str.length();
        //StringBuilder rev = new StringBuilder();
        //for (int i = 0; i < sz; i++) {
        //    Character c = str.charAt(i);
        //    boolean isZero = c == '0';
        //    if (isZero) {
        //        if (hasSeenDigit){
        //            rev.append(c);
        //        }
        //    } else {
        //        if (!hasSeenDigit && c != '.') {
        //            hasSeenDigit = true;
        //        }
        //        rev.append(c);
        //    }
        //}
        //
        //int len = rev.length();
        StringBuilder num = new StringBuilder();
        for (int i = 0; i < sz; i++) {
            num.append(str.charAt(sz - i - 1));
        }
        Double res = Double.parseDouble(num.toString());
        if (res % 1 == 0) {
            System.out.println(Integer.parseInt(num.toString()));
        } else {
            System.out.println(res);
        }
    }
}
