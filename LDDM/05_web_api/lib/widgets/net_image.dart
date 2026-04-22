import 'package:flutter/material.dart';
import 'package:cached_network_image/cached_network_image.dart';
import '../theme.dart';

class NetImage extends StatelessWidget {
  final String? url;
  final double? width;
  final double? height;
  final BoxFit fit;
  final BorderRadius? borderRadius;

  const NetImage(
    this.url, {
    super.key,
    this.width,
    this.height,
    this.fit = BoxFit.cover,
    this.borderRadius,
  });

  @override
  Widget build(BuildContext context) {
    final child = (url != null && url!.isNotEmpty)
        ? CachedNetworkImage(
            imageUrl: url!,
            width: width,
            height: height,
            fit: fit,
            placeholder: (_, _) => Container(
              width: width,
              height: height,
              color: AppColors.surface2,
            ),
            errorWidget: (_, _, _) => Container(
              width: width,
              height: height,
              color: AppColors.surface2,
            ),
          )
        : Container(width: width, height: height, color: AppColors.surface2);

    return borderRadius != null
        ? ClipRRect(borderRadius: borderRadius!, child: child)
        : child;
  }
}
