#include <pxStdDef.h>

#include <pxPalette.h>

bool    if_PlayField_Initialize( const pxPalette* palette );
void    if_PlayField_Reset     ();
void    if_PlayField_SetRect( const fRECT *rc_view );
fRECT*  if_PlayField_GetRect  ();
void    if_PlayField_Put      ();
void    if_PlayField_SetStartMeas( int32_t meas, bool bExistingDelete );
int32_t if_PlayField_GetStartMeas();
void    if_PlayField_SetEndMeas(   int32_t meas, bool bExistingDelete );
int32_t if_PlayField_GetEndMeas();
