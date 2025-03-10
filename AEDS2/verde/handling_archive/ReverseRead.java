import java.io.*;

public class ReverseRead {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        // Write to file
        RandomAccessFile raf = new RandomAccessFile("temp.txt", "rw");
        for (int i = 0; i < n; i++) {
            String num = br.readLine();
            raf.writeBytes(num + "\n");
        }
        raf.close();

        // Read backwards using seek
        raf = new RandomAccessFile("temp.txt", "r");
        long length = raf.length();
        long pos = length - 1;
        StringBuilder line = new StringBuilder();

        while (pos >= 0) {
            raf.seek(pos);
            char c = (char) raf.readByte();
            if (c == '\n') {
                if (line.length() > 0) {
                    System.out.println(line.reverse().toString());
                    line.setLength(0);
                }
            } else {
                line.append(c);
            }
            pos--;
        }
        if (line.length() > 0) {
            System.out.println(line.reverse().toString());
        }
        raf.close();
    }
}
