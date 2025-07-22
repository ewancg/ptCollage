
typedef struct
{
	float cut  ;
	float amp  ;
	int32_t   group;

	bool  b_delete;
}
EFFECTSTRUCT_OVERDRIVE;

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_OverDrive_Procedure( HWND hDlg, UINT msg, WPARAM w, LPARAM l );
