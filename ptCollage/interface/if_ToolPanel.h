#pragma once

#include <pxStdDef.h>

enum enum_ToolMode
{
	enum_ToolMode_W = 0,
	enum_ToolMode_U,
	enum_ToolMode_K,
};

enum enum_ToolButton
{
	enum_ToolButton_Mode_W ,
	enum_ToolButton_Mode_U ,
	enum_ToolButton_Mode_K ,
	enum_ToolButton_Mode_3 ,
	enum_ToolButton_Mode_4 ,
	enum_ToolButton_W_add  ,
	enum_ToolButton_W_1    ,
	enum_ToolButton_W_2    ,
	enum_ToolButton_W_3    ,
	enum_ToolButton_W_4    ,
	enum_ToolButton_U_add  ,
	enum_ToolButton_U_1    ,
	enum_ToolButton_U_2    ,
	enum_ToolButton_U_3    ,
	enum_ToolButton_U_all  ,
	enum_ToolButton_U_solo ,
	enum_ToolButton_K_pen  ,
	enum_ToolButton_K_hand ,
	enum_ToolButton_K_2    ,
	enum_ToolButton_K_up   ,
	enum_ToolButton_K_down ,
	enum_ToolButton_unknown,
};

void if_ToolPanel_Put();
void if_ToolPanel_SetRect( const fRECT *rc_view );
enum_ToolMode if_ToolPanel_GetMode();
bool if_ToolPanel_IsUseKeyOnly();

void if_ToolPanel_SetMode_W();
void if_ToolPanel_SetMode_U();
void if_ToolPanel_SetMode_K();

enum_ToolButton if_ToolPanel_GetHitButton( float cur_x, float cur_y );
bool            if_ToolPanel_SetHitButton( enum_ToolButton button );
