#pragma once
#define _WIN32_WINNT    0400
#define STRICT
#define WIN32_LEAN_AND_MEAN
#define WH_KEYBOARD_LL 13
// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。


#include <SDKDDKVer.h>
