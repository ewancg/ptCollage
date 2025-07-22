typedef struct
{
	const TCHAR *p_message;
	const TCHAR *p_title  ;
}
MESSAGEDIALOGSTRUCT;

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_Message( HWND hWnd, UINT msg, WPARAM w, LPARAM l );
