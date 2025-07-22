#include <pxStdDef.h>

#include <pxPalette.h>

void    if_BaseField_SetRect( const fRECT *rc_view );
fRECT*  if_BaseField_GetRect();

bool    if_BaseField_init( int32_t beat_w, int32_t divi_num, const pxPalette* palpng );

void    if_BaseField_Release();

void    if_BaseField_SetParameter( int32_t  beat_w, int32_t  divi_num );
int32_t if_BaseField_GetBeatWidth();
int32_t if_BaseField_GetDivideWidth();
void    if_BaseField_Put_Field();
void    if_BaseField_Put_Grid ();
bool    if_BaseField_Action( float cur_x, float cur_y );

#include <pxtnEvelist.h>

int32_t if_BaseField_Event_get_Value( float cur_x, int32_t unit_no, int32_t kind );
int32_t if_BaseField_Event_get_View(             int32_t unit_no, int32_t kind, const EVERECORD** pp_eve );
int32_t if_BaseField_Event_get_View(             int32_t unit_no,               const EVERECORD** pp_eve );
int32_t if_BaseField_Event_get_View_KeyField(    int32_t unit_no,               const EVERECORD** pp_eve );
void    if_BaseField_Event_get_View_Unlock();
