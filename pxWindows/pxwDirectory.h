// '16/01/29 pxwDirectory.
// '17/10/04 + pxwDirectory_remove, pxwDirectory_rename

#ifndef pxwDirectory_H
#define pxwSirectory_H

#include <pxStdDef.h>

bool pxwDirectory_find        ( const TCHAR *path_dir, const TCHAR *ext, bool b_sub_dir, pxfunc_find_path func, void *user );
bool pxwDirectory_copy_folders( const TCHAR *path_dst, const TCHAR* path_src );

bool pxwDirectory_remove      ( const TCHAR* dir_path );
bool pxwDirectory_create      ( const TCHAR* dir_path );
bool pxwDirectory_rename      ( const TCHAR *path_orginal, const TCHAR* path_new, bool b_remove_exist );

#endif
