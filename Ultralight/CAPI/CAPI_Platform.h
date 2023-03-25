#ifndef ULTRALIGHT_CAPI_PLATFORM_H
#define ULTRALIGHT_CAPI_PLATFORM_H

#include <Ultralight/CAPI/CAPI_Defines.h>
#include <Ultralight/CAPI/CAPI_Logger.h>
#include <Ultralight/CAPI/CAPI_FileSystem.h>
#include <Ultralight/CAPI/CAPI_Surface.h>
#include <Ultralight/CAPI/CAPI_GPUDriver.h>
#include <Ultralight/CAPI/CAPI_Clipboard.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Platform
 *****************************************************************************/

///
/// Set a custom Logger implementation.
///
/// This is used to log debug messages to the console or to a log file.
///
/// You should call this before ulCreateRenderer() or ulCreateApp().
///
/// @note  ulCreateApp() will use the default logger if you never call this.
///
/// @note  If you're not using ulCreateApp(), (eg, using ulCreateRenderer()) you can still use the
///        default logger by calling ulEnableDefaultLogger() (@see <AppCore/CAPI.h>)
///
ULExport void ulPlatformSetLogger(ULLogger logger);

///
/// Set a custom FileSystem implementation.
///
/// This is used for loading File URLs (eg, <file:///page.html>). If you don't call this, and are
/// not using ulCreateApp() or ulEnablePlatformFileSystem(), you will not be able to load any File
/// URLs.
///
/// You should call this before ulCreateRenderer() or ulCreateApp().
///
/// @note  ulCreateApp() will use the default platform file system if you never call this.
///
/// @note  If you're not using ulCreateApp(), (eg, using ulCreateRenderer()) you can still use the
///        default platform file system by calling ulEnablePlatformFileSystem()'
///        (@see <AppCore/CAPI.h>)
///
ULExport void ulPlatformSetFileSystem(ULFileSystem file_system);

///
/// Set a custom Surface implementation.
///
/// This can be used to wrap a platform-specific GPU texture, Windows DIB, macOS CGImage, or any
/// other pixel buffer target for display on screen.
///
/// By default, the library uses a bitmap surface for all surfaces but you can override this by
/// providing your own surface definition here.
///
/// You should call this before ulCreateRenderer() or ulCreateApp().
///
ULExport void ulPlatformSetSurfaceDefinition(ULSurfaceDefinition surface_definition);

///
/// Set a custom GPUDriver implementation.
///
/// This should be used if you have enabled the GPU renderer in the Config and are using
/// ulCreateRenderer() (which does not provide its own GPUDriver implementation).
///
/// The GPUDriver interface is used by the library to dispatch GPU calls to your native GPU context
/// (eg, D3D11, Metal, OpenGL, Vulkan, etc.) There are reference implementations for this interface
/// in the AppCore repo.
///
/// You should call this before ulCreateRenderer().
///
ULExport void ulPlatformSetGPUDriver(ULGPUDriver gpu_driver);

///
/// Set a custom Clipboard implementation.
///
/// This should be used if you are using ulCreateRenderer() (which does not provide its own
/// clipboard implementation).
///
/// The Clipboard interface is used by the library to make calls to the system's native clipboard
/// (eg, cut, copy, paste).
///
/// You should call this before ulCreateRenderer().
///
ULExport void ulPlatformSetClipboard(ULClipboard clipboard);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_PLATFORM_H