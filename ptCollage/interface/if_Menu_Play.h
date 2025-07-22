#include <pxStdDef.h>

enum enum_PlayMenu
{
	enum_PlayMenu_None  = 0,
	enum_PlayMenu_SetRepeat,
	enum_PlayMenu_SetLast  ,
	enum_PlayMenu_CutRepeat,
	enum_PlayMenu_CutLast  ,
};

void   if_Menu_Play_Initialize    ();
void   if_Menu_Play_SetPosition   ( float x  , float y, bool bCenter );
void   if_Menu_Play_GetPosition   ( float *px, float *py );
void   if_Menu_Play_SetRect       ( const fRECT *rc_view );
void   if_Menu_Play_SetActive     ( bool bActive );
fRECT* if_Menu_Play_GetRect       ();
bool   if_Menu_Play_IsFrame       ( float x, float y );
enum_PlayMenu if_Menu_Play_GetMenu( float x, float y );
void   if_Menu_Play_Put           ();
