#ifndef if_Effector_H
#define if_Effector_H

#include <pxStdDef.h>

#include <pxFile2.h>

void    if_Effector_init( HWND hWnd, const pxFile2* file_profile );

void    if_Effector_SavePosition();
void    if_Effector_SetPosition( float x, float y );
void    if_Effector_GetPosition( float *px, float *py );
void    if_Effector_SetRect    ( const fRECT *rc_view );
fRECT*  if_Effector_GetRect    ();
void    if_Effector_SetCursor  ( float cur_x, float cur_y );
bool    if_Effector_ShutButton ( float x, float y );
int32_t if_Effector_GetFlags   ();
void    if_Effector_SetFlags   ( int32_t flags );
bool    if_Effector_IsOpen     ();
void    if_Effector_SetOpen    ();
bool    if_Effector_HitButton  ( float cur_x, float cur_y );
void    if_Effector_Put        ();
bool    if_Effector_HitPlayed  ( float cur_x, float cur_y, bool* p_b );
void    if_Effector_SetPlayed  ( float cur_x, float cur_y, bool b    );
void    if_Effector_SetFocus   ();

#endif