#include <pxStdDef.h>

#include <pxPalette.h>

bool   if_KeyField_init       ( const pxPalette* palpng  );

void   if_KeyField_PutField   ();
void   if_KeyField_PutEvent   ();
void   if_KeyField_JustScroll ();
void   if_KeyField_SetRect    ( const fRECT *rc_view );
fRECT* if_KeyField_GetRect    ();
void   if_KeyField_ResetScroll();
