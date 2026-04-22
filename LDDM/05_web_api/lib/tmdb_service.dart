import 'dart:convert';
import 'package:http/http.dart' as http;

const _apiKey = '2fcf24d155701ad465c7d59c7b0e91f1';
const _base = 'https://api.themoviedb.org/3';
const _imgBase = 'https://image.tmdb.org/t/p';

String imageUrl(String? path, {String size = 'w500'}) {
  if (path == null || path.isEmpty) return '';
  return '$_imgBase/$size$path';
}

Future<Map<String, dynamic>> _get(
  String path, [
  Map<String, String>? extra,
]) async {
  final params = {'api_key': _apiKey, 'language': 'en-US', ...?extra};
  final uri = Uri.parse('$_base$path').replace(queryParameters: params);
  final res = await http.get(uri);
  if (res.statusCode != 200) throw Exception('HTTP ${res.statusCode}');
  return jsonDecode(res.body) as Map<String, dynamic>;
}

class TvSeries {
  final int id;
  final String name;
  final String? posterPath;
  final String? backdropPath;
  final String overview;
  final double voteAverage;
  final String? firstAirDate;

  TvSeries.fromJson(Map<String, dynamic> j)
    : id = j['id'],
      name = j['name'] ?? '',
      posterPath = j['poster_path'],
      backdropPath = j['backdrop_path'],
      overview = j['overview'] ?? '',
      voteAverage = (j['vote_average'] as num?)?.toDouble() ?? 0,
      firstAirDate = j['first_air_date'];

  String get year => firstAirDate != null && firstAirDate!.length >= 4
      ? firstAirDate!.substring(0, 4)
      : '—';
}

class TvSeriesDetail extends TvSeries {
  final String? tagline;
  final String? originalName;
  final String? status;
  final int? numberOfSeasons;
  final List<String> genres;

  TvSeriesDetail.fromJson(super.j)
    : tagline = j['tagline'],
      originalName = j['original_name'],
      status = j['status'],
      numberOfSeasons = j['number_of_seasons'],
      genres =
          (j['genres'] as List?)?.map((g) => g['name'] as String).toList() ??
          [],
      super.fromJson();
}

class CastMember {
  final String name;
  final String? character;
  final String? profilePath;

  CastMember.fromJson(Map<String, dynamic> j)
    : name = j['name'] ?? '',
      character = j['character'],
      profilePath = j['profile_path'];
}

class TmdbService {
  static Future<({List<TvSeries> results, int totalPages})> getPopularSeries({
    int page = 1,
  }) async {
    final data = await _get('/discover/tv', {
      'sort_by': 'vote_average.desc',
      'vote_count.gte': '200',
      'include_adult': 'false',
      'page': '$page',
    });
    return (
      results: (data['results'] as List)
          .map((j) => TvSeries.fromJson(j))
          .toList(),
      totalPages: (data['total_pages'] as int?) ?? 1,
    );
  }

  static Future<({List<TvSeries> results, int totalPages})> getNewSeries({
    int page = 1,
  }) async {
    final today = DateTime.now().toIso8601String().split('T').first;
    final data = await _get('/discover/tv', {
      'sort_by': 'first_air_date.desc',
      'include_adult': 'false',
      'first_air_date.lte': today,
      'vote_count.gte': '1',
      'page': '$page',
    });
    return (
      results: (data['results'] as List)
          .map((j) => TvSeries.fromJson(j))
          .toList(),
      totalPages: (data['total_pages'] as int?) ?? 1,
    );
  }

  static Future<({List<TvSeries> results, int totalPages})> searchSeries(
    String query, {
    int page = 1,
  }) async {
    final data = await _get('/search/tv', {'query': query, 'page': '$page'});
    return (
      results: (data['results'] as List)
          .map((j) => TvSeries.fromJson(j))
          .toList(),
      totalPages: (data['total_pages'] as int?) ?? 1,
    );
  }

  static Future<TvSeriesDetail> getSeriesDetails(int id) async {
    final data = await _get('/tv/$id');
    return TvSeriesDetail.fromJson(data);
  }

  static Future<List<CastMember>> getSeriesCast(int id) async {
    final data = await _get('/tv/$id/credits');
    return (data['cast'] as List).map((j) => CastMember.fromJson(j)).toList();
  }
}
