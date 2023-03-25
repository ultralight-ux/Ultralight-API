#ifndef ULTRALIGHT_CAPI_CONFIG_H
#define ULTRALIGHT_CAPI_CONFIG_H

#include <Ultralight/CAPI/CAPI_Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Config
 *****************************************************************************/

///
/// Create config with default values (see <Ultralight/platform/Config.h>).
///
ULExport ULConfig ulCreateConfig();

///
/// Destroy config.
///
ULExport void ulDestroyConfig(ULConfig config);

///
/// Set the file path to a writable directory that will be used to store cookies, cached resources, and other persistent data.
///
/// Files are only written to disk when using a persistent Session.
///
ULExport void ulConfigSetCachePath(ULConfig config, ULString cache_path);

///
/// The library loads bundled resources (eg, cacert.pem and other localized resources) from the
/// FileSystem API (eg, `file:///resources/cacert.pem`). You can customize the prefix to use when
/// loading resource URLs by modifying this setting. (Default = "resources/")
///
ULExport void ulConfigSetResourcePathPrefix(ULConfig config, ULString resource_path_prefix);

///
/// The winding order for front-facing triangles. (Default = kFaceWinding_CounterClockwise)
///
/// Note: This is only used with custom GPUDrivers
///
ULExport void ulConfigSetFaceWinding(ULConfig config, ULFaceWinding winding);

///
/// The hinting algorithm to use when rendering fonts. (Default = kFontHinting_Normal)
/// @see ULFontHinting
///
ULExport void ulConfigSetFontHinting(ULConfig config, ULFontHinting font_hinting);

///
/// The gamma to use when compositing font glyphs, change this value to adjust contrast (Adobe and
/// Apple prefer 1.8, others may prefer 2.2). (Default = 1.8)
///
ULExport void ulConfigSetFontGamma(ULConfig config, double font_gamma);

///
/// Set user stylesheet (CSS) (Default = Empty).
///
ULExport void ulConfigSetUserStylesheet(ULConfig config, ULString css_string);

///
/// Set whether or not we should continuously repaint any Views or compositor layers, regardless if
/// they are dirty or not. This is mainly used to diagnose painting/shader issues. (Default = False)
///
ULExport void ulConfigSetForceRepaint(ULConfig config, bool enabled);

///
/// Set the amount of time to wait before triggering another repaint when a CSS animation is active.
/// (Default = 1.0 / 60.0)
///
ULExport void ulConfigSetAnimationTimerDelay(ULConfig config, double delay);

///
/// When a smooth scroll animation is active, the amount of time (in seconds) to wait before
/// triggering another repaint. Default is 60 Hz.
///
ULExport void ulConfigSetScrollTimerDelay(ULConfig config, double delay);

///
/// The amount of time (in seconds) to wait before running the recycler (will attempt to return
/// excess memory back to the system). (Default = 4.0)
///
ULExport void ulConfigSetRecycleDelay(ULConfig config, double delay);

///
/// Set the size of WebCore's memory cache for decoded images, scripts, and other assets in bytes.
/// (Default = 64 * 1024 * 1024)
///
ULExport void ulConfigSetMemoryCacheSize(ULConfig config, unsigned int size);

///
/// Set the number of pages to keep in the cache. (Default = 0)
///
ULExport void ulConfigSetPageCacheSize(ULConfig config, unsigned int size);

///
/// JavaScriptCore tries to detect the system's physical RAM size to set reasonable allocation
/// limits. Set this to anything other than 0 to override the detected value. Size is in bytes.
///
/// This can be used to force JavaScriptCore to be more conservative with its allocation strategy
/// (at the cost of some performance).
///
ULExport void ulConfigSetOverrideRAMSize(ULConfig config, unsigned int size);

///
/// The minimum size of large VM heaps in JavaScriptCore. Set this to a lower value to make these
/// heaps start with a smaller initial value.
///
ULExport void ulConfigSetMinLargeHeapSize(ULConfig config, unsigned int size);

///
/// The minimum size of small VM heaps in JavaScriptCore. Set this to a lower value to make these
/// heaps start with a smaller initial value.
///
ULExport void ulConfigSetMinSmallHeapSize(ULConfig config, unsigned int size);

///
/// The number of threads to use in the Renderer (for parallel painting on the CPU, etc.).
///
/// You can set this to a certain number to limit the number of threads to spawn.
///
/// @note  If this value is 0 (the default), the number of threads will be determined at runtime
///        using the following formula:
///
///        max(PhysicalProcessorCount() - 1, 1)
///
ULExport void ulConfigSetNumRendererThreads(ULConfig config, unsigned int num_renderer_threads);

///
/// The max amount of time (in seconds) to allow Renderer::Update to run per call. The library will
/// attempt to throttle timers and/or reschedule work if this time budget is exceeded. (Default =
/// 0.01)
///
ULExport void ulConfigSetMaxUpdateTime(ULConfig config, double max_update_time);

///
/// The alignment (in bytes) of the BitmapSurface when using the CPU renderer.
///
/// The underlying bitmap associated with each BitmapSurface will have row_bytes padded to reach
/// this alignment.
///
/// Aligning the bitmap helps improve performance when using the CPU renderer. Determining the
/// proper value to use depends on the CPU architecture and max SIMD instruction set used.
///
/// We generally target the 128-bit SSE2 instruction set across most PC platforms so '16' is a safe
/// value to use.
///
/// You can set this to '0' to perform no padding (row_bytes will always be width * 4) at a slight
/// cost to performance.
///
/// (Default = 16)
///
ULExport void ulConfigSetBitmapAlignment(ULConfig config, double bitmap_alignment);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_CONFIG_H