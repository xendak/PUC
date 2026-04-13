import 'package:flutter/material.dart';

import '../routes.dart';
import '../widgets/header.dart';
import '../widgets/bottom_nav.dart';

class ListPage extends StatefulWidget {
  final String name;

  const ListPage({super.key, required this.name});

  @override
  State<ListPage> createState() => _ListPageState();
}

class _ListPageState extends State<ListPage> {
  void _onTabTapped(int index) {
    if (index == 1) {
      Navigator.pushReplacementNamed(context, AppRoutes.home);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: Header(title: 'Welcome, ${widget.name}'),
      body: ListView.builder(
        itemCount: 20,
        itemBuilder: (context, index) {
          return ListTile(
            title: Text('Item $index'),
            subtitle: Text('Descriptions should be here?! :) '),
            onTap: () {
              showDialog(
                context: context,
                builder: (context) => AlertDialog(
                  title: const Text('Alert'),
                  content: Text('You clicked on item: $index'),
                  actions: [
                    TextButton(
                      onPressed: () => Navigator.pop(context),
                      child: const Text('Close??'),
                    ),
                    TextButton(
                      onPressed: () => Navigator.pop(context),
                      child: const Text('Close!!'),
                    ),
                  ],
                ),
              );
            },
          );
        },
      ),
      bottomNavigationBar: BottomNav(
        currentIndex: 0,
        isAuthenticated: true,
        onTap: _onTabTapped,
      ),
    );
  }
}
