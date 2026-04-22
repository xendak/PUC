import 'package:flutter/material.dart';
import '../theme.dart';

/// Callback fired when user submits a search from the header.
typedef OnHeaderSearch = void Function(String query);

class AppHeader extends StatefulWidget implements PreferredSizeWidget {
  final OnHeaderSearch onSearch;

  const AppHeader({super.key, required this.onSearch});

  @override
  Size get preferredSize => const Size.fromHeight(56);

  @override
  State<AppHeader> createState() => _AppHeaderState();
}

class _AppHeaderState extends State<AppHeader> {
  bool _searching = false;
  final _ctrl = TextEditingController();
  final _focusNode = FocusNode();

  void _open() {
    setState(() => _searching = true);
    WidgetsBinding.instance.addPostFrameCallback((_) {
      _focusNode.requestFocus();
    });
  }

  void _close() {
    _ctrl.clear();
    _focusNode.unfocus();
    setState(() => _searching = false);
  }

  void _submit() {
    final q = _ctrl.text.trim();
    if (q.isEmpty) {
      _close();
      return;
    }
    _focusNode.unfocus();
    setState(() => _searching = false);
    widget.onSearch(q);
    _ctrl.clear();
  }

  @override
  void dispose() {
    _ctrl.dispose();
    _focusNode.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return AppBar(
      title: AnimatedSwitcher(
        duration: const Duration(milliseconds: 200),
        child: _searching ? _buildSearchField() : _buildTitle(),
      ),
      // :Search
      leading: IconButton(
        icon: AnimatedSwitcher(
          duration: const Duration(milliseconds: 200),
          child: _searching
              ? const Icon(Icons.arrow_back, key: ValueKey('back'))
              : const Icon(Icons.search, key: ValueKey('search')),
        ),
        onPressed: _searching ? _close : _open,
      ),
      actions: [
        if (_searching)
          IconButton(
            icon: const Icon(Icons.check, color: AppColors.accent),
            onPressed: _submit,
          ),
      ],
    );
  }

  Widget _buildTitle() {
    return const Align(
      key: ValueKey('title'),
      alignment: Alignment.centerLeft,
      child: Text(
        'Series Portal',
        style: TextStyle(
          color: AppColors.accent,
          fontSize: 18,
          fontWeight: FontWeight.w600,
          letterSpacing: 0.3,
        ),
      ),
    );
  }

  Widget _buildSearchField() {
    return TextField(
      key: const ValueKey('searchField'),
      controller: _ctrl,
      focusNode: _focusNode,
      style: const TextStyle(color: AppColors.text, fontSize: 14),
      cursorColor: AppColors.accent,
      textInputAction: TextInputAction.search,
      onSubmitted: (_) => _submit(),
      decoration: const InputDecoration(
        hintText: 'Buscar séries...',
        border: InputBorder.none,
        enabledBorder: InputBorder.none,
        focusedBorder: InputBorder.none,
        fillColor: Colors.transparent,
        contentPadding: EdgeInsets.zero,
      ),
    );
  }
}
