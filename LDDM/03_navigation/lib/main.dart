import 'package:flutter/material.dart';

import 'pages/login.dart';
import 'pages/registration.dart';
import 'widgets/header.dart';
import 'widgets/bottom_nav.dart';

void main() {
  runApp(const MainPage());
}

class MainPage extends StatefulWidget {
  const MainPage({super.key});

  @override
  State<MainPage> createState() => _MainPageState();
}

class _MainPageState extends State<MainPage> {
  // Login | Registration
  int _currentIndex = 0;

  void _onTabTapped(int index) {
    setState(() {
      _currentIndex = index;
    });
  }

  void _goToRegistration() {
    setState(() {
      _currentIndex = 1;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      // debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.blue),
        useMaterial3: true,
      ),
      home: Scaffold(
        appBar: Header(title: _currentIndex == 0 ? 'Login' : 'Registration'),
        body: IndexedStack(
          index: _currentIndex,
          children: [
            LoginPage(onCreateAccountTapped: _goToRegistration),
            const RegistrationPage(),
          ],
        ),
        bottomNavigationBar: BottomNav(
          currentIndex: _currentIndex,
          onTap: _onTabTapped,
        ),
      ),
    );
  }
}
