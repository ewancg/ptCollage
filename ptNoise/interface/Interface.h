
#include <pxFile2.h>

// RECTサイズ

#define PANEL_LOGO_W  112
#define PANEL_LOGO_H   24
#define PANEL_SCALE_W 112
#define PANEL_SCALE_H  24


#define PCMTABLE_H   (256/2)
#define PCMTABLE_X    0
#define PCMTABLE_Y   24

#define SCRLL_H      16

#define VIEWDEFAULT_W 441
#define VIEWDEFAULT_H (PCMTABLE_Y + PCMTABLE_H * 2 + SCRLL_H)

void Interface_Process( HWND hWnd, bool bDraw );
bool Interface_init   ( HWND hWnd, const pxFile2* file_profile );
