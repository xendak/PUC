import 'package:flutter/material.dart';

// Material Colors Dark
class AppColors {
  static const bg = Color(0xFF0D0D12);
  static const surface = Color(0xFF16161E);
  static const surface2 = Color(0xFF1E1E28);
  static const accent = Color(0xFFA78BFA);
  static const muted = Color(0xFF8884A0);
  static const text = Color(0xFFF0EEFF);

  static const genreChipBg = Color(0x1FA78BFA);
  static const genreChipBorder = Color(0x4DA78BFA);
}

ThemeData buildTheme() => ThemeData(
  scaffoldBackgroundColor: AppColors.bg,
  colorScheme: const ColorScheme.dark(
    primary: AppColors.accent,
    surface: AppColors.surface,
  ),
  fontFamily: 'Roboto',
  textTheme: const TextTheme(bodyMedium: TextStyle(color: AppColors.text)),
  appBarTheme: const AppBarTheme(
    backgroundColor: AppColors.surface,
    elevation: 0,
    iconTheme: IconThemeData(color: AppColors.muted),
  ),
  bottomNavigationBarTheme: const BottomNavigationBarThemeData(
    backgroundColor: AppColors.surface,
    selectedItemColor: AppColors.accent,
    unselectedItemColor: AppColors.muted,
    showSelectedLabels: true,
    showUnselectedLabels: true,
    type: BottomNavigationBarType.fixed,
    elevation: 0,
  ),
  inputDecorationTheme: InputDecorationTheme(
    filled: true,
    fillColor: AppColors.surface2,
    border: OutlineInputBorder(
      borderRadius: BorderRadius.circular(12),
      borderSide: BorderSide.none,
    ),
    focusedBorder: OutlineInputBorder(
      borderRadius: BorderRadius.circular(12),
      borderSide: const BorderSide(color: AppColors.accent, width: 1.2),
    ),
    hintStyle: const TextStyle(color: AppColors.muted, fontSize: 14),
    contentPadding: const EdgeInsets.symmetric(horizontal: 16, vertical: 12),
  ),
);
