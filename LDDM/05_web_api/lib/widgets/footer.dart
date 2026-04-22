import 'package:flutter/material.dart';

class AppFooter extends StatelessWidget {
  final int currentIndex;
  final bool detailEnabled;
  final void Function(int) onTap;

  const AppFooter({
    super.key,
    required this.currentIndex,
    required this.detailEnabled,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    return BottomNavigationBar(
      currentIndex: currentIndex,
      onTap: (i) {
        if (i == 2 && !detailEnabled) return;
        onTap(i);
      },
      items: [
        const BottomNavigationBarItem(
          icon: Icon(Icons.home_outlined),
          activeIcon: Icon(Icons.home),
          label: 'HOME',
        ),
        const BottomNavigationBarItem(
          icon: Icon(Icons.explore_outlined),
          activeIcon: Icon(Icons.explore),
          label: 'EXPLORE',
        ),
        BottomNavigationBarItem(
          icon: Opacity(
            opacity: detailEnabled ? 1.0 : 0.3,
            child: const Icon(Icons.article_outlined),
          ),
          activeIcon: const Icon(Icons.article),
          label: 'DETAILS',
        ),
      ],
    );
  }
}
