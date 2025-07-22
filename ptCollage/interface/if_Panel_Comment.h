#ifndef if_Panel_Comment_H
#define if_Panel_Comment_H

#include <pxStdDef.h>

void   if_Panel_Comment_SetRect( const fRECT *rc_view );
fRECT* if_Panel_Comment_GetRect();
void   if_Panel_Comment_Put(     void );
bool   if_Panel_Comment_HitButton( float cur_x, float cur_y );


#endif
