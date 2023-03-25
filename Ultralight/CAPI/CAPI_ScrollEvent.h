#ifndef ULTRALIGHT_CAPI_SCROLLEVENT_H
#define ULTRALIGHT_CAPI_SCROLLEVENT_H

#include <Ultralight/CAPI/CAPI_Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Scroll Event
 *****************************************************************************/

///
/// Create a scroll event, @see ScrollEvent for help using this function.
///
ULExport ULScrollEvent ulCreateScrollEvent(ULScrollEventType type, int delta_x, int delta_y);

///
/// Destroy a scroll event.
///
ULExport void ulDestroyScrollEvent(ULScrollEvent evt);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ULTRALIGHT_CAPI_SCROLLEVENT_H