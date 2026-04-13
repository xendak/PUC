import 'package:flutter/material.dart';

class BottomNav extends StatelessWidget {
  final int currentIndex;
  final Function(int) onTap;
  final bool isAuthenticated;

  const BottomNav({
    super.key,
    required this.currentIndex,
    required this.onTap,
    required this.isAuthenticated,
  });

  @override
  Widget build(BuildContext context) {
    return BottomNavigationBar(
      backgroundColor: Colors.blue,
      selectedItemColor: Colors.white,
      unselectedItemColor: Colors.white38,
      selectedLabelStyle: const TextStyle(
        fontWeight: FontWeight.bold,
        fontSize: 14,
      ),
      unselectedLabelStyle: const TextStyle(fontSize: 12),
      currentIndex: currentIndex,
      items: isAuthenticated
          ? const <BottomNavigationBarItem>[
              BottomNavigationBarItem(icon: Icon(Icons.home), label: 'Home'),
              BottomNavigationBarItem(
                icon: Icon(Icons.logout),
                label: 'Logout',
              ),
            ]
          : const <BottomNavigationBarItem>[
              BottomNavigationBarItem(icon: Icon(Icons.home), label: 'Login'),
              BottomNavigationBarItem(
                icon: Icon(Icons.account_balance),
                label: 'Register',
              ),
            ],
      onTap: onTap,
    );
  }
}
