///
/// @file Config.h
///
/// @brief The header for the Config struct.
///
/// @author
///
/// This file is a part of Ultralight, a next-generation HTML renderer.
///
/// Website: <http://ultralig.ht>
///
/// Copyright (C) 2021 Ultralight, Inc. All rights reserved.
///
#pragma once
#include "../Defines.h"
#include "../String16.h"

namespace ultralight {

///
/// The winding order for front-facing triangles. (Only used when the GPU renderer is used)
///
/// @note  In most 3D engines, there is the concept that triangles have a "front" and a "back". All
///        the front-facing triangles (eg, those that are facing the camera) are rendered, and all
///        back-facing triangles are culled (ignored). The winding-order of the triangle's vertices
///        is used to determine which side is front and back. You should tell Ultralight which
///        winding-order your 3D engine uses.
///
enum FaceWinding {
  ///
  /// Clockwise Winding (Direct3D, etc.)
  ///
  kFaceWinding_Clockwise,

  ///
  /// Counter-Clockwise Winding (OpenGL, etc.)
  ///
  kFaceWinding_CounterClockwise,
};

enum FontHinting {
  ///
  /// Lighter hinting algorithm-- glyphs are slightly fuzzier but better resemble their original
  /// shape. This is achieved by snapping glyphs to the pixel grid only vertically which better
  /// preserves inter-glyph spacing.
  ///
  kFontHinting_Smooth,

  ///
  /// Default hinting algorithm-- offers a good balance between sharpness and shape at smaller font
  /// sizes.
  ///
  kFontHinting_Normal,

  ///
  /// Strongest hinting algorithm-- outputs only black/white glyphs. The result is usually
  /// unpleasant if the underlying TTF does not contain hints for this type of rendering.
  ///
  kFontHinting_Monochrome,
};

///
/// @brief  Configuration settings for Ultralight.
///
/// This is intended to be implemented by users and defined before creating the Renderer. @see
/// Platform::set_config.
///
struct UExport Config {
  ///
  /// The file path to the directory that contains Ultralight's bundled resources (eg, cacert.pem
  /// and other localized resources).
  ///
  String16 resource_path;

  ///
  /// The file path to a writable directory that will be used to store cookies, cached resources,
  /// and other persistent data.
  ///
  String16 cache_path;

  ///
  /// The winding order for front-facing triangles. @see FaceWinding
  ///
  /// Note: This is only used when the GPU renderer is enabled.
  ///
  FaceWinding face_winding = kFaceWinding_CounterClockwise;

  ///
  /// The hinting algorithm to use when rendering fonts. @see FontHinting
  ///
  FontHinting font_hinting = kFontHinting_Normal;

  ///
  /// The gamma to use when compositing font glyphs, change this value to adjust contrast (Adobe and
  /// Apple prefer 1.8, others may prefer 2.2).
  ///
  double font_gamma = 1.8;

  ///
  /// Default user stylesheet. You should set this to your own custom CSS string to define default
  /// styles for various DOM elements, scrollbars, and platform input widgets.
  ///
  String16 user_stylesheet;

  ///
  /// Whether or not we should continuously repaint any Views or compositor layers, regardless if
  /// they are dirty or not. This is mainly used to diagnose painting/shader issues.
  ///
  bool force_repaint = false;

  ///
  /// When a CSS animation is active, the amount of time (in seconds) to wait before triggering
  /// another repaint. Default is 60 Hz.
  ///
  double animation_timer_delay = 1.0 / 60.0;

  ///
  /// When a smooth scroll animation is active, the amount of time (in seconds) to wait before
  /// triggering another repaint. Default is 60 Hz.
  ///
  double scroll_timer_delay = 1.0 / 60.0;

  ///
  /// The amount of time (in seconds) to wait before running the recycler (will attempt to return
  /// excess memory back to the system).
  ///
  double recycle_delay = 4.0;

  ///
  /// Size of WebCore's memory cache in bytes.
  ///
  /// @note  You should increase this if you anticipate handling pages with large resources, Safari
  ///        typically uses 128+ MiB for its cache.
  ///
  uint32_t memory_cache_size = 64 * 1024 * 1024;

  ///
  /// Number of pages to keep in the cache. Defaults to 0 (none).
  ///
  /// @note  Safari typically caches about 5 pages and maintains an on-disk cache to support typical
  ///        web-browsing activities. If you increase this, you should probably increase the memory
  ///        cache size as well.
  ///
  uint32_t page_cache_size = 0;

  ///
  /// JavaScriptCore tries to detect the system's physical RAM size to set reasonable allocation
  /// limits. Set this to anything other than 0 to override the detected value. Size is in bytes.
  ///
  /// This can be used to force JavaScriptCore to be more conservative with its allocation strategy
  /// (at the cost of some performance).
  ///
  uint32_t override_ram_size = 0;

  ///
  /// The minimum size of large VM heaps in JavaScriptCore. Set this to a lower value to make these
  /// heaps start with a smaller initial value.
  ///
  uint32_t min_large_heap_size = 32 * 1024 * 1024;

  ///
  /// The minimum size of small VM heaps in JavaScriptCore. Set this to a lower value to make these
  /// heaps start with a smaller initial value.
  ///
  uint32_t min_small_heap_size = 1 * 1024 * 1024;
};

} // namespace ultralight
