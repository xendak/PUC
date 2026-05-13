import 'dart:async';
import 'package:flame/components.dart';
import 'package:flame/events.dart';
import 'package:flame/game.dart';
import 'package:flutter/material.dart';
import 'config.dart';
import 'logic.dart';

class Lightsout extends FlameGame {
  final GameConfig config;
  final GameLogic logic;
  final VoidCallback onStateChanged;
  final VoidCallback onWin;
  final void Function(int r, int c) onShowContextMenu;

  Color _currentBgColor = const Color(0xFF0B0B12);

  Lightsout({
    required this.config,
    required this.logic,
    required this.onStateChanged,
    required this.onWin,
    required this.onShowContextMenu,
  });

  void updateThemeColor(Color color) {
    _currentBgColor = color;
  }

  @override
  Color backgroundColor() => _currentBgColor;

  @override
  Future<void> onLoad() async {
    _layoutBoard();
  }

  @override
  void onGameResize(Vector2 size) {
    super.onGameResize(size);
    _layoutBoard();
  }

  void _layoutBoard() {
    removeAll(children);

    const double pad = 20.0;
    double boardW = size.x - (pad * 2);
    double boardH = size.y - (pad * 2);

    double maxCellW = boardW / logic.cols;
    double maxCellH = boardH / logic.rows;
    double cellSize = maxCellW < maxCellH ? maxCellW : maxCellH;

    double gap = (cellSize / 12).clamp(2.0, double.infinity);
    cellSize -= gap;

    double totalW = logic.cols * (cellSize + gap) - gap;
    double totalH = logic.rows * (cellSize + gap) - gap;

    double startX = (size.x - totalW) / 2;
    double startY = (size.y - totalH) / 2;

    for (int r = 0; r < logic.rows; r++) {
      for (int c = 0; c < logic.cols; c++) {
        double px = startX + c * (cellSize + gap);
        double py = startY + r * (cellSize + gap);

        add(
          CellComponent(
            row: r,
            col: c,
            position: Vector2(px, py),
            size: Vector2.all(cellSize),
          ),
        );
      }
    }
  }

  void forceRedraw() {
    _layoutBoard();
  }
}

class CellComponent extends RectangleComponent
    with TapCallbacks, HasGameReference<Lightsout> {
  final int row;
  final int col;

  CellComponent({
    required this.row,
    required this.col,
    required super.position,
    required super.size,
  });

  @override
  void render(Canvas canvas) {
    int state = game.logic.getCell(row, col);
    Color color = game.config.palette[state];

    paint.color = color;
    super.render(canvas);

    final borderPaint = Paint()
      ..color = _darken(color, 0.45)
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2.0;
    canvas.drawRect(size.toRect(), borderPaint);

    if (size.x >= 24) {
      final textSpan = TextSpan(
        text: state.toString(),
        style: TextStyle(
          color: Colors.black.withValues(alpha: 0.6),
          fontSize: size.x >= 40 ? 20 : 12,
          fontWeight: FontWeight.bold,
        ),
      );
      final textPainter = TextPainter(
        text: textSpan,
        textDirection: TextDirection.ltr,
      );
      textPainter.layout();
      textPainter.paint(
        canvas,
        Offset(
          (size.x - textPainter.width) / 2,
          (size.y - textPainter.height) / 2,
        ),
      );
    }
  }

  @override
  void onTapDown(TapDownEvent event) {
    bool wasWon = game.logic.won;
    if (!wasWon) {
      game.logic.press(row, col);
      game.onStateChanged();
      game.forceRedraw();

      if (game.logic.won && !wasWon) {
        game.onWin();
      }
    }
  }

  @override
  void onLongTapDown(TapDownEvent event) {
    if (!game.logic.won) {
      game.onShowContextMenu(row, col);
    }
  }

  Color _darken(Color c, double factor) {
    return Color.fromARGB(
      (c.a * 255.0).round().clamp(0, 255),
      (c.r * 255.0 * factor).round().clamp(0, 255),
      (c.g * 255.0 * factor).round().clamp(0, 255),
      (c.b * 255.0 * factor).round().clamp(0, 255),
    );
  }
}
