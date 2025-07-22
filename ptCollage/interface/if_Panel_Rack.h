#ifndef if_Panel_Rack_H
#define if_Panel_Rack_H

#include <pxStdDef.h>

void   if_Panel_Rack_SetRect  ( const fRECT *rc_view );
fRECT* if_Panel_Rack_GetRect  ();
void   if_Panel_Rack_Put      ();
bool   if_Panel_Rack_HitButton( float cur_x, float cur_y );

#endif
