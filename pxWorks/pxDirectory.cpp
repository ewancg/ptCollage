
#include <pxwrDirectory.h>

#include "./pxDirectory.h"

bool pxDirectory_file_find( const TCHAR *path_dir, const TCHAR *ext, bool b_sub_dir, pxfunc_find_path func, void *user )
{
	return pxwrDirectory_find( path_dir, ext, b_sub_dir, func, user );
}

bool pxDirectory_copy_folders( const TCHAR* path_dst, const TCHAR* path_src )
{
	return pxwrDirectory_copy_folders( path_dst, path_src );
}