import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class Body extends StatefulWidget {
  const Body({super.key});

  @override
  State<Body> createState() => _BodyState();
}

class _BodyState extends State<Body> {
  // Controllers
  final _nameController = TextEditingController();
  final _birthDateController = TextEditingController();
  final _emailController = TextEditingController();
  final _phoneController = TextEditingController();
  final _passwordController = TextEditingController();

  bool _obscurePassword = true;

  String? _selectedGender;

  bool _emailNotifications = false;
  bool _phoneNotifications = false;

  double _rating = 10;

  // :Email
  // :validation
  // @, no dots before @, ends with .something
  String? _validateEmail(String? value) {
    if (value == null || value.isEmpty) return 'E-mail is required';
    final atIndex = value.indexOf('@');
    if (atIndex < 0) return 'E-mail must contain @';
    final localPart = value.substring(0, atIndex);
    if (localPart.contains('.')) return 'No dots allowed before @';
    final domainPart = value.substring(atIndex + 1);
    if (!domainPart.contains('.')) {
      return 'Domain must contain a dot (e.g. gmail.com)';
    }
    if (domainPart.endsWith('.')) return 'Domain cannot end with a dot';
    return null;
  }

  void _onRegister() {
    // for funsies till we implement it
    ScaffoldMessenger.of(context).showSnackBar(
      const SnackBar(content: Text('Registered! (not really ...)')),
    );
  }

  @override
  void dispose() {
    _nameController.dispose();
    _birthDateController.dispose();
    _emailController.dispose();
    _phoneController.dispose();
    _passwordController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return ListView(
      padding: const EdgeInsets.symmetric(horizontal: 24, vertical: 20),
      children: [
        // :Name
        TextField(
          controller: _nameController,
          maxLength: 60,
          textCapitalization: TextCapitalization.words,
          keyboardType: TextInputType.name,
          decoration: const InputDecoration(
            labelText: 'Name',
            prefixIcon: Icon(Icons.person_outline),
            border: OutlineInputBorder(),
          ),
        ),
        const SizedBox(height: 16),

        // :Date
        TextField(
          controller: _birthDateController,
          keyboardType: TextInputType.datetime,
          inputFormatters: [
            FilteringTextInputFormatter.digitsOnly,
            _DateInputFormatter(),
          ],
          decoration: const InputDecoration(
            labelText: 'Birth Date (DD/MM/YYYY)',
            prefixIcon: Icon(Icons.calendar_today_outlined),
            border: OutlineInputBorder(),
          ),
        ),
        const SizedBox(height: 16),

        // :Email
        TextFormField(
          controller: _emailController,
          keyboardType: TextInputType.emailAddress,
          autovalidateMode: AutovalidateMode.onUserInteraction,
          validator: _validateEmail,
          decoration: const InputDecoration(
            labelText: 'E-mail',
            prefixIcon: Icon(Icons.email_outlined),
            border: OutlineInputBorder(),
          ),
        ),
        const SizedBox(height: 16),

        // :Phone
        TextField(
          controller: _phoneController,
          keyboardType: TextInputType.phone,
          inputFormatters: [
            FilteringTextInputFormatter.digitsOnly,
            _PhoneInputFormatter(),
          ],
          decoration: const InputDecoration(
            labelText: 'Phone',
            prefixIcon: Icon(Icons.phone_outlined),
            border: OutlineInputBorder(),
            hintText: '(00) 00000-0000',
          ),
        ),
        const SizedBox(height: 16),

        // :Password
        TextField(
          controller: _passwordController,
          maxLength: 20,
          obscureText: _obscurePassword,
          decoration: InputDecoration(
            labelText: 'Password',
            prefixIcon: const Icon(Icons.lock_outline),
            border: const OutlineInputBorder(),
            suffixIcon: IconButton(
              icon: Icon(
                _obscurePassword ? Icons.visibility_off : Icons.visibility,
              ),
              onPressed: () {
                setState(() => _obscurePassword = !_obscurePassword);
              },
            ),
          ),
        ),
        const SizedBox(height: 8),

        // :Gender
        const Text(
          'Gender',
          style: TextStyle(fontSize: 16, fontWeight: FontWeight.w500),
        ),
        RadioGroup<String>(
          groupValue: _selectedGender,
          onChanged: (val) => setState(() => _selectedGender = val),
          child: Column(
            children:
                [
                      ('Male', 'male'),
                      ('Female', 'female'),
                      ("Don't want to say", 'unspecified'),
                    ]
                    .map(
                      (entry) => RadioListTile<String>(
                        title: Text(entry.$1),
                        value: entry.$2,
                        contentPadding: EdgeInsets.zero,
                        dense: true,
                      ),
                    )
                    .toList(),
          ),
        ),
        const SizedBox(height: 8),

        // :Notification
        const Text(
          'Notifications',
          style: TextStyle(fontSize: 16, fontWeight: FontWeight.w500),
        ),
        SwitchListTile(
          title: const Text('E-mail notifications'),
          secondary: const Icon(Icons.email_outlined),
          value: _emailNotifications,
          onChanged: (val) => setState(() => _emailNotifications = val),
          contentPadding: EdgeInsets.zero,
        ),
        SwitchListTile(
          title: const Text('Phone notifications'),
          secondary: const Icon(Icons.phone_outlined),
          value: _phoneNotifications,
          onChanged: (val) => setState(() => _phoneNotifications = val),
          contentPadding: EdgeInsets.zero,
        ),
        const SizedBox(height: 8),

        // :RateMyApp
        Text(
          'Rate my app: ${_rating.round()}',
          style: const TextStyle(fontSize: 16, fontWeight: FontWeight.w500),
        ),
        Slider(
          value: _rating,
          min: 1,
          max: 10,
          divisions: 9,
          label: _rating.round().toString(),
          onChanged: (val) => setState(() => _rating = val),
        ),
        const SizedBox(height: 24),

        // :Register
        SizedBox(
          width: double.infinity,
          child: ElevatedButton(
            onPressed: _onRegister,
            style: ElevatedButton.styleFrom(
              backgroundColor: Colors.blue,
              foregroundColor: Colors.white,
              padding: const EdgeInsets.symmetric(vertical: 16),
              textStyle: const TextStyle(
                fontSize: 16,
                fontWeight: FontWeight.bold,
              ),
            ),
            child: const Text('Register'),
          ),
        ),
        const SizedBox(height: 20),
      ],
    );
  }
}

