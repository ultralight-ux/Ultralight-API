///
/// @file Clipboard.h
///
/// @brief The header for the Clipboard interface.
///
/// @author
///
/// This file is a part of Ultralight, a fast, lightweight, HTML UI engine
///
/// Website: <http://ultralig.ht>
///
/// Copyright (C) 2020 Ultralight, Inc. All rights reserved.
///
#pragma once
#include <Ultralight/Defines.h>
#include <Ultralight/String16.h>

namespace ultralight {

///
/// @brief  Clipboard interface.
///          
/// This is used for reading and writing data to the platform Clipboard.
///
/// This is intended to be implemented by users and defined before creating the
/// Renderer. @see Platform::set_clipboard.
///
class UExport Clipboard {
public:
  virtual ~Clipboard();

  ///
  /// Clear the clipboard.
  ///
  virtual void Clear() = 0;

  ///
  /// Read plain text from the clipboard
  ///
  virtual String16 ReadPlainText() = 0;

  ///
  /// Write plain text to the clipboard.
  ///
  virtual void WritePlainText(const String16& text) = 0;
};

}  // namespace ultralight
