/**************************************************************************************************
 *  This file is a part of Ultralight.                                                            *
 *                                                                                                *
 *  See <https://ultralig.ht> for licensing and more.                                             *
 *                                                                                                *
 *  (C) 2024 Ultralight, Inc.                                                                     *
 **************************************************************************************************/

///
/// @file CAPI_FontFile.h
///
/// Font file interface.
///
/// `#include <Ultralight/CAPI/CAPI_FontFile.h>`
///
/// The font file interface represents a font file: either on-disk path or in-memory file contents.
///
/// @see ULFontLoader
///
#ifndef ULTRALIGHT_CAPI_FONTFILE_H
#define ULTRALIGHT_CAPI_FONTFILE_H

#include <Ultralight/CAPI/CAPI_Defines.h>
#include <Ultralight/CAPI/CAPI_String.h>
#include <Ultralight/CAPI/CAPI_Buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

///
/// Create a font file from an on-disk file path.
///
/// @note  The file path should already exist.
///
ULExport ULFontFile ulFontFileCreateFromFilePath(ULString file_path);

///
/// Create a font file from an in-memory buffer.
///
ULExport ULFontFile ulFontFileCreateFromBuffer(ULBuffer buffer);

///
/// Destroy font file
///
ULExport void ulDestroyFontFile(ULFontFile font_file);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_FONTFILE_H