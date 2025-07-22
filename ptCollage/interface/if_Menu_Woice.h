#include <pxStdDef.h>

enum enum_WoiceMenu
{
	enum_WoiceMenu_None = 0,
	enum_WoiceMenu_Change  ,
	enum_WoiceMenu_Edit    ,
	enum_WoiceMenu_Remove  ,
	enum_WoiceMenu_Export  ,
};

void     if_Menu_Woice_Initialize();
void     if_Menu_Woice_SetPosition( float x  , float y, int32_t u );
void     if_Menu_Woice_GetPosition( float *px, float *py );
int32_t  if_Menu_Woice_GetWoiceIndex();
void     if_Menu_Woice_SetRect( const fRECT *rc_view );
void     if_Menu_Woice_SetActive( bool bActive );
fRECT*   if_Menu_Woice_GetRect();
bool     if_Menu_Woice_IsFrame      ( float x, float y );
enum_WoiceMenu if_Menu_Woice_GetMenu( float x, float y );
void     if_Menu_Woice_Put  ();
bool     if_Menu_Woice_IsTop();
