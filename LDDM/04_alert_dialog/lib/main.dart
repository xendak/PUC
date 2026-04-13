import 'package:flutter/material.dart';

import 'routes.dart';
import 'pages/guest_page.dart';
import 'pages/list.dart';

void main() {
  runApp(const MainPage());
}

class MainPage extends StatelessWidget {
  const MainPage({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(
        primarySwatch: Colors.blue,
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.blue),
        useMaterial3: true,
      ),
      initialRoute: AppRoutes.home,
      onGenerateRoute: (settings) {
        if (settings.name == AppRoutes.list) {
          final String name = settings.arguments as String? ?? 'Admin';
          return MaterialPageRoute(builder: (context) => ListPage(name: name));
        }
        return MaterialPageRoute(builder: (context) => const GuestPage());
      },
    );
  }
}
