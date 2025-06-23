import java.util.Scanner;

public class q1 {
  public static class Carro {
    String placa, modelo, tipo, chassi;

    Carro() { }

    void ler(String linha) {
      String[] partes = linha.split(",");
      placa = partes[0];
      modelo = partes[1];
      tipo = partes[2];
      chassi = partes[3];
    }

    void imprimir() {
      System.out.println(placa + " " + modelo + " " + tipo + " " + chassi);
    }
  }

  public static class BinTree {
    class Node {
      Carro car;
      Node left;
      Node right;
    }

    Node root;

    BinTree() { }

    public Node insert(Node curr, Carro c) {
      if (curr == null) {
        Node n = new Node();
        n.left = null;
        n.right = null;
        n.car = c;
        return n;
      }
      if (c.placa.compareToIgnoreCase(curr.car.placa) < 0) {
        curr.left = insert(curr.left, c);

      } else if (c.placa.compareToIgnoreCase(curr.car.placa) > 0) {
        curr.right = insert(curr.right, c);
      } else {
        System.out.println("cant have same value");
        return null;
      }
      return curr;
    }

    public void imprimir(Node root) {
      if (root != null) {
        imprimir(root.left);
        root.car.imprimir();
        imprimir(root.right);
      }
    }

  }

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    String line = input.nextLine();
    BinTree t = new BinTree();
    while (!line.equals("FIM")) {
      Carro curr = new Carro();
      curr.ler(line);
      t.root = t.insert(t.root, curr);

      line = input.nextLine();

    }
    t.imprimir(t.root);
    input.close();
  }

}

  
    
    
    
      
        
        
        
      
      
    
    
      

  
