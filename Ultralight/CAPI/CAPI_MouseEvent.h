#ifndef ULTRALIGHT_CAPI_MOUSEEVENT_H
#define ULTRALIGHT_CAPI_MOUSEEVENT_H

#include <Ultralight/CAPI/CAPI_Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Mouse Event
 *****************************************************************************/

///
/// Create a mouse event, @see MouseEvent for help using this function.
///
ULExport ULMouseEvent ulCreateMouseEvent(ULMouseEventType type, int x, int y, ULMouseButton button);

///
/// Destroy a mouse event.
///
ULExport void ulDestroyMouseEvent(ULMouseEvent evt);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_MOUSEEVENT_H