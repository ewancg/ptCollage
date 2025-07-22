#ifndef if_SubWindows_H
#define if_SubWindows_H

#include <pxStdDef.h>

typedef void (* PUTFUNCTION    )( void                   );
typedef bool (* CURSORFUNCTION )( float cur_x, float cur_y  );

typedef struct
{
	PUTFUNCTION    func_put;
	CURSORFUNCTION func_cur;

}SUBWINDOWSTRUCT;


void if_SubWindows_Initialize();
void if_SubWindows_Release(    void );
SUBWINDOWSTRUCT* if_SubWindows_Create( PUTFUNCTION func_put, CURSORFUNCTION func_cur );
void if_SubWindows_Put(        void );
void if_SubWindows_SetFocus( SUBWINDOWSTRUCT* handle );

bool if_Cursor_Action_SubWindow( float cur_x, float cur_y );

#endif
