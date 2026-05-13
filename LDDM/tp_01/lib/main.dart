import 'dart:ui';
import 'package:flutter/material.dart';
import 'screens/setup.dart';

void main() {
  runApp(const LightsOutApp());
}

class LightsOutApp extends StatefulWidget {
  const LightsOutApp({super.key});

  static _LightsOutAppState of(BuildContext context) =>
      context.findAncestorStateOfType<_LightsOutAppState>()!;

  @override
  State<LightsOutApp> createState() => _LightsOutAppState();
}

class _LightsOutAppState extends State<LightsOutApp> {
  ThemeMode _themeMode = ThemeMode.system;

  void toggleTheme() {
    setState(() {
      if (_themeMode == ThemeMode.system) {
        final brightness = PlatformDispatcher.instance.platformBrightness;
        _themeMode = brightness == Brightness.dark
            ? ThemeMode.light
            : ThemeMode.dark;
      } else {
        _themeMode = _themeMode == ThemeMode.dark
            ? ThemeMode.light
            : ThemeMode.dark;
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Lights Out',
      themeMode: _themeMode,
      theme: ThemeData.light().copyWith(
        scaffoldBackgroundColor: const Color(0xFFF0F0F5),
      ),
      darkTheme: ThemeData.dark().copyWith(
        scaffoldBackgroundColor: const Color(0xFF0B0B12),
      ),
      home: const SetupScreen(),
    );
  }
}
