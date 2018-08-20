#pragma once

#define MAXKEY 255

class CInput
{
	STATIC_SINGLETON(CInput)

private:
	BYTE keyState[MAXKEY];
	BYTE keyOldState[MAXKEY];
	BYTE keyMap[MAXKEY];

	enum
	{
		KEY_NONE,
		KEY_DOWN,
		KEY_UP,
		KEY_PRESS,
		KEY_END
	};

public:
	CInput();
	~CInput();

	void Init();
	void Update_Key();
	void Release();
	void Destroy();
	bool KeyDown(DWORD key)
	{
		return keyMap[key] == KEY_DOWN;
	}

	bool KeyUp(DWORD key)
	{
		return keyMap[key] == KEY_UP;
	}

	bool keyPress(DWORD key)
	{
		return keyMap[key] == KEY_PRESS;
	}
};

