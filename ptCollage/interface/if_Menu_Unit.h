#include <pxStdDef.h>

enum enum_UnitMenu
{
	enum_UnitMenu_None = 0,
	enum_UnitMenu_Edit,
	enum_UnitMenu_Remove,
};

void    if_Menu_Unit_Initialize();
void    if_Menu_Unit_SetPosition( float x, float y, int32_t u );
void    if_Menu_Unit_GetPosition( float *px, float *py );
int32_t if_Menu_Unit_GetUnitIndex();
void    if_Menu_Unit_SetRect ( const fRECT *rc_view );
void    if_Menu_Unit_Close   ();
fRECT*  if_Menu_Unit_GetRect ();
bool    if_Menu_Unit_IsFrame      ( float x, float y );
enum_UnitMenu if_Menu_Unit_GetMenu( float x, float y );
void    if_Menu_Unit_Put     ();
bool    if_Menu_Unit_IsTop   ();
