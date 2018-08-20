#include "stdafx.h"
#include "Input.h"


CInput::CInput()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

CInput::~CInput()
{
	Release();
}

void CInput::Init()
{

}

void CInput::Update_Key()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	//1 : 한번 눌러진 상태
	//0 : 다시 누르면 0으로
	//128 : 0상태일때 해당키가 눌러져 있음
	//129 : 1상태일때 해당키가 눌러져 있음
	GetKeyboardState(keyState);

	for (int i = 0; i < MAXKEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1)
		{
			keyMap[i] = KEY_DOWN;
		}
		else if (oldState == 1 && state == 0)
		{
			keyMap[i] = KEY_UP;
		}
		else if (oldState == 1 && state == 1)
		{
			keyMap[i] = KEY_PRESS;
		}
		else
		{
			keyMap[i] = KEY_NONE;
		}
	}
}

void CInput::Release()
{

}

void CInput::Destroy()
{

}
