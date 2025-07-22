#include <pxFile2.h>

void    if_Panel_Scale_init        ( const pxFile2* ref_file_profile );

void    if_Panel_Scale_SetRect     ( const fRECT *rc_view );
fRECT*  if_Panel_Scale_GetRect     ();
void    if_Panel_Scale_Put         ();
bool    if_Panel_Scale_IsZoomButton( float x, float y );

void    if_Panel_Scale_SetZoom     ( int32_t zoom_index );
int32_t if_Panel_Scale_GetZoom     ();
void    if_Panel_Scale_ShiftZoom   ( bool b );
