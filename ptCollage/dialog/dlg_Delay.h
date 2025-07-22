
#include <pxtnDelay.h>

typedef struct
{
	DELAYUNIT unit    ;
	float     freq    ;
	float     rate    ;
	int32_t       group   ;
	bool      b_delete;
}
EFFECTSTRUCT_DELAY;

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_Delay_Procedure( HWND hDlg, UINT msg, WPARAM w, LPARAM l );
