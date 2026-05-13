import 'dart:math';

/// non linear algeabra approach to lightsout.

class GameLogic {
  final int rows;
  final int cols;
  final int states;

  late int winState;
  late List<int> board;
  late List<int> solution;

  int moves = 0;
  bool won = false;

  GameLogic(this.rows, this.cols, this.states) {
    newPuzzle();
  }

  void newPuzzle() {
    final rand = Random();
    winState = rand.nextInt(states);
    int dim = rows * cols;

    board = List.filled(dim, winState);
    solution = List.filled(dim, 0);

    // generate a board that is solveable by randomly "pressing" stuff on the already solved board.
    // dont track the "moves"
    int scrambleMoves = dim * states;
    for (int i = 0; i < scrambleMoves; i++) {
      int r = rand.nextInt(rows);
      int c = rand.nextInt(cols);
      _applyCross(r, c, 1, isScramble: true);
    }

    moves = 0;
    won = false;
  }

  void _cycle(int r, int c, int times) {
    int idx = r * cols + c;
    board[idx] = (board[idx] + times) % states;
  }

  void _applyCross(int r, int c, int times, {bool isScramble = false}) {
    _cycle(r, c, times);
    if (r > 0) _cycle(r - 1, c, times);
    if (r + 1 < rows) _cycle(r + 1, c, times);
    if (c > 0) _cycle(r, c - 1, times);
    if (c + 1 < cols) _cycle(r, c + 1, times);

    // Since the operation is reversible, we can just
    // "undo" the moves by the player to generate
    // the correct solution at any given time
    int idx = r * cols + c;
    solution[idx] = (solution[idx] + (states - times)) % states;

    if (!isScramble) {
      moves += times;
      _checkWin();
    }
  }

  void press(int r, int c) {
    if (won) return;
    _applyCross(r, c, 1);
  }

  void pressToState(int r, int c, int target) {
    if (won) return;
    int cur = board[r * cols + c];
    int times = (target + states - cur) % states;
    if (times > 0) {
      _applyCross(r, c, times);
    }
  }

  void _checkWin() {
    for (int v in board) {
      if (v != winState) return;
    }
    won = true;
  }

  int getCell(int r, int c) {
    return board[r * cols + c];
  }
}
