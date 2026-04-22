import 'package:flutter/material.dart';
import '../tmdb_service.dart';
import '../theme.dart';
import '../widgets/net_image.dart';

class ExplorePage extends StatefulWidget {
  final ScrollController scrollController;

  final String initialQuery;
  final int initialPage;
  final int initialTotalPages;
  final List<TvSeries> initialResults;

  final void Function(String) onQueryChange;
  final void Function(int) onPageChange;
  final void Function(int) onTotalPagesChange;
  final void Function(List<TvSeries>) onResultsChange;

  final void Function(int id) onSelectSeries;

  const ExplorePage({
    super.key,
    required this.scrollController,
    required this.initialQuery,
    required this.initialPage,
    required this.initialTotalPages,
    required this.initialResults,
    required this.onQueryChange,
    required this.onPageChange,
    required this.onTotalPagesChange,
    required this.onResultsChange,
    required this.onSelectSeries,
  });

  static GlobalKey<ExplorePageState> createKey() =>
      GlobalKey<ExplorePageState>();

  @override
  ExplorePageState createState() => ExplorePageState();
}

class ExplorePageState extends State<ExplorePage>
    with AutomaticKeepAliveClientMixin {
  @override
  bool get wantKeepAlive => true;

  late final TextEditingController _ctrl;
  late String _query;
  late int _page;
  late int _totalPages;
  late List<TvSeries> _results;
  bool _loading = false;

  @override
  void initState() {
    super.initState();
    _query = widget.initialQuery;
    _page = widget.initialPage;
    _totalPages = widget.initialTotalPages;
    _results = widget.initialResults;
    _ctrl = TextEditingController(text: _query);
    if (_results.isEmpty) _fetch();
  }

  @override
  void dispose() {
    _ctrl.dispose();
    super.dispose();
  }

  // :Serach
  // public -> this needs to be available from search in header
  void searchFromOutside(String query) {
    _ctrl.text = query;
    _query = query;
    _page = 1;
    widget.onQueryChange(query);
    widget.onPageChange(1);
    _fetch(scrollTop: true);
  }

  Future<void> _fetch({bool scrollTop = false}) async {
    setState(() => _loading = true);
    try {
      final res = _query.isNotEmpty
          ? await TmdbService.searchSeries(_query, page: _page)
          : await TmdbService.getPopularSeries(page: _page);

      _results = res.results;
      _totalPages = res.totalPages;

      widget.onResultsChange(_results);
      widget.onTotalPagesChange(_totalPages);

      if (scrollTop && widget.scrollController.hasClients) {
        widget.scrollController.animateTo(
          0,
          duration: const Duration(milliseconds: 300),
          curve: Curves.easeOut,
        );
      }
    } finally {
      if (mounted) setState(() => _loading = false);
    }
  }

  void _search() {
    _query = _ctrl.text.trim();
    _page = 1;
    widget.onQueryChange(_query);
    widget.onPageChange(1);
    _fetch(scrollTop: true);
  }

  void _changePage(int delta) {
    _page = (_page + delta).clamp(1, _totalPages);
    widget.onPageChange(_page);
    _fetch(scrollTop: true);
  }

  @override
  Widget build(BuildContext context) {
    super.build(context);
    return Column(
      children: [
        _buildSearchBar(),
        Expanded(child: _loading ? _buildLoading() : _buildResults()),
      ],
    );
  }

  Widget _buildSearchBar() {
    return Padding(
      padding: const EdgeInsets.fromLTRB(16, 14, 16, 10),
      child: Row(
        children: [
          Expanded(
            child: TextField(
              controller: _ctrl,
              style: const TextStyle(color: AppColors.text, fontSize: 13),
              onSubmitted: (_) => _search(),
              decoration: const InputDecoration(hintText: 'Search series...'),
            ),
          ),
          const SizedBox(width: 8),
          ElevatedButton(
            onPressed: _search,
            style: ElevatedButton.styleFrom(
              backgroundColor: AppColors.accent,
              foregroundColor: Colors.white,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(12),
              ),
              padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 13),
            ),
            child: const Text('Search', style: TextStyle(fontSize: 13)),
          ),
        ],
      ),
    );
  }

  Widget _buildLoading() =>
      const Center(child: CircularProgressIndicator(color: AppColors.accent));

  Widget _buildResults() {
    if (_results.isEmpty) {
      return const Center(
        child: Text(
          'No results found.',
          style: TextStyle(color: AppColors.muted, fontSize: 13),
        ),
      );
    }
    return CustomScrollView(
      controller: widget.scrollController,
      slivers: [
        SliverPadding(
          padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 4),
          sliver: SliverGrid(
            gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
              crossAxisCount: 2,
              mainAxisSpacing: 10,
              crossAxisSpacing: 10,
              childAspectRatio: 0.55,
            ),
            delegate: SliverChildBuilderDelegate(
              (_, i) => GestureDetector(
                onTap: () => widget.onSelectSeries(_results[i].id),
                child: _SeriesGridCard(series: _results[i]),
              ),
              childCount: _results.length,
            ),
          ),
        ),
        SliverToBoxAdapter(
          child: _PaginationRow(
            page: _page,
            totalPages: _totalPages,
            onPrev: () => _changePage(-1),
            onNext: () => _changePage(1),
          ),
        ),
      ],
    );
  }
}

