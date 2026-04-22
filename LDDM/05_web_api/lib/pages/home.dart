import 'package:flutter/material.dart';
import '../tmdb_service.dart';
import '../theme.dart';
import '../widgets/net_image.dart';

class HomePage extends StatefulWidget {
  final void Function(int id) onSelectSeries;

  const HomePage({super.key, required this.onSelectSeries});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage>
    with AutomaticKeepAliveClientMixin {
  @override
  bool get wantKeepAlive => true;

  List<TvSeries> _trending = [];
  List<TvSeries> _newSeries = [];
  bool _loading = true;
  int _heroIdx = 0;
  final _pageController = PageController();

  @override
  void initState() {
    super.initState();
    _load();
  }

  @override
  void dispose() {
    _pageController.dispose();
    super.dispose();
  }

  Future<void> _load() async {
    final results = await Future.wait([
      TmdbService.getPopularSeries(),
      TmdbService.getNewSeries(),
    ]);
    if (!mounted) return;
    setState(() {
      _trending = results[0].results.take(7).toList();
      _newSeries = results[1].results
          .where((s) => s.posterPath != null && s.overview.isNotEmpty)
          .take(10)
          .toList();
      _loading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    super.build(context);
    if (_loading) {
      return const Center(
        child: CircularProgressIndicator(color: AppColors.accent),
      );
    }
    return SingleChildScrollView(
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          if (_trending.isNotEmpty) _buildCarousel(),
          _buildSection('Trending', _trending),
          _buildSection('Newly Added', _newSeries),
          const SizedBox(height: 16),
        ],
      ),
    );
  }

  Widget _buildCarousel() {
    return SizedBox(
      height: 220,
      child: Stack(
        children: [
          PageView.builder(
            controller: _pageController,
            onPageChanged: (i) => setState(() => _heroIdx = i),
            itemCount: _trending.length,
            itemBuilder: (_, i) {
              final s = _trending[i];
              return GestureDetector(
                onTap: () => widget.onSelectSeries(s.id),
                child: Stack(
                  fit: StackFit.expand,
                  children: [
                    NetImage(imageUrl(s.backdropPath, size: 'w1280')),
                    Container(
                      decoration: const BoxDecoration(
                        gradient: LinearGradient(
                          begin: Alignment.bottomCenter,
                          end: Alignment.topCenter,
                          colors: [AppColors.bg, Colors.transparent],
                        ),
                      ),
                    ),
                    Positioned(
                      bottom: 16,
                      left: 16,
                      right: 60,
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            s.name,
                            style: const TextStyle(
                              fontSize: 20,
                              fontWeight: FontWeight.w600,
                              color: Colors.white,
                              shadows: [
                                Shadow(blurRadius: 8, color: Colors.black54),
                              ],
                            ),
                          ),
                          const SizedBox(height: 4),
                          Text(
                            '${s.voteAverage.toStringAsFixed(1)} ★ · ${s.year}',
                            style: const TextStyle(
                              fontSize: 11,
                              color: Colors.white70,
                            ),
                          ),
                        ],
                      ),
                    ),
                  ],
                ),
              );
            },
          ),

          // :Indicator
          Positioned(
            bottom: 16,
            right: 16,
            child: Row(
              children: List.generate(_trending.length, (i) {
                final active = i == _heroIdx;
                return AnimatedContainer(
                  duration: const Duration(milliseconds: 200),
                  margin: const EdgeInsets.only(left: 4),
                  width: active ? 14 : 5,
                  height: 5,
                  decoration: BoxDecoration(
                    color: active ? AppColors.accent : Colors.white30,
                    borderRadius: BorderRadius.circular(3),
                  ),
                );
              }),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildSection(String title, List<TvSeries> items) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Padding(
          padding: const EdgeInsets.fromLTRB(16, 20, 16, 10),
          child: Text(
            title,
            style: const TextStyle(
              fontSize: 14,
              fontWeight: FontWeight.w600,
              color: AppColors.text,
            ),
          ),
        ),
        SizedBox(
          height: 180,
          child: ListView.separated(
            scrollDirection: Axis.horizontal,
            padding: const EdgeInsets.symmetric(horizontal: 16),
            itemCount: items.length,
            separatorBuilder: (_, _) => const SizedBox(width: 10),
            itemBuilder: (_, i) {
              final s = items[i];
              return GestureDetector(
                onTap: () => widget.onSelectSeries(s.id),
                child: SizedBox(
                  width: 100,
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      NetImage(
                        imageUrl(s.posterPath, size: 'w342'),
                        width: 100,
                        height: 140,
                        borderRadius: BorderRadius.circular(10),
                      ),
                      const SizedBox(height: 5),
                      Text(
                        s.name,
                        maxLines: 1,
                        overflow: TextOverflow.ellipsis,
                        style: const TextStyle(
                          fontSize: 10,
                          color: AppColors.text,
                        ),
                      ),
                      Text(
                        '★ ${s.voteAverage.toStringAsFixed(1)}',
                        style: const TextStyle(
                          fontSize: 9,
                          color: AppColors.accent,
                        ),
                      ),
                    ],
                  ),
                ),
              );
            },
          ),
        ),
      ],
    );
  }
}
