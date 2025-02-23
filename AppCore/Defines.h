/**************************************************************************************************
 *  This file is a part of Ultralight.                                                            *
 *                                                                                                *
 *  See <https://ultralig.ht> for licensing and more.                                             *
 *                                                                                                *
 *  (C) 2024 Ultralight, Inc.                                                                     *
 **************************************************************************************************/
#pragma once

// Needed for limit defines, like INTMAX_MAX, which is used by the std C++ library
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include <cstdint>
#include <cstddef>
#include <limits.h>

#ifdef SWIG
#define AExport
#else

// Require C++11 Support
#if defined(_MSC_VER)
#   if _MSC_VER < 1800 
#       error This project needs at least Visual Studio 2013 to build
#   endif
#elif __cplusplus <= 199711L
#   error This project can only be compiled with a compiler that supports C++11
#endif

#if defined(ULTRALIGHT_STATIC_BUILD)
#  define AExport 
#else
#  if defined(__WIN32__) || defined(_WIN32)
#    if defined(APPCORE_IMPLEMENTATION)
#      define AExport __declspec(dllexport)
#    else
#      define AExport __declspec(dllimport)
#    endif
#  else
#    define AExport __attribute__((visibility("default")))
#  endif
#endif

#if defined(__WIN32__) || defined(_WIN32)
#  define _thread_local __declspec(thread)
#  ifndef _NATIVE_WCHAR_T_DEFINED
#    define DISABLE_NATIVE_WCHAR_T
#  endif
#else
#  define _thread_local __thread
#endif

#endif