class _SeriesGridCard extends StatelessWidget {
  final TvSeries series;
  const _SeriesGridCard({required this.series});

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        color: AppColors.surface2,
        borderRadius: BorderRadius.circular(12),
      ),
      clipBehavior: Clip.antiAlias,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Expanded(
            child: NetImage(
              imageUrl(series.posterPath, size: 'w342'),
              width: double.infinity,
            ),
          ),
          Padding(
            padding: const EdgeInsets.fromLTRB(8, 8, 8, 10),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  series.name,
                  maxLines: 2,
                  overflow: TextOverflow.ellipsis,
                  style: const TextStyle(
                    fontSize: 12,
                    fontWeight: FontWeight.w500,
                    color: AppColors.text,
                    height: 1.3,
                  ),
                ),
                const SizedBox(height: 3),
                Text(
                  '★ ${series.voteAverage.toStringAsFixed(1)} · ${series.year}',
                  style: const TextStyle(fontSize: 10, color: AppColors.accent),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}

class _PaginationRow extends StatelessWidget {
  final int page;
  final int totalPages;
  final VoidCallback onPrev;
  final VoidCallback onNext;

  const _PaginationRow({
    required this.page,
    required this.totalPages,
    required this.onPrev,
    required this.onNext,
  });

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 16),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          _PageBtn(label: '← Prev.', enabled: page > 1, onTap: onPrev),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 16),
            child: Text(
              '$page / $totalPages',
              style: const TextStyle(fontSize: 12, color: AppColors.muted),
            ),
          ),
          _PageBtn(label: 'Next. →', enabled: page < totalPages, onTap: onNext),
        ],
      ),
    );
  }
}

class _PageBtn extends StatelessWidget {
  final String label;
  final bool enabled;
  final VoidCallback onTap;

  const _PageBtn({
    required this.label,
    required this.enabled,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: enabled ? onTap : null,
      child: Opacity(
        opacity: enabled ? 1.0 : 0.3,
        child: Container(
          padding: const EdgeInsets.symmetric(horizontal: 14, vertical: 7),
          decoration: BoxDecoration(
            color: AppColors.surface2,
            borderRadius: BorderRadius.circular(8),
            border: Border.all(color: Colors.white12, width: 0.5),
          ),
          child: Text(
            label,
            style: const TextStyle(fontSize: 12, color: AppColors.text),
          ),
        ),
      ),
    );
  }
}
