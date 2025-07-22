typedef struct
{
	int32_t voice_no;
	char    name[ pxtnMAX_TUNEUNITNAME + 1 ];
}
ADDUNITSTRUCT;

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
	dlg_AddUnit( HWND hDlg, UINT msg, WPARAM w, LPARAM l );
