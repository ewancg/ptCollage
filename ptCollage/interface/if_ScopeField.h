#ifndef if_ScopeField_H
#define if_ScopeField_H

#include <pxStdDef.h>

#include <pxSurface.h>

bool   if_ScopeField_init( const pxPalette* pal );

void   if_ScopeField_Zero       ();
void   if_ScopeField_SetRect    ( const fRECT *rc_view );
fRECT* if_ScopeField_GetRect    ();
void   if_ScopeField_Put        ();
void   if_ScopeField_SetScope   ( int32_t clock1, int32_t clock2 );
void   if_ScopeField_SetScopeAll();
void   if_ScopeField_GetSelected( int32_t *p_clock1, int32_t *p_clock2 );
void   if_ScopeField_GetSelected( int32_t *p_meas1, int32_t *p_beat1, int32_t *p_clock1,
								  int32_t *p_meas2, int32_t *p_beat2, int32_t *p_clock2 );

#endif


