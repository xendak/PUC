import 'package:flutter/material.dart';
import 'theme.dart';
import 'tmdb_service.dart';
import 'widgets/header.dart';
import 'widgets/footer.dart';
import 'pages/home.dart';
import 'pages/explore.dart';
import 'pages/detail.dart';

void main() => runApp(const TmdbApp());

class TmdbApp extends StatelessWidget {
  const TmdbApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Series Portal',
      debugShowCheckedModeBanner: false,
      theme: buildTheme(),
      home: const RootScreen(),
    );
  }
}

class RootScreen extends StatefulWidget {
  const RootScreen({super.key});

  @override
  State<RootScreen> createState() => _RootScreenState();
}

class _RootScreenState extends State<RootScreen> {
  int _tabIndex = 0;

  final _exploreKey = ExplorePage.createKey();

  int? _lastDetailId;
  TvSeriesDetail? _cachedDetail;
  List<CastMember> _cachedCast = [];

  final _exploreScrollCtrl = ScrollController();
  String _exploreQuery = '';
  int _explorePage = 1;
  int _exploreTotalPages = 1;
  List<TvSeries> _exploreResults = [];

  @override
  void dispose() {
    _exploreScrollCtrl.dispose();
    super.dispose();
  }

  void _openDetail(int id) {
    setState(() {
      _lastDetailId = id;
      _tabIndex = 2;
    });
  }

  void _headerSearch(String query) {
    setState(() => _tabIndex = 1);
    WidgetsBinding.instance.addPostFrameCallback((_) {
      _exploreKey.currentState?.searchFromOutside(query);
    });
  }

  void _goBack() {
    setState(() => _tabIndex = _exploreResults.isNotEmpty ? 1 : 0);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppHeader(onSearch: _headerSearch),
      body: IndexedStack(
        index: _tabIndex,
        children: [
          // :Home
          HomePage(onSelectSeries: _openDetail),

          // :Explore
          ExplorePage(
            key: _exploreKey,
            scrollController: _exploreScrollCtrl,
            initialQuery: _exploreQuery,
            initialPage: _explorePage,
            initialTotalPages: _exploreTotalPages,
            initialResults: _exploreResults,
            onQueryChange: (q) => _exploreQuery = q,
            onPageChange: (p) => _explorePage = p,
            onTotalPagesChange: (t) => _exploreTotalPages = t,
            onResultsChange: (r) => _exploreResults = r,
            onSelectSeries: _openDetail,
          ),

          // :Detail
          DetailPage(
            seriesId: _lastDetailId,
            cachedDetail: _cachedDetail?.id == _lastDetailId
                ? _cachedDetail
                : null,
            cachedCast: _cachedDetail?.id == _lastDetailId ? _cachedCast : null,
            onDetailLoaded: (d, c) {
              _cachedDetail = d;
              _cachedCast = c;
            },
            onBack: _goBack,
          ),
        ],
      ),
      bottomNavigationBar: AppFooter(
        currentIndex: _tabIndex,
        detailEnabled: _lastDetailId != null,
        onTap: (i) => setState(() => _tabIndex = i),
      ),
    );
  }
}
