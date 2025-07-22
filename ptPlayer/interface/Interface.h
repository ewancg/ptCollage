
#include <pxFile2.h>
#include <pxPalette.h>


#define TUNENAME_WIDTH  152
#define TUNENAME_HEIGHT  16

bool Interface_init   ( HWND hWnd, const pxPalette* palette, const pxFile2* file_profile );
void Interface_Process( HWND hWnd, bool bDraw );
void Interface_Release();
