#include <atlconv.h>
#include <WinUser.h>

//ֱ�ӵ���SendString�����Ϳ����ڵ�ǰ����λ���Զ�����ָ�����ַ���

void SendAscii(wchar_t data, BOOL shift)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));

	if (shift)
	{
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		SendInput(1, input, sizeof(INPUT));
	}

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = data;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, input, sizeof(INPUT));

	if (shift)
	{
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, input, sizeof(INPUT)); 
	}
}


void SendUnicode(wchar_t data)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = data;
	input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 0;
	input[1].ki.wScan = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;

	SendInput(2, input, sizeof(INPUT));
}

//Ϊ����ʹ�ã��������������װ��ǰ����������
void SendString(wchar_t* data)
{
	USES_CONVERSION;
	//wchar_t* data = T2W(msg.GetBuffer(0));
	int len = wcslen(data);

	for(int i=0;i<len;i++)
	{
		SendUnicode(data[i]);
	}
}

