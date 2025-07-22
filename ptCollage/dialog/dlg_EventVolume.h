enum enum_EventKind
{
	enum_EventKind_Key     ,
	enum_EventKind_Velocity,
	enum_EventKind_TimePan ,
	enum_EventKind_VolPan  ,
	enum_EventKind_Volume  ,
};

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_EventVolume( HWND hDlg, UINT msg, WPARAM w, LPARAM l );

