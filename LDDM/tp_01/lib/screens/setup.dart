import 'package:flutter/material.dart';
import '../game/config.dart';
import 'game.dart';
import '../main.dart';

class SetupScreen extends StatefulWidget {
  const SetupScreen({super.key});

  @override
  State<SetupScreen> createState() => _SetupScreenState();
}

class _SetupScreenState extends State<SetupScreen> {
  int _selectedSize = 4;
  int _selectedStates = 3;

  @override
  Widget build(BuildContext context) {
    final theme = AppTheme.of(context);

    return Scaffold(
      backgroundColor: theme.bg,
      body: SafeArea(
        child: Stack(
          children: [
            Align(
              alignment: Alignment.topRight,
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: IconButton(
                  icon: Icon(
                    Theme.of(context).brightness == Brightness.dark
                        ? Icons.light_mode
                        : Icons.dark_mode,
                    color: theme.subText,
                  ),
                  onPressed: () => LightsOutApp.of(context).toggleTheme(),
                ),
              ),
            ),
            Center(
              child: SingleChildScrollView(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Text(
                      "LIGHTS OUT",
                      style: TextStyle(
                        color: theme.text,
                        fontSize: 48,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    const SizedBox(height: 20),
                    Text("BOARD SIZE", style: TextStyle(color: theme.subText)),
                    const SizedBox(height: 10),
                    Wrap(
                      alignment: WrapAlignment.center,
                      children: [
                        for (int i = 3; i <= 9; i++)
                          _buildSelector(
                            value: i,
                            current: _selectedSize,
                            onSelect: (v) => setState(() => _selectedSize = v),
                            theme: theme,
                          ),
                      ],
                    ),
                    const SizedBox(height: 40),
                    Text(
                      "NUMBER OF STATES",
                      style: TextStyle(color: theme.subText),
                    ),
                    const SizedBox(height: 10),
                    Wrap(
                      alignment: WrapAlignment.center,
                      children: [
                        for (int i = 2; i <= 7; i++)
                          _buildSelector(
                            value: i,
                            current: _selectedStates,
                            onSelect: (v) =>
                                setState(() => _selectedStates = v),
                            theme: theme,
                          ),
                      ],
                    ),
                    const SizedBox(height: 30),
                    Text("PREVIEW", style: TextStyle(color: theme.subText)),
                    const SizedBox(height: 10),
                    Wrap(
                      alignment: WrapAlignment.center,
                      spacing: 8,
                      children: List.generate(_selectedStates, (index) {
                        return Container(
                          width: 24,
                          height: 24,
                          decoration: BoxDecoration(
                            color: GameConfig.availableColors[index],
                            border: Border.all(color: theme.text, width: 1),
                            borderRadius: BorderRadius.circular(4),
                          ),
                        );
                      }),
                    ),
                    const SizedBox(height: 40),
                    ElevatedButton(
                      style: ElevatedButton.styleFrom(
                        backgroundColor: theme.surface,
                        side: BorderSide(color: theme.border),
                        padding: const EdgeInsets.symmetric(
                          horizontal: 50,
                          vertical: 15,
                        ),
                      ),
                      onPressed: () {
                        Navigator.pushReplacement(
                          context,
                          MaterialPageRoute(
                            builder: (_) => GameScreen(
                              config: GameConfig(
                                size: _selectedSize,
                                states: _selectedStates,
                              ),
                            ),
                          ),
                        );
                      },
                      child: Text(
                        "START GAME",
                        style: TextStyle(color: theme.text, fontSize: 18),
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildSelector({
    required int value,
    required int current,
    required ValueChanged<int> onSelect,
    required AppTheme theme,
  }) {
    bool isSelected = value == current;

    return GestureDetector(
      onTap: () => onSelect(value),
      child: Container(
        width: 44,
        height: 44,
        margin: const EdgeInsets.all(4),
        decoration: BoxDecoration(
          color: isSelected ? theme.activeBlock : theme.inactiveBlock,
          border: Border.all(
            color: isSelected ? theme.activeBorder : theme.inactiveBorder,
            width: 2,
          ),
        ),
        alignment: Alignment.center,
        child: Text(
          value.toString(),
          style: TextStyle(
            color: isSelected ? theme.activeBorder : theme.subText,
            fontSize: 18,
            fontWeight: FontWeight.bold,
          ),
        ),
      ),
    );
  }
}
