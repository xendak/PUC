import java.util.Scanner;

public class Java {
  public static class Path {
    int start;
    int end;

    public void print() {
      System.out.print("[" + this.start + "," + this.end + "]");
    }

    public boolean isConnected(Path b) {
      return  this.start <= b.start && this.end >= b.start;
    }

    public void joinPath(Path b) {
      if (b.end > this.end)
        this.end = b.end;
    }

  }

  public static class List {
    public static class Node {
      Node next;
      Path el;

      Node() {
        this.el = new Path();
        this.el.start = -1;
        this.el.end = -1;
        this.next = null;
      }
      Node(Path p) {
        this.el = p;
        this.next = null;
      }
    }

    public Node head;
    public Node tail;

    List() {
      this.head = new Node();
      this.tail = head;
    }

    List(Path p) {
      this.head = new Node(p);
      this.tail = head;
    }

    public void insert(Path p) {
      Path to_add = p;
      Node tmp = new Node(to_add);

      this.tail.next = tmp;
      this.tail = tmp;

      Node curr = this.head.next.next;
      Node prev = this.head.next;

      while(curr != null) {
        if (comparePath(curr.el, prev.el)) {
          swap(curr, prev);
        }
        prev = curr;
        curr = curr.next;
      }
      

    }

    public static void swap(Node a, Node b) {
      Path p = new Path();
      p = b.el;
      b.el = a.el;
      a.el = p;
    }
    
    public static boolean comparePath(Path a, Path b) {
      return (a.start < b.start);
    }

    public void remove() {
      if (this.head == this.tail) return;

      this.head = this.head.next;
    }
    
    public void coalesce_path() {
      if (this.head == this.tail) return;

      Node curr = this.head.next.next;
      Node prev = this.head.next;

      while (curr != null) {
        Node tmp = curr.next;
        if(prev.el.isConnected(curr.el)) {
          prev.el.joinPath(curr.el);

          // delete the current "curr"
          prev.next = curr.next;
          
        } else {
          prev = curr;
      }

        curr = tmp;
      }
    }

    public void print() {
      Node tmp = this.head.next;
      while (tmp != null) {
        tmp.el.print();
        if (tmp.next != null) {
          System.out.printf(" -> ");
        }
        tmp = tmp.next;
      }
      System.out.println();
    }
  }


  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int s, b;
    b = input.nextInt();
    s = input.nextInt();

    while (b != 0 && s != 0) {
      List l = new List();

      for (int i = 0; i < s; i++) {
        Path p = new Path(); // if this is outside then we just rewrite the same pointer;
        p.start = input.nextInt();
        p.end = input.nextInt();
        l.insert(p);
      }

      l.coalesce_path();
      l.print();
      b = input.nextInt();
      s = input.nextInt();
    }

  }
}
