#include <pxStdDef.h>

#include <windows.h>
#include <stdio.h>
#include <cstdint>


#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "Interface.h"
#include "SurfaceNo.h"

void   if_Tenkey_Tuning_Initialize();
void   if_Tenkey_Tuning_SetActive ( float x, float y, int32_t u, int32_t clock );
void   if_Tenkey_Tuning_SetRect   ( const fRECT *rc_view );
void   if_Tenkey_Tuning_Close     ();
fRECT* if_Tenkey_Tuning_GetRect   ();
bool   if_Tenkey_Tuning_IsFrame   ( float x, float y );
bool   if_Tenkey_Tuning_ButtonDown( float x, float y );
bool   if_Tenkey_Tuning_ButtonUp  ();
void   if_Tenkey_Tuning_ButtonCancel();
void   if_Tenkey_Tuning_Put       ();

bool   if_Tenkey_Tuning_GetResult( float* p_f, int32_t* p_u, int32_t* p_clock );
