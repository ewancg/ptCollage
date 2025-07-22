#ifndef pxwFilePath_H
#define pxwFilePath_H

#include <pxStdDef.h>

enum SPECIALPATH
{
	SPECIALPATH_DESKTOP = 0,
	SPECIALPATH_MYDOCUMENT ,
	SPECIALPATH_MYCOMPUTER ,
};

void pxwFilePath_ncomp_x_sjis        ( char *name );

bool pxwFilePath_ArgToPath           ( const TCHAR* arg, TCHAR* path_dst );

void pxwFilePath_GetSpecial          (       TCHAR* path, SPECIALPATH special );
void pxwFilePath_GetDesktop          (       TCHAR* path );

bool pxwFilePath_GetShortcutDirectory( const TCHAR* path_lnk, TCHAR* path_dst );
bool pxwFilePath_IsDrive             ( const TCHAR* path );
void pxwFilePath_GetModuleDirectory  (       TCHAR* path );

bool pxwFilePath_MakeFolderPath      (       TCHAR** p_path_dst, const TCHAR *name, bool b_create );

#endif
