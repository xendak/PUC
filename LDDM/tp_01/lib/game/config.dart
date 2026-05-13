import 'package:flutter/material.dart';

class AppTheme {
  final Color bg;
  final Color surface;
  final Color bar;
  final Color text;
  final Color subText;
  final Color border;
  final Color activeBlock;
  final Color inactiveBlock;
  final Color activeBorder;
  final Color inactiveBorder;
  final Color winAccent;

  const AppTheme({
    required this.bg,
    required this.surface,
    required this.bar,
    required this.text,
    required this.subText,
    required this.border,
    required this.activeBlock,
    required this.inactiveBlock,
    required this.activeBorder,
    required this.inactiveBorder,
    required this.winAccent,
  });

  static const AppTheme dark = AppTheme(
    bg: Color(0xFF181818),
    surface: Color(0xFF101010),
    bar: Color(0xFF181818),
    text: Color(0xFFE4E4F0),
    subText: Color(0xFFA0A0A0),
    border: Color(0xFF6B8E23),
    activeBlock: Color(0xFF000000),
    inactiveBlock: Color(0xFF282828),
    activeBorder: Color(0xFF6B8E23),
    inactiveBorder: Color(0xFF000000),
    winAccent: Color(0xFF6B8E23),
  );

  static const AppTheme light = AppTheme(
    bg: Color(0xFFF0F0F5),
    surface: Color(0xFFf0f0f0),
    bar: Color(0xFFF0F0F0),
    text: Color(0xFF1A1A2C),
    subText: Color(0xFF757575),
    border: Color(0xFFD0D0E0),
    activeBlock: Color(0xFFE0E0F0),
    inactiveBlock: Color(0xFFF5F5FA),
    activeBorder: Color(0xFFAB4642),
    inactiveBorder: Color(0xFFC0C0D0),
    winAccent: Color(0xFFAB4642),
  );

  static AppTheme of(BuildContext context) {
    return Theme.of(context).brightness == Brightness.dark ? dark : light;
  }
}

class GameConfig {
  final int size;
  final int states;
  final List<Color> palette;

  static const List<Color> availableColors = [
    Color(0xFFE6194b),
    Color(0xFF42D4F4),
    Color(0xFF3CB44B),
    Color(0xFFF58231),
    Color(0xFF4363D8),
    Color(0xFFFFE119),
    Color(0xFF58256E),
  ];

  GameConfig({required this.size, required this.states})
    : palette = availableColors.sublist(0, states);
}