// :DateInput
class _DateInputFormatter extends TextInputFormatter {
  @override
  TextEditingValue formatEditUpdate(
    TextEditingValue oldValue,
    TextEditingValue newValue,
  ) {
    final digits = newValue.text.replaceAll('/', '');
    if (digits.length > 8) return oldValue; // 12 - 12 - 1212 -> 8

    final buffer = StringBuffer();
    for (int i = 0; i < digits.length; i++) {
      if (i == 2 || i == 4) buffer.write('/');
      buffer.write(digits[i]);
    }

    final formatted = buffer.toString();
    return TextEditingValue(
      text: formatted,
      selection: TextSelection.collapsed(offset: formatted.length),
    );
  }
}

// :PhoneInput
// Positions: (XX) NNNNN-YYYY
class _PhoneInputFormatter extends TextInputFormatter {
  @override
  TextEditingValue formatEditUpdate(
    TextEditingValue oldValue,
    TextEditingValue newValue,
  ) {
    final digits = newValue.text;
    if (digits.length > 11) return oldValue;

    final buf = StringBuffer();
    for (int i = 0; i < digits.length; i++) {
      switch (i) {
        case 0:
          buf.write('(');
        case 2:
          buf.write(')');
        case 7:
          buf.write('-');
      }
      buf.write(digits[i]);
    }

    final formatted = buf.toString();
    return TextEditingValue(
      text: formatted,
      selection: TextSelection.collapsed(offset: formatted.length),
    );
  }
}
