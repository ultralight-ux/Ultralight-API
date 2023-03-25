///
/// @file GamepadEvent.h
///
/// @brief The header for various gamepad events.
///
/// @author
///
/// This file is a part of Ultralight, a next-generation HTML renderer.
///
/// Website: <http://ultralig.ht>
///
/// Copyright (C) 2022 Ultralight, Inc. All rights reserved.
///
#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/String.h>

namespace ultralight {

///
/// @brief  A gamepad event.
///
/// @see    View::FireGamepadEvent
///
class UExport GamepadEvent {
 public:
  ///
  /// The various GamepadEvent types.
  ///
  enum Type {
    ///
    /// This event type should be fired when a gamepad is connected.
    ///
    /// @note  You will need to previously declare the gamepad, its index, and details about
    ///        its axis and button layout via View::SetGamepadDetails prior to calling
    ///        View::FireGamepadEvent.
    /// 
    kType_GamepadConnected,
    
    ///
    /// This event type should be fired when a gamepad is disconnected.
    ///
    kType_GamepadDisconnected,
  };

  ///
  // The type of this GamepadEvent
  ///
  Type type;

  ///
  /// The index of the gamepad, this should match the value previously set in
  /// View::SetGamepadDetails.
  ///
  uint32_t index;
};

///
/// @brief  A gamepad axis event.
///
/// @see    View::FireGamepadAxisEvent
///
class UExport GamepadAxisEvent {
 public:
  ///
  /// The index of the gamepad, this should match the value previously set in
  /// View::SetGamepadDetails.
  ///
  uint32_t index;

  ///
  /// The index of the axis whose value has changed.
  ///
  /// This value should be in the range previously set in View::SetGamepadDetails.
  ///
  uint32_t axis_index;

  ///
  /// The new value of the axis.
  ///
  /// This value should be normalized to the range [-1.0, 1.0].
  ///
  double value;
};

///
/// @brief  A gamepad button event.
///
/// @see    View::FireGamepadButtonEvent
///
class UExport GamepadButtonEvent {
 public:
  ///
  /// The index of the gamepad, this should match the value previously set in
  /// View::SetGamepadDetails.
  ///
  uint32_t index;

  ///
  /// The index of the button whose value has changed.
  ///
  /// This value should be in the range previously set in View::SetGamepadDetails.
  ///
  uint32_t button_index;

  ///
  /// The new value of the button.
  ///
  /// This value should be normalized to the range [-1.0, 1.0], with any value greater than
  /// 0.0 to be considered "pressed".
  ///
  double value;
};

}  // namespace ultralight
