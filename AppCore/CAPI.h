/**************************************************************************************************
 *  This file is a part of Ultralight.                                                            *
 *                                                                                                *
 *  See <https://ultralig.ht> for licensing and more.                                             *
 *                                                                                                *
 *  (C) 2024 Ultralight, Inc.                                                                     *
 **************************************************************************************************/

///
/// @file AppCore/CAPI.h
///
/// AppCore API interface.
///
/// `#include <AppCore/CAPI.h>`
///
/// AppCore is a convenient windowing system for desktop platforms built on top of the
/// Ultralight renderer.
/// 
/// It automatically sets up the Renderer, creates a run loop, and handles all window creation,
/// painting, and platform-specific operations for you.
/// 
/// ## Creating the App
/// 
/// Call ulCreateApp() to initialize the library and create the App singleton:
///
/// ```
/// // Create the App using default config and settings
/// ULApp app = ulCreateApp(NULL, NULL);
/// ```
///
/// ## Creating a Window
///
/// Call ulCreateWindow() to create one or more windows during the lifetime of your app:
///
/// ```
/// ULWindow window = ulCreateWindow(ulAppGetMainMonitor(app), 1024, 768, false,
///                                  kWindowFlags_Titled | kWindowFlags_Resizable);
/// ```
///
/// ## Creating an Overlay in a Window
///
/// Each Window can have one or more Overlay instances. Overlays are used to display web-based
/// content in a portion of the window.
///
/// Call ulCreateOverlay() to create an overlay in a window:
///
/// ```
/// ULOverlay overlay = ulCreateOverlay(window, 1024, 768, 0, 0);
/// ```
///
/// Each Overlay has a View instance that you can use to load web content into:
///
/// ```
/// ULString url = ulCreateString("https://google.com");
/// ULView view = ulOverlayGetView(overlay);
/// ulViewLoadURL(view, url);
/// ulDestroyString(url);
/// ```
///
/// ## Running the App
///
/// Call ulAppRun() to start the main run loop:
///
/// ```
/// #include <AppCore/CAPI.h>
///
/// int main() {
///   // Initialize app, window, overlay, etc. here...
///
///   ulAppRun(app);
///
///   ulDestroyApp(app);
///   return 0;
/// }
/// ```
///
#ifndef APPCORE_CAPI_H
#define APPCORE_CAPI_H

#include <Ultralight/CAPI.h>

#if defined(ULTRALIGHT_STATIC_BUILD)
#  define ACExport 
#else
#  if defined(__WIN32__) || defined(_WIN32)
#    if defined(APPCORE_IMPLEMENTATION)
#      define ACExport __declspec(dllexport)
#    else
#      define ACExport __declspec(dllimport)
#    endif
#  else
#    define ACExport __attribute__((visibility("default")))
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct C_Settings* ULSettings;
typedef struct C_App* ULApp;
typedef struct C_Window* ULWindow;
typedef struct C_Monitor* ULMonitor;
typedef struct C_Overlay* ULOverlay;

///
/// Window creation flags. @see Window::Create
///
typedef enum {
  kWindowFlags_Borderless  = 1 << 0,
  kWindowFlags_Titled      = 1 << 1,
  kWindowFlags_Resizable   = 1 << 2,
  kWindowFlags_Maximizable = 1 << 3,
  kWindowFlags_Hidden      = 1 << 4,
} ULWindowFlags;

///
/// Create settings with default values (see <AppCore/App.h>).
///
ACExport ULSettings ulCreateSettings();

///
/// Destroy settings.
///
ACExport void ulDestroySettings(ULSettings settings);

///
/// Set the name of the developer of this app.
///
/// This is used to generate a unique path to store local application data
/// on the user's machine.
///
/// Default is "MyCompany"
///
ACExport void ulSettingsSetDeveloperName(ULSettings settings, ULString name);

///
/// Set the name of this app.
///
/// This is used to generate a unique path to store local application data
/// on the user's machine.
///
/// Default is "MyApp"
///
ACExport void ulSettingsSetAppName(ULSettings settings, ULString name);

///
/// Set the root file path for our file system, you should set this to the
/// relative path where all of your app data is.
///
/// This will be used to resolve all file URLs, eg file:///page.html
///
/// @note  The default path is "./assets/"
///        
///        This relative path is resolved using the following logic:
///         - Windows: relative to the executable path
///         - Linux:   relative to the executable path
///         - macOS:   relative to YourApp.app/Contents/Resources/
///
ACExport void ulSettingsSetFileSystemPath(ULSettings settings, ULString path);

///
/// Set whether or not we should load and compile shaders from the file system
/// (eg, from the /shaders/ path, relative to file_system_path).
///
/// If this is false (the default), we will instead load pre-compiled shaders
/// from memory which speeds up application startup time.
///
ACExport void ulSettingsSetLoadShadersFromFileSystem(ULSettings settings,
                                                     bool enabled);

///
/// We try to use the GPU renderer when a compatible GPU is detected.
///
/// Set this to true to force the engine to always use the CPU renderer.
///
ACExport void ulSettingsSetForceCPURenderer(ULSettings settings,
                                            bool force_cpu);
///
/// Create the App singleton.
///
/// @param  settings  Settings to customize App runtime behavior. You can pass
///                   NULL for this parameter to use default settings.
///
/// @param  config  Config options for the Ultralight renderer. You can pass
///                 NULL for this parameter to use default config.
///
/// @note  You should only create one of these per application lifetime.
///        
/// @note  Certain Config options may be overridden during App creation,
///        most commonly Config::face_winding and Config::device_scale_hint.
///
ACExport ULApp ulCreateApp(ULSettings settings, ULConfig config);

///
/// Destroy the App instance.
///
ACExport void ulDestroyApp(ULApp app);

typedef void
(*ULUpdateCallback) (void* user_data);

///
/// Set a callback for whenever the App updates. You should update all app
/// logic here.
///
/// @note  This event is fired right before the run loop calls
///        Renderer::Update and Renderer::Render.
///
ACExport void ulAppSetUpdateCallback(ULApp app, ULUpdateCallback callback,
                                     void* user_data);

///
/// Whether or not the App is running.
///
ACExport bool ulAppIsRunning(ULApp app);

///
/// Get the main monitor (this is never NULL).
///
/// @note  We'll add monitor enumeration later.
///
ACExport ULMonitor ulAppGetMainMonitor(ULApp app);

///
/// Get the underlying Renderer instance.
///
ACExport ULRenderer ulAppGetRenderer(ULApp app);

///
/// Run the main loop.
///
ACExport void ulAppRun(ULApp app);

///
/// Quit the application.
///
ACExport void ulAppQuit(ULApp app);

///
/// Get the monitor's DPI scale (1.0 = 100%).
///
ACExport double ulMonitorGetScale(ULMonitor monitor);

///
/// Get the width of the monitor (in pixels).
///
ACExport unsigned int ulMonitorGetWidth(ULMonitor monitor);

///
/// Get the height of the monitor (in pixels).
///
ACExport unsigned int ulMonitorGetHeight(ULMonitor monitor);

///
/// Create a new Window.
///
/// @param  monitor       The monitor to create the Window on.
///
/// @param  width         The width (in screen coordinates).
///
/// @param  height        The height (in screen coordinates).
///
/// @param  fullscreen    Whether or not the window is fullscreen.
///
/// @param  window_flags  Various window flags.
///
ACExport ULWindow ulCreateWindow(ULMonitor monitor, unsigned int width,
	                               unsigned int height, bool fullscreen,
                                 unsigned int window_flags);

///
/// Destroy a Window.
///
ACExport void ulDestroyWindow(ULWindow window);

typedef void
(*ULCloseCallback) (void* user_data, ULWindow window);

///
/// Set a callback to be notified when a window closes.
///
ACExport void ulWindowSetCloseCallback(ULWindow window,
                                       ULCloseCallback callback,
                                       void* user_data);

typedef void
(*ULResizeCallback) (void* user_data, ULWindow window, unsigned int width, unsigned int height);

///
/// Set a callback to be notified when a window resizes
/// (parameters are passed back in pixels).
///
ACExport void ulWindowSetResizeCallback(ULWindow window,
                                        ULResizeCallback callback,
                                        void* user_data);

///
/// Get window width (in screen coordinates).
///
ACExport unsigned int ulWindowGetScreenWidth(ULWindow window);

///
/// Get window width (in pixels).
///
ACExport unsigned int ulWindowGetWidth(ULWindow window);

///
/// Get window height (in screen coordinates).
///
ACExport unsigned int ulWindowGetScreenHeight(ULWindow window);

///
/// Get window height (in pixels).
///
ACExport unsigned int ulWindowGetHeight(ULWindow window);

///
/// Move the window to a new position (in screen coordinates) relative to the top-left of the
/// monitor area.
///
ACExport void ulWindowMoveTo(ULWindow window, int x, int y);

///
/// Move the window to the center of the monitor.
///
ACExport void ulWindowMoveToCenter(ULWindow);

///
/// Get the x-position of the window (in screen coordinates) relative to the top-left of the
/// monitor area.
///
ACExport int ulWindowGetPositionX(ULWindow window);

///
/// Get the y-position of the window (in screen coordinates) relative to the top-left of the
/// monitor area.
///
ACExport int ulWindowGetPositionY(ULWindow window);

///
/// Get whether or not a window is fullscreen.
///
ACExport bool ulWindowIsFullscreen(ULWindow window);

///
/// Get the DPI scale of a window.
///
ACExport double ulWindowGetScale(ULWindow window);

///
/// Set the window title.
///
ACExport void ulWindowSetTitle(ULWindow window, const char* title);

///
/// Set the cursor for a window.
///
ACExport void ulWindowSetCursor(ULWindow window, ULCursor cursor);

///
/// Show the window (if it was previously hidden).
///
ACExport void ulWindowShow(ULWindow window);

///
/// Hide the window.
///
ACExport void ulWindowHide(ULWindow window);

///
/// Whether or not the window is currently visible (not hidden).
///
ACExport bool ulWindowIsVisible(ULWindow window);

///
/// Close a window.
///
ACExport void ulWindowClose(ULWindow window);

///
/// Convert screen coordinates to pixels using the current DPI scale.
///
ACExport int ulWindowScreenToPixels(ULWindow window, int val);

///
/// Convert pixels to screen coordinates using the current DPI scale.
///
ACExport int ulWindowPixelsToScreen(ULWindow window, int val);

///
/// Get the underlying native window handle.
///
/// @note This is:  - HWND on Windows
///                 - NSWindow* on macOS
///                 - GLFWwindow* on Linux
///
ACExport void* ulWindowGetNativeHandle(ULWindow window);

///
/// Create a new Overlay.
///
/// @param  window  The window to create the Overlay in.
///
/// @param  width   The width in pixels.
///
/// @param  height  The height in pixels.
///
/// @param  x       The x-position (offset from the left of the Window), in
///                 pixels.
///
/// @param  y       The y-position (offset from the top of the Window), in
///                 pixels.
///
/// @note  Each Overlay is essentially a View and an on-screen quad. You should
///        create the Overlay then load content into the underlying View.
///
ACExport ULOverlay ulCreateOverlay(ULWindow window, unsigned int width,
                                   unsigned int height, int x, int y);

///
/// Create a new Overlay, wrapping an existing View.
///
/// @param  window  The window to create the Overlay in. (we currently only
///                 support one window per application)
///
/// @param  view    The View to wrap (will use its width and height).
///
/// @param  x       The x-position (offset from the left of the Window), in
///                 pixels.
///
/// @param  y       The y-position (offset from the top of the Window), in
///                 pixels.
///
/// @note  Each Overlay is essentially a View and an on-screen quad. You should
///        create the Overlay then load content into the underlying View.
///
ACExport ULOverlay ulCreateOverlayWithView(ULWindow window, ULView view, 
                                           int x, int y);

///
/// Destroy an overlay.
///
ACExport void ulDestroyOverlay(ULOverlay overlay);

///
/// Get the underlying View.
///
ACExport ULView ulOverlayGetView(ULOverlay overlay);

///
/// Get the width (in pixels).
///
ACExport unsigned int ulOverlayGetWidth(ULOverlay overlay);

///
/// Get the height (in pixels).
///
ACExport unsigned int ulOverlayGetHeight(ULOverlay overlay);

///
/// Get the x-position (offset from the left of the Window), in pixels.
///
ACExport int ulOverlayGetX(ULOverlay overlay);

///
/// Get the y-position (offset from the top of the Window), in pixels.
///
ACExport int ulOverlayGetY(ULOverlay overlay);

///
/// Move the overlay to a new position (in pixels).
///
ACExport void ulOverlayMoveTo(ULOverlay overlay, int x, int y);

///
/// Resize the overlay (and underlying View), dimensions should be
/// specified in pixels.
///
ACExport void ulOverlayResize(ULOverlay overlay, unsigned int width,
                              unsigned int height);

///
/// Whether or not the overlay is hidden (not drawn).
///
ACExport bool ulOverlayIsHidden(ULOverlay overlay);

///
/// Hide the overlay (will no longer be drawn).
///
ACExport void ulOverlayHide(ULOverlay overlay);

///
/// Show the overlay.
///
ACExport void ulOverlayShow(ULOverlay overlay);

///
/// Whether or not an overlay has keyboard focus.
///
ACExport bool ulOverlayHasFocus(ULOverlay overlay);

///
/// Grant this overlay exclusive keyboard focus.
///
ACExport void ulOverlayFocus(ULOverlay overlay);

///
/// Remove keyboard focus.
///
ACExport void ulOverlayUnfocus(ULOverlay overlay);

/******************************************************************************
 * Platform
 *****************************************************************************/

///
/// This is only needed if you are not calling ulCreateApp().
///
/// Initializes the platform font loader and sets it as the current FontLoader.
///
ACExport void ulEnablePlatformFontLoader();

///
/// This is only needed if you are not calling ulCreateApp().
///
/// Initializes the platform file system (needed for loading file:/// URLs) and
/// sets it as the current FileSystem.
///
/// You can specify a base directory path to resolve relative paths against.
///
ACExport void ulEnablePlatformFileSystem(ULString base_dir);

///
/// This is only needed if you are not calling ulCreateApp().
///
/// Initializes the default logger (writes the log to a file).
///
/// You should specify a writable log path to write the log to 
/// for example "./ultralight.log".
///
ACExport void ulEnableDefaultLogger(ULString log_path);

#ifdef __cplusplus
}
#endif

#endif // APPCORE_CAPI_H
