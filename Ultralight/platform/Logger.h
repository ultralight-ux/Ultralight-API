///
/// @file Logger.h
///
/// @brief The header for the Logger interface.
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
#include <Ultralight/Defines.h>
#include <Ultralight/String.h>

namespace ultralight {

///
/// Log levels, used with Logger::LogMessage
///
enum class LogLevel : uint8_t {
  Error,
  Warning,
  Info
};

///
/// @brief  Logger interface.
///          
/// This can be used to log debug messages to the console or to a log file.
///
/// This is intended to be implemented by users and defined before creating the Renderer. 
/// 
/// @see Platform::set_file_system.
///
class UExport Logger {
public:
  virtual ~Logger();

  ///
  /// Called when the library wants to print a message to the log.
  ///
  virtual void LogMessage(LogLevel log_level, const String& message) = 0;
};

}  // namespace ultralight
