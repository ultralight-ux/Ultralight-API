/**************************************************************************************************
 *  This file is a part of Ultralight.                                                            *
 *                                                                                                *
 *  See <https://ultralig.ht> for licensing and more.                                             *
 *                                                                                                *
 *  (C) 2024 Ultralight, Inc.                                                                     *
 **************************************************************************************************/

///
/// @file CAPI_FileSystem.h
///
/// User-defined file system interface.
///
/// `#include <Ultralight/CAPI/CAPI_FileSystem.h>`
///
/// The library uses this to load file data (ie, raw file bytes) for a given file URL 
/// (eg, `file:///page.html`) .
///
/// You can provide the library with your own FileSystem implementation (ULFileSystem) so that file
/// data is provided directly by your application (eg, from memory, from a virtual file system,
/// etc).
///
/// @see ulPlatformSetFileSystem
/// 
#ifndef ULTRALIGHT_CAPI_FILESYSTEM_H
#define ULTRALIGHT_CAPI_FILESYSTEM_H

#include <Ultralight/CAPI/CAPI_Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * File System
 *****************************************************************************/

///
/// The callback invoked when the FileSystem wants to check if a file path exists, return true if it
/// exists.
///
typedef bool (*ULFileSystemFileExistsCallback)(ULString path);

///
/// Get the mime-type of the file (eg "text/html").
///
/// This is usually determined by analyzing the file extension.
///
/// If a mime-type cannot be determined, you should return "application/unknown" for this value.
/// 
/// The library will consume the result and call ulDestroyString() after this call returns.
///
typedef ULString (*ULFileSystemGetFileMimeTypeCallback)(ULString path);

///
/// Get the charset / encoding of the file (eg "utf-8").
///
/// This is only important for text-based files and is usually determined by analyzing the
/// contents of the file.
///
/// If a charset cannot be determined, it's usually safe to return "utf-8" for this value.
/// 
/// The library will consume the result and call ulDestroyString() after this call returns.
///
typedef ULString (*ULFileSystemGetFileCharsetCallback)(ULString path);

///
/// Open file for reading and map it to a Buffer.
///
/// To minimize copies, you should map the requested file into memory and use ulCreateBuffer()
/// to wrap the data pointer (unmapping should be performed in the destruction callback).
///
/// If the file was unable to be opened, you should return NULL for this value.
///
typedef ULBuffer (*ULFileSystemOpenFileCallback)(ULString path);

/// 
/// User-defined file system interface.
///
/// You should implement each of these callbacks, then pass an instance of this struct containing
/// your callbacks to ulPlatformSetFileSystem().
///
typedef struct {
  ULFileSystemFileExistsCallback file_exists;
  ULFileSystemGetFileMimeTypeCallback get_file_mime_type;
  ULFileSystemGetFileCharsetCallback get_file_charset;
  ULFileSystemOpenFileCallback open_file;
} ULFileSystem;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_FILESYSTEM_H