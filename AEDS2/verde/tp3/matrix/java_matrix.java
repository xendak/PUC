import java.util.Scanner;

class Cell {
  Cell up;
  Cell left;
  Cell right;
  Cell down;
  int val;

  public Cell(int value) {
    this.val = value;
    this.up = null;
    this.left = null;
    this.right = null;
    this.down = null;
  }
}

class Matrix {
  private Cell start;
  private int rows;
  private int cols;

  public Matrix(int rows, int cols) {
    this.rows = rows;
    this.cols = cols;

    if (rows == 0 || cols == 0) {
      this.start = null;
      return;
    }

    this.start = new Cell(0);

    // first row
    Cell current = start;
    for (int j = 1; j < cols; j++) {
      Cell newCell = new Cell(0);

      // horizontal
      current.right = newCell;
      newCell.left = current;

      current = newCell;
    }

    // remaining rows
    Cell firstOfPrevRow = start;
    for (int i = 1; i < rows; i++) {
      Cell prevRowCell = firstOfPrevRow;
      Cell firstOfCurrentRow = null;
      Cell prevInCurrentRow = null;

      for (int j = 0; j < cols; j++) {
        Cell newCell = new Cell(0);

        // vertical
        prevRowCell.down = newCell;
        newCell.up = prevRowCell;

        // horizontal
        if (j == 0) {
          firstOfCurrentRow = newCell;
        } else {
          prevInCurrentRow.right = newCell;
          newCell.left = prevInCurrentRow;
        }

        prevInCurrentRow = newCell;
        prevRowCell = prevRowCell.right;
      }

      firstOfPrevRow = firstOfCurrentRow;
    }
  }

  private Cell getCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || start == null) {
      return null;
    }

    Cell current = start;

    // go down
    for (int i = 0; i < row; i++) {
      current = current.down;
    }

    // go right
    for (int j = 0; j < col; j++) {
      current = current.right;
    }

    return current;
  }

  public void setElement(int row, int col, int value) {
    Cell cell = getCell(row, col);
    if (cell != null) {
      cell.val = value;
    }
  }

  public int getElement(int row, int col) {
    Cell cell = getCell(row, col);
    return cell != null ? cell.val : 0;
  }

  public int getRows() {
    return rows;
  }

  public int getCols() {
    return cols;
  }

  public Matrix sum(Matrix other) {
    if (this.rows != other.rows || this.cols != other.cols) {
      return null;
    }

    Matrix result = new Matrix(this.rows, this.cols);

    for (int i = 0; i < this.rows; i++) {
      for (int j = 0; j < this.cols; j++) {
        int sum = this.getElement(i, j) + other.getElement(i, j);
        result.setElement(i, j, sum);
      }
    }

    return result;
  }

  public Matrix multiply(Matrix other) {
    if (this.cols != other.rows) {
      return null;
    }

    Matrix result = new Matrix(this.rows, other.cols);

    for (int i = 0; i < this.rows; i++) {
      for (int j = 0; j < other.cols; j++) {
        int sum = 0;
        for (int k = 0; k < this.cols; k++) {
          sum += this.getElement(i, k) * other.getElement(k, j);
        }
        result.setElement(i, j, sum);
      }
    }

    return result;
  }

  public void showDiagonal() {
    int minDim = Math.min(rows, cols);
    for (int i = 0; i < minDim; i++) {
      System.out.print(getElement(i, i));
      if (i < minDim - 1) {
        System.out.print(" ");
      }
    }
    System.out.println();
  }

  public void showSecondaryDiagonal() {
    int minDim = Math.min(rows, cols);
    for (int i = 0; i < minDim; i++) {
      System.out.print(getElement(i, cols - 1 - i));
      if (i < minDim - 1) {
        System.out.print(" ");
      }
    }
    System.out.println();
  }

  public void print() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        System.out.print(getElement(i, j));
        if (j < cols - 1) {
          System.out.print(" ");
        }
      }
      System.out.println();
    }
  }
}

public class java_matrix {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int numCases = scanner.nextInt();

    for (int testCase = 0; testCase < numCases; testCase++) {
      int l1 = scanner.nextInt();
      int c1 = scanner.nextInt();

      Matrix matrix1 = new Matrix(l1, c1);
      for (int i = 0; i < l1; i++) {
        for (int j = 0; j < c1; j++) {
          int value = scanner.nextInt();
          matrix1.setElement(i, j, value);
        }
      }

      int l2 = scanner.nextInt();
      int c2 = scanner.nextInt();

      Matrix matrix2 = new Matrix(l2, c2);
      for (int i = 0; i < l2; i++) {
        for (int j = 0; j < c2; j++) {
          int value = scanner.nextInt();
          matrix2.setElement(i, j, value);
        }
      }

      // Output results
      matrix1.showDiagonal();
      matrix1.showSecondaryDiagonal();

      Matrix sumResult = matrix1.sum(matrix2);
      if (sumResult != null) {
        sumResult.print();
      }

      Matrix multResult = matrix1.multiply(matrix2);
      if (multResult != null) {
        multResult.print();
      }
    }

    scanner.close();
  }
}
