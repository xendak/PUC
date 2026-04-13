import 'package:flutter/material.dart';

import '../routes.dart';

class LoginPage extends StatefulWidget {
  final VoidCallback onCreateAccountTapped;

  const LoginPage({super.key, required this.onCreateAccountTapped});

  @override
  State<LoginPage> createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  final _emailController = TextEditingController();
  final _passwordController = TextEditingController();

  bool _obscurePassword = true;

  void _handleLogin() {
    if (_emailController.text == 'admin@admin.com' &&
        _passwordController.text == '12345') {
      Navigator.pushReplacementNamed(
        context,
        AppRoutes.list,
        arguments: 'Admin',
      );
    } else {
      showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: const Text('Failed to Login'),
          content: const Text('Incorrect e-mail or password.'),
          actions: [
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: const Text('OK'),
            ),
          ],
        ),
      );
    }
  }

  // :Validation
  // @, no dots before @, ends with .something
  String? _validateEmail(String? value) {
    if (value == null || value.isEmpty) return 'E-mail is required';
    final atIndex = value.indexOf('@');
    if (atIndex < 0) return 'E-mail must contain @';
    final domainPart = value.substring(atIndex + 1);
    if (!domainPart.contains('.')) {
      return 'Domain must contain a dot (e.g. gmail.com)';
    }
    if (domainPart.endsWith('.')) return 'Domain cannot end with a dot';
    return null;
  }

  @override
  void dispose() {
    _emailController.dispose();
    _passwordController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Stack(
      children: [
        Center(
          child: Padding(
            padding: const EdgeInsets.symmetric(horizontal: 150.0),
            child: Container(
              constraints: const BoxConstraints(maxWidth: 900),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const SizedBox(height: 10),
                  TextFormField(
                    controller: _emailController,
                    autovalidateMode: AutovalidateMode.onUserInteraction,
                    validator: _validateEmail,

                    textInputAction: TextInputAction.next,
                    style: const TextStyle(color: Colors.black),
                    decoration: const InputDecoration(
                      labelText: 'E-mail',
                      labelStyle: TextStyle(color: Colors.grey),
                    ),
                  ),
                  const SizedBox(height: 10),
                  TextField(
                    controller: _passwordController,
                    textInputAction: TextInputAction.done,
                    onSubmitted: (_) => _handleLogin(),
                    style: const TextStyle(color: Colors.black),
                    obscureText: _obscurePassword,
                    decoration: InputDecoration(
                      labelText: 'Password',
                      labelStyle: const TextStyle(color: Colors.grey),
                      suffixIcon: IconButton(
                        icon: Icon(
                          _obscurePassword
                              ? Icons.visibility_off
                              : Icons.visibility,
                        ),
                        onPressed: () {
                          setState(() => _obscurePassword = !_obscurePassword);
                        },
                      ),
                    ),
                  ),
                  const SizedBox(height: 20),
                  SizedBox(
                    width: double.infinity,
                    child: ElevatedButton(
                      onPressed: _handleLogin,
                      style: ElevatedButton.styleFrom(
                        backgroundColor: Colors.blue,
                        foregroundColor: Colors.white,
                      ),
                      child: const Text('Enter'),
                    ),
                  ),
                  const SizedBox(height: 20),
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      const Text(
                        'New here?',
                        style: TextStyle(color: Colors.black),
                      ),
                      TextButton(
                        onPressed: widget.onCreateAccountTapped,
                        child: const Text(
                          'Create an account',
                          style: TextStyle(color: Colors.blue),
                        ),
                      ),
                    ],
                  ),
                ],
              ),
            ),
          ),
        ),
      ],
    );
  }
}
