/**************************************************************************************************
 *  This file is a part of Ultralight.                                                            *
 *                                                                                                *
 *  See <https://ultralig.ht> for licensing and more.                                             *
 *                                                                                                *
 *  (C) 2024 Ultralight, Inc.                                                                     *
 **************************************************************************************************/
#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/KeyCodes.h>
#include <Ultralight/String.h>
#ifdef __OBJC__
#import <AppKit/NSEvent.h>
#endif

namespace ultralight {

///
/// Keyboard event representing a change in keyboard state.
///
/// @see  View::FireKeyEvent
///
class UExport KeyEvent {
 public:
  ///
  /// The various KeyEvent types.
  ///
  enum Type {
    ///
    /// Key-Down event type. This type does **not** trigger accelerator commands in WebCore (eg, 
    /// Ctrl+C for copy is an accelerator command).
    ///
    /// @warning  You should probably use kType_RawKeyDown instead. This type is only here for
    ///           historic compatibility with WebCore's key event types.
    ///
    kType_KeyDown,

    ///
    /// Key-Up event type. Use this when a physical key is released.
    ///
    kType_KeyUp,

    ///
    /// Raw Key-Down type. Use this when a physical key is pressed.
    ///
    kType_RawKeyDown,

    ///
    /// Character input event type. Use this when the OS generates text from a physical key being
    /// pressed (for example, this maps to WM_CHAR on Windows).
    ///
    kType_Char,
  };

  ///
  /// Creates an empty KeyEvent, you will need to initialize its members
  /// yourself. This is useful for synthesizing your own keyboard events.
  ///
  KeyEvent();

#ifdef _WIN32
  ///
  /// Create a KeyEvent directly from a Windows keyboard event.
  ///
  KeyEvent(Type type, uintptr_t wparam, intptr_t lparam, bool is_system_key);
#endif

#ifdef __OBJC__
  ///
  /// Create a KeyEvent directly from a macOS NSEvent.
  ///
  KeyEvent(NSEvent* evt);
#endif

  ///
  /// An enumeration of the different keyboard modifiers.
  ///
  enum Modifiers : uint8_t {
    /// Whether or not an ALT key is down
    kMod_AltKey = 1 << 0,

    /// Whether or not a Control key is down
    kMod_CtrlKey = 1 << 1,

    /// Whether or not a meta key (Command-key on Mac, Windows-key on Win) is down
    kMod_MetaKey = 1 << 2,

    /// Whether or not a Shift key is down
    kMod_ShiftKey = 1 << 3,
  };

  ///
  /// The type of this KeyEvent.
  ///
  Type type;

  ///
  /// The current state of the keyboard. Modifiers may be OR'd together to represent multiple
  /// values.
  ///
  unsigned modifiers;

  ///
  /// The virtual key-code associated with this keyboard event. This is either directly from the
  /// event (ie, WPARAM on Windows) or via a mapping function. You can see a full list of the
  /// possible virtual key-codes in KeyCodes.h
  ///
  int virtual_key_code;

  ///
  /// The actual key-code generated by the platform. The DOM spec primarily uses Windows-equivalent
  /// codes (hence virtualKeyCode above) but it helps to also specify the platform-specific
  /// key-code as well.
  ///
  int native_key_code;

  ///
  /// This is a string identifying the key that was pressed. This can be generated from the
  /// virtual_key_code via the GetKeyIdentifierFromVirtualKeyCode() utility function. You can find
  /// the full list of key identifiers at:
  ///   <https://www.w3.org/TR/2003/WD-DOM-Level-3-Events-20030331/keyset.html>
  ///
  String key_identifier;

  ///
  /// The actual text generated by this keyboard event. This is usually only a single character.
  ///
  String text;

  ///
  /// The text generated by this keyboard event before all modifiers except shift are applied. This
  /// is used internally for working out shortcut keys. This is usually only a single character.
  ///
  String unmodified_text;

  ///
  /// Whether or not this is a keypad event.
  ///
  bool is_keypad;

  ///
  /// Whether or not this was generated as the result of an auto-repeat (eg, holding down a key).
  ///
  bool is_auto_repeat;

  ///
  /// Whether or not the pressed key is a "system key". This is a Windows-only concept and should
  /// be "false" for all non-Windows platforms. For more information, see the following link:
  ///   <http://msdn.microsoft.com/en-us/library/ms646286(VS.85).aspx>
  ///
  bool is_system_key;
};

///
/// Utility function for generating a key identifier string from a virtual
/// key-code.
///
/// @param  virtual_key_code       The virtual key-code to generate the key identifier from.
///
/// @param  key_identifier_result  The string to store the result in.
///
void UExport GetKeyIdentifierFromVirtualKeyCode(int virtual_key_code,
                                                String& key_identifier_result);

///
/// Utility function for generating a key string from a virtual key-code.
///
/// @param  virtual_key_code       The virtual key-code to generate the key string from.
///
/// @param  shift   Whether or not the shift key is currently pressed.
///
/// @param  key_result  The string to store the result in.
///
/// @note   This function assumes US keyboard layout.
///
/// @see <https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/key/Key_Values>
///
void UExport GetKeyFromVirtualKeyCode(int virtual_key_code, bool shift, String& key_result);

} // namespace ultralight
