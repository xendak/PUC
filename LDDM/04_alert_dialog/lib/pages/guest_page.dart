import 'package:flutter/material.dart';

import 'login.dart';
import 'registration.dart';
import '../widgets/header.dart';
import '../widgets/bottom_nav.dart';

class GuestPage extends StatefulWidget {
  const GuestPage({super.key});

  @override
  State<GuestPage> createState() => _GuestPageState();
}

class _GuestPageState extends State<GuestPage> {
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
    return Scaffold(
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
        isAuthenticated: false,
        onTap: _onTabTapped,
      ),
    );
  }
}
