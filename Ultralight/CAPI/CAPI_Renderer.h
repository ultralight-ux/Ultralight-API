#ifndef ULTRALIGHT_CAPI_RENDERER_H
#define ULTRALIGHT_CAPI_RENDERER_H

#include <Ultralight/CAPI/CAPI_Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Renderer
 *****************************************************************************/

///
/// Create the Ultralight Renderer directly.
///
/// Unlike ulCreateApp(), this does not use any native windows for drawing and allows you to manage
/// your own runloop and painting. This method is recommended for those wishing to integrate the
/// library into a game.
///
/// This singleton manages the lifetime of all Views and coordinates all painting, rendering,
/// network requests, and event dispatch.
///
/// You should only call this once per process lifetime.
///
/// You shoud set up your platform handlers (eg, ulPlatformSetLogger, ulPlatformSetFileSystem, etc.)
/// before calling this.
///
/// You will also need to define a font loader before calling this-- as of this writing (v1.2) the
/// only way to do this in C API is by calling ulEnablePlatformFontLoader() (available in
/// <AppCore/CAPI.h>).
///
/// @NOTE:  You should not call this if you are using ulCreateApp(), it creates its own renderer and
///         provides default implementations for various platform handlers automatically.
///
ULExport ULRenderer ulCreateRenderer(ULConfig config);

///
/// Destroy the renderer.
///
ULExport void ulDestroyRenderer(ULRenderer renderer);

///
/// Update timers and dispatch internal callbacks (JavaScript and network).
///
ULExport void ulUpdate(ULRenderer renderer);

///
/// Render all active Views.
///
ULExport void ulRender(ULRenderer renderer);

///
/// Attempt to release as much memory as possible. Don't call this from any callbacks or driver
/// code.
///
ULExport void ulPurgeMemory(ULRenderer renderer);

///
/// Print detailed memory usage statistics to the log. (@see ulPlatformSetLogger)
///
ULExport void ulLogMemoryUsage(ULRenderer renderer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_RENDERER_H