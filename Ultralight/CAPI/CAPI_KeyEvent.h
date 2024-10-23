/**************************************************************************************************
 *  This file is a part of Ultralight.                                                            *
 *                                                                                                *
 *  See <https://ultralig.ht> for licensing and more.                                             *
 *                                                                                                *
 *  (C) 2024 Ultralight, Inc.                                                                     *
 **************************************************************************************************/

///
/// @file CAPI_KeyEvent.h
///
/// Key event interface.
///
/// `#include <Ultralight/CAPI/CAPI_KeyEvent.h>`
///
/// This file defines the C API for various key events.
///
#ifndef ULTRALIGHT_CAPI_KEYEVENT_H
#define ULTRALIGHT_CAPI_KEYEVENT_H

#include <Ultralight/CAPI/CAPI_Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Key Event
 ******************************************************************************/

///
/// Create a key event, see KeyEvent in the C++ API for help with the parameters.
///
ULExport ULKeyEvent ulCreateKeyEvent(ULKeyEventType type, unsigned int modifiers,
                                     int virtual_key_code, int native_key_code, ULString text,
                                     ULString unmodified_text, bool is_keypad, bool is_auto_repeat,
                                     bool is_system_key);

#ifdef _WIN32
///
/// Create a key event from native Windows event.
///
ULExport ULKeyEvent ulCreateKeyEventWindows(ULKeyEventType type, uintptr_t wparam, intptr_t lparam,
                                            bool is_system_key);
#endif

#ifdef __OBJC__
///
/// Create a key event from native macOS event.
///
ULExport ULKeyEvent ulCreateKeyEventMacOS(NSEvent* evt);
#endif

///
/// Destroy a key event.
///
ULExport void ulDestroyKeyEvent(ULKeyEvent evt);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_KEYEVENT_H