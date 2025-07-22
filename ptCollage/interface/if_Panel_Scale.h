#include <pxStdDef.h>

#include <pxFile2.h>

void    if_Panel_init( const pxFile2* file_profile );

void    if_Panel_Scale_Load();
bool    if_Panel_Scale_Save();


void    if_Panel_Scale_SetRect     ( const fRECT *rc_view );
fRECT*  if_Panel_Scale_GetRect     ();
void    if_Panel_Scale_Put         ();
bool    if_Panel_Scale_IsZoomButton( float x, float y );
bool    if_Panel_Scale_IsDiviButton( float x, float y );

void    if_Panel_Scale_SetDivision ( int32_t divi_index );
int32_t if_Panel_Scale_GetDivision ();
void    if_Panel_Scale_SetZoom     ( int32_t zoom_index );
int32_t if_Panel_Scale_GetZoom     ();
void    if_Panel_Scale_ShiftZoom   ( bool b );
