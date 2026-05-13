import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flame/game.dart';
import '../game/config.dart';
import '../game/logic.dart';
import '../game/lightsout.dart';
import '../main.dart';
import 'setup.dart';

class GameScreen extends StatefulWidget {
  final GameConfig config;

  const GameScreen({super.key, required this.config});

  @override
  State<GameScreen> createState() => _GameScreenState();
}

class _GameScreenState extends State<GameScreen> {
  late GameLogic _logic;
  late Lightsout _flameGame;

  Timer? _timer;
  int _secondsElapsed = 0;

  @override
  void initState() {
    super.initState();
    _initGame();
  }

  void _initGame() {
    _logic = GameLogic(
      widget.config.size,
      widget.config.size,
      widget.config.states,
    );

    _flameGame = Lightsout(
      config: widget.config,
      logic: _logic,
      onStateChanged: _onStateChanged,
      onShowContextMenu: _showContextMenu,
      onWin: _showWinPopup,
    );

    _secondsElapsed = 0;
    _timer?.cancel();
    _timer = Timer.periodic(const Duration(seconds: 1), (timer) {
      if (!_logic.won) {
        setState(() => _secondsElapsed++);
      } else {
        timer.cancel();
      }
    });
  }

  @override
  void dispose() {
    _timer?.cancel();
    super.dispose();
  }

  void _onStateChanged() {
    setState(() {});
  }

  void _showWinPopup() {
    showDialog(
      context: context,
      barrierDismissible: false,
      builder: (context) {
        final theme = AppTheme.of(context);

        return AlertDialog(
          backgroundColor: theme.bar,
          shape: RoundedRectangleBorder(
            side: BorderSide(color: theme.winAccent, width: 2),
            borderRadius: BorderRadius.circular(12),
          ),
          title: Center(
            child: Text(
              "YOU WIN!",
              style: TextStyle(
                color: theme.winAccent,
                fontSize: 32,
                fontWeight: FontWeight.bold,
              ),
            ),
          ),
          content: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              Text(
                "TIME: ${_formatTime()}",
                style: TextStyle(color: theme.text, fontSize: 18),
              ),
              const SizedBox(height: 8),
              Text(
                "MOVES: ${_logic.moves}",
                style: TextStyle(color: theme.text, fontSize: 18),
              ),
            ],
          ),
          actionsAlignment: MainAxisAlignment.spaceEvenly,
          actions: [
            TextButton(
              onPressed: () {
                Navigator.pop(context);
                setState(() => _initGame());
              },
              child: Text(
                "RESTART",
                style: TextStyle(
                  color: theme.text,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
            TextButton(
              onPressed: () {
                Navigator.pop(context);
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(builder: (_) => const SetupScreen()),
                );
              },
              child: Text(
                "EXIT",
                style: TextStyle(
                  color: theme.text,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
          ],
        );
      },
    );
  }

  void _showSolutionPopup() {
    showDialog(
      context: context,
      builder: (context) {
        final theme = AppTheme.of(context);

        return AlertDialog(
          backgroundColor: theme.bar,
          title: Text("SOLUTION", style: TextStyle(color: theme.subText)),
          content: SizedBox(
            width: double.maxFinite,
            child: GridView.builder(
              shrinkWrap: true,
              physics: const NeverScrollableScrollPhysics(),
              gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
                crossAxisCount: _logic.cols,
                crossAxisSpacing: 4,
                mainAxisSpacing: 4,
              ),
              itemCount: _logic.rows * _logic.cols,
              itemBuilder: (context, index) {
                int presses = _logic.solution[index];
                bool active = presses > 0;

                return Container(
                  decoration: BoxDecoration(
                    color: active ? theme.activeBlock : theme.inactiveBlock,
                    border: Border.all(
                      color: active ? theme.activeBorder : theme.inactiveBorder,
                      width: active ? 2 : 1,
                    ),
                  ),
                  alignment: Alignment.center,
                  child: Text(
                    active ? presses.toString() : "",
                    style: TextStyle(
                      color: active ? theme.activeBorder : Colors.transparent,
                      fontWeight: FontWeight.bold,
                      fontSize: widget.config.size >= 7 ? 12 : 16,
                    ),
                  ),
                );
              },
            ),
          ),
          actions: [
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: Text("CLOSE", style: TextStyle(color: theme.text)),
            ),
          ],
        );
      },
    );
  }

  void _showContextMenu(int r, int c) {
    showDialog(
      context: context,
      builder: (context) {
        final theme = AppTheme.of(context);

        return AlertDialog(
          backgroundColor: theme.bar,
          title: Text("SET", style: TextStyle(color: theme.subText)),
          content: Wrap(
            spacing: 8,
            runSpacing: 8,
            children: List.generate(widget.config.states, (index) {
              return GestureDetector(
                onTap: () {
                  Navigator.pop(context);
                  _logic.pressToState(r, c, index);
                  _onStateChanged();
                  _flameGame.forceRedraw();
                },
                child: Container(
                  width: 50,
                  height: 50,
                  color: widget.config.palette[index],
                  alignment: Alignment.center,
                  child: Text(
                    index.toString(),
                    style: const TextStyle(
                      color: Colors.black87,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
              );
            }),
          ),
        );
      },
    );
  }

  String _formatTime() {
    int m = _secondsElapsed ~/ 60;
    int s = _secondsElapsed % 60;
    return '${m.toString().padLeft(2, '0')}:${s.toString().padLeft(2, '0')}';
  }

  @override
  Widget build(BuildContext context) {
    final theme = AppTheme.of(context);
    _flameGame.updateThemeColor(theme.bg);

    return Scaffold(
      backgroundColor: theme.bg,
      body: SafeArea(
        child: Column(
          children: [
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 15),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Row(
                    children: [
                      Text("WIN: ", style: TextStyle(color: theme.subText)),
                      Container(
                        width: 20,
                        height: 20,
                        decoration: BoxDecoration(
                          color: widget.config.palette[_logic.winState],
                          border: Border.all(color: theme.text),
                        ),
                      ),
                    ],
                  ),
                  Text(
                    _formatTime(),
                    style: TextStyle(color: theme.text, fontSize: 20),
                  ),
                  Row(
                    children: [
                      Text(
                        "MOVES: ${_logic.moves}",
                        style: TextStyle(color: theme.subText),
                      ),
                      const SizedBox(width: 10),
                      IconButton(
                        icon: Icon(
                          Theme.of(context).brightness == Brightness.dark
                              ? Icons.light_mode
                              : Icons.dark_mode,
                          color: theme.subText,
                        ),
                        onPressed: () => LightsOutApp.of(context).toggleTheme(),
                      ),
                    ],
                  ),
                ],
              ),
            ),
            Expanded(child: GameWidget(game: _flameGame)),
            Container(
              color: theme.bar,
              padding: const EdgeInsets.symmetric(vertical: 10),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  TextButton(
                    onPressed: _logic.won ? null : _showSolutionPopup,
                    child: Text(
                      "SOLUTION",
                      style: TextStyle(
                        color: _logic.won
                            ? theme.subText.withValues(alpha: 0.5)
                            : theme.text,
                      ),
                    ),
                  ),
                  TextButton(
                    onPressed: () {
                      setState(() => _initGame());
                    },
                    child: Text("RESTART", style: TextStyle(color: theme.text)),
                  ),
                  TextButton(
                    onPressed: () {
                      Navigator.pushReplacement(
                        context,
                        MaterialPageRoute(builder: (_) => const SetupScreen()),
                      );
                    },
                    child: Text("EXIT", style: TextStyle(color: theme.text)),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}
