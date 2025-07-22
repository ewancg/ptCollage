#pragma once

//for HDROP
//#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT 0x0400 // MainProc.cpp

#define WM_USER_RELATEDFILE (WM_USER + 0)

#include <windows.h>
#include <stdio.h>
#include <cstdint>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi")
#include <commctrl.h>
#pragma comment(lib, "comctl32")

#pragma comment( lib, "imm32" )
#pragma comment( lib, "winmm" )
#include <imm.h>

#include <pxStdDef.h>

#include <tchar.h>
