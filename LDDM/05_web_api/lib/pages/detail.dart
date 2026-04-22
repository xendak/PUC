import 'package:flutter/material.dart';
import '../tmdb_service.dart';
import '../theme.dart';
import '../widgets/net_image.dart';

class DetailPage extends StatefulWidget {
  final int? seriesId;
  final TvSeriesDetail? cachedDetail;
  final List<CastMember>? cachedCast;
  final void Function(TvSeriesDetail, List<CastMember>) onDetailLoaded;
  final VoidCallback onBack;

  const DetailPage({
    super.key,
    required this.seriesId,
    required this.cachedDetail,
    required this.cachedCast,
    required this.onDetailLoaded,
    required this.onBack,
  });

  @override
  State<DetailPage> createState() => _DetailPageState();
}

class _DetailPageState extends State<DetailPage> {
  TvSeriesDetail? _detail;
  List<CastMember> _cast = [];
  bool _loading = false;

  @override
  void initState() {
    super.initState();
    _loadDetail();
  }

  @override
  void didUpdateWidget(DetailPage old) {
    super.didUpdateWidget(old);
    if (widget.seriesId != old.seriesId) _loadDetail();
  }

  Future<void> _loadDetail() async {
    if (widget.seriesId == null) return;

    // Try cached images :')
    if (widget.cachedDetail != null &&
        widget.cachedDetail!.id == widget.seriesId) {
      setState(() {
        _detail = widget.cachedDetail;
        _cast = widget.cachedCast ?? [];
      });
      return;
    }

    setState(() => _loading = true);
    final results = await Future.wait([
      TmdbService.getSeriesDetails(widget.seriesId!),
      TmdbService.getSeriesCast(widget.seriesId!),
    ]);

    final detail = results[0] as TvSeriesDetail;
    final cast = results[1] as List<CastMember>;
    widget.onDetailLoaded(detail, cast);

    if (mounted) {
      setState(() {
        _detail = detail;
        _cast = cast;
        _loading = false;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    if (widget.seriesId == null) {
      return const Center(
        child: Text(
          'Pick a series to see in depth details.',
          style: TextStyle(color: AppColors.muted, fontSize: 13),
        ),
      );
    }
    if (_loading || _detail == null) {
      return const Center(
        child: CircularProgressIndicator(color: AppColors.accent),
      );
    }
    return _buildContent(_detail!);
  }

  Widget _buildContent(TvSeriesDetail s) {
    return SingleChildScrollView(
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          // :Back
          Padding(
            padding: const EdgeInsets.fromLTRB(16, 12, 16, 4),
            child: GestureDetector(
              onTap: widget.onBack,
              child: Container(
                padding: const EdgeInsets.symmetric(
                  horizontal: 12,
                  vertical: 6,
                ),
                decoration: BoxDecoration(
                  color: AppColors.surface2,
                  borderRadius: BorderRadius.circular(8),
                  border: Border.all(color: Colors.white12, width: 0.5),
                ),
                child: const Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Icon(Icons.chevron_left, size: 16, color: AppColors.muted),
                    SizedBox(width: 4),
                    Text(
                      'Back',
                      style: TextStyle(fontSize: 12, color: AppColors.muted),
                    ),
                  ],
                ),
              ),
            ),
          ),

          // :Backdrop
          Stack(
            children: [
              NetImage(
                imageUrl(s.backdropPath, size: 'w1280'),
                width: double.infinity,
                height: 180,
              ),
              Positioned(
                bottom: 0,
                left: 0,
                right: 0,
                height: 80,
                child: Container(
                  decoration: const BoxDecoration(
                    gradient: LinearGradient(
                      begin: Alignment.bottomCenter,
                      end: Alignment.topCenter,
                      colors: [AppColors.bg, Colors.transparent],
                    ),
                  ),
                ),
              ),
            ],
          ),

          Padding(
            padding: const EdgeInsets.fromLTRB(16, 0, 16, 24),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Row(
                  crossAxisAlignment: CrossAxisAlignment.end,
                  children: [
                    Transform.translate(
                      offset: const Offset(0, -40),
                      child: NetImage(
                        imageUrl(s.posterPath, size: 'w342'),
                        width: 80,
                        height: 120,
                        borderRadius: BorderRadius.circular(10),
                      ),
                    ),
                    const SizedBox(width: 12),
                    Expanded(
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            s.name,
                            maxLines: 2,
                            overflow: TextOverflow.ellipsis,
                            style: const TextStyle(
                              fontSize: 18,
                              fontWeight: FontWeight.w600,
                              color: AppColors.text,
                              height: 1.2,
                            ),
                          ),
                          if ((s.tagline ?? '').isNotEmpty)
                            Padding(
                              padding: const EdgeInsets.only(top: 4),
                              child: Text(
                                s.tagline!,
                                style: const TextStyle(
                                  fontSize: 11,
                                  color: AppColors.muted,
                                ),
                              ),
                            ),
                        ],
                      ),
                    ),
                  ],
                ),

                // :Genre
                if (s.genres.isNotEmpty || s.status != null)
                  Wrap(
                    spacing: 6,
                    runSpacing: 6,
                    children: [
                      ...s.genres.map((g) => _Chip(label: g, accent: true)),
                      if (s.status != null) _Chip(label: s.status!),
                    ],
                  ),

                const SizedBox(height: 14),

                // :Stats
                Row(
                  children: [
                    _StatBox(
                      value: s.voteAverage.toStringAsFixed(1),
                      label: 'Rating',
                    ),
                    const SizedBox(width: 8),
                    _StatBox(
                      value: '${s.numberOfSeasons ?? '—'}',
                      label: 'Seasons',
                    ),
                    const SizedBox(width: 8),
                    _StatBox(value: s.year, label: 'Year'),
                  ],
                ),

                const SizedBox(height: 14),

                // :Overview
                Text(
                  s.overview.isNotEmpty ? s.overview : 'Info unavailable.',
                  style: const TextStyle(
                    fontSize: 12,
                    color: AppColors.muted,
                    height: 1.7,
                  ),
                ),

                // :Cast
                if (_cast.isNotEmpty) ...[
                  const Padding(
                    padding: EdgeInsets.only(top: 20, bottom: 10),
                    child: Text(
                      'Cast',
                      style: TextStyle(
                        fontSize: 14,
                        fontWeight: FontWeight.w600,
                        color: AppColors.text,
                      ),
                    ),
                  ),
                  SizedBox(
                    height: 100,
                    child: ListView.separated(
                      scrollDirection: Axis.horizontal,
                      itemCount: _cast.take(12).length,
                      separatorBuilder: (_, _) => const SizedBox(width: 8),
                      itemBuilder: (_, i) {
                        final p = _cast[i];
                        return SizedBox(
                          width: 64,
                          child: Column(
                            children: [
                              ClipOval(
                                child: NetImage(
                                  imageUrl(p.profilePath, size: 'w185'),
                                  width: 52,
                                  height: 52,
                                ),
                              ),
                              const SizedBox(height: 5),
                              Text(
                                p.name,
                                maxLines: 2,
                                textAlign: TextAlign.center,
                                style: const TextStyle(
                                  fontSize: 9,
                                  color: AppColors.text,
                                  height: 1.2,
                                ),
                              ),
                              if ((p.character ?? '').isNotEmpty)
                                Text(
                                  p.character!,
                                  maxLines: 1,
                                  textAlign: TextAlign.center,
                                  overflow: TextOverflow.ellipsis,
                                  style: const TextStyle(
                                    fontSize: 8,
                                    color: AppColors.muted,
                                  ),
                                ),
                            ],
                          ),
                        );
                      },
                    ),
                  ),
                ],
              ],
            ),
          ),
        ],
      ),
    );
  }
}

class _Chip extends StatelessWidget {
  final String label;
  final bool accent;
  const _Chip({required this.label, this.accent = false});

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.symmetric(horizontal: 9, vertical: 3),
      decoration: BoxDecoration(
        color: accent ? AppColors.genreChipBg : AppColors.surface2,
        borderRadius: BorderRadius.circular(100),
        border: Border.all(
          color: accent ? AppColors.genreChipBorder : Colors.white12,
          width: 0.8,
        ),
      ),
      child: Text(
        label,
        style: TextStyle(
          fontSize: 10,
          color: accent ? AppColors.accent : AppColors.muted,
        ),
      ),
    );
  }
}

class _StatBox extends StatelessWidget {
  final String value;
  final String label;
  const _StatBox({required this.value, required this.label});

  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Container(
        padding: const EdgeInsets.symmetric(vertical: 10),
        decoration: BoxDecoration(
          color: AppColors.surface2,
          borderRadius: BorderRadius.circular(10),
        ),
        child: Column(
          children: [
            Text(
              value,
              style: const TextStyle(
                fontSize: 16,
                fontWeight: FontWeight.w600,
                color: AppColors.accent,
              ),
            ),
            const SizedBox(height: 2),
            Text(
              label,
              style: const TextStyle(fontSize: 9, color: AppColors.muted),
            ),
          ],
        ),
      ),
    );
  }
}
