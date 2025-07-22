// '17/01/21 ファイルを pxCSV2 で実装し直す。

#ifndef Menu_HistoryW_H
#define Menu_HistoryW_H

#include <pxStdDef.h>

#include <pxFile2.h>

bool Menu_HistoryW_init( HMENU hMenu, int32_t max_history, const UINT* idms, uint32_t idm_dummy, const pxFile2* file_profile );
void Menu_HistoryW_Release   ();
bool Menu_HistoryW_Load      ();
bool Menu_HistoryW_Save      ();
void Menu_HistoryW_Add       ( const wchar_t* path_new );
void Menu_HistoryW_Delete    ( uint32_t idm );
bool Menu_HistoryW_GetPath   ( uint32_t idm, wchar_t* path_dst );

#endif
