#pragma once

#include <pxStdDef.h>

void    KeyControl_Clear(         );
void    KeyControl_WM_MESSAGE(    HWND hWnd, UINT message, WPARAM wParam );
void    KeyControl_WM_MOUSEWHEEL( HWND hWnd, UINT message, WPARAM wParam );
void    KeyControl_UpdateTrigger(        );
bool    KeyControl_IsKey        ( int32_t vk );
bool    KeyControl_IsKeyTrigger ( int32_t vk );
bool    KeyControl_IsKeyNtrigger( int32_t vk );
bool    KeyControl_IsClickLeft  (         );
bool    KeyControl_IsClickRight (         );
bool    KeyControl_IsClickLeftTrigger(    );
bool    KeyControl_IsClickRightTrigger(   );
bool    KeyControl_IsClickLeftRtrigger(   );
bool    KeyControl_IsClickRightRtrigger();
int32_t KeyControl_GetWheel(             );

bool    KeyControl_IsCapture();
