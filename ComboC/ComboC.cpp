// ComboC.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
using namespace std;
void SendString(wchar_t*);
typedef struct 
{
	DWORD vkCode;
	DWORD scanCode;
	DWORD flags;
	DWORD time;
	ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

DWORD   g_main_tid = 0;
HHOOK   g_kb_hook   = 0;
BOOL CALLBACK con_handler (DWORD)
{
	PostThreadMessage (g_main_tid, WM_QUIT, 0, 0);
	return TRUE;
};
LRESULT CALLBACK kb_proc (int code, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT pVirKey = (PKBDLLHOOKSTRUCT)lParam;
	wchar_t tmp[10];
	if (pVirKey->vkCode == 231)
	{
		return CallNextHookEx (g_kb_hook, code, wParam, lParam);
	}
	if (code >= 0)
	{
		switch(wParam)
		{
		// SYS KEY 只是Alt
		case(WM_KEYDOWN):
		case(WM_SYSKEYDOWN):
			printf("%d down\n",pVirKey->vkCode);
			swprintf(tmp,10,L"%d down\n",pVirKey->vkCode);
			break;
		case(WM_KEYUP):
		case(WM_SYSKEYUP):
			printf("%d up\n",pVirKey->vkCode);
			swprintf(tmp,10,L"%d up\n",pVirKey->vkCode);
			break;
		}
		SendString(tmp);
	}
	if(pVirKey->vkCode == 164){
		return 1;
	}else{
		return CallNextHookEx (g_kb_hook, code, wParam, lParam);
	}

};
int _tmain(int argc, _TCHAR* argv[])
{
	g_main_tid = GetCurrentThreadId ();
	SetConsoleCtrlHandler (&con_handler, TRUE);
	g_kb_hook = SetWindowsHookEx (
		WH_KEYBOARD_LL,
		&kb_proc,
		GetModuleHandle (NULL), //　不能为NULL，否则失败
		0);
	if (g_kb_hook == NULL)
	{
		fprintf (stderr,
			"SetWindowsHookEx failed with error %d\n",
			::GetLastError ());
		return 0;
	};
	// 消息循环是必须的，想知道原因可以查msdn
	MSG msg;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	};
	UnhookWindowsHookEx (g_kb_hook);
	return 0;
}

