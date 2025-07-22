#include <pxStdDef.h>

#define KEYBOARD_KEYNUM     88
#define KEYBOARD_KEYHEIGHT  16

void   if_Keyboard_Initialize();
void   if_Keyboard_Put();
void   if_Keyboard_SetRect( const fRECT *rc_view );
fRECT* if_Keyboard_GetRect();
void   if_Keyboard_SetPush( int32_t key, bool bOn );
void   if_Keyboard_ClearPush();

