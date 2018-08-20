#pragma once

#include "stdafx.h"

class CMouse
{
public:
	CMouse(){}
	~CMouse(){}

public:
	static inline POINT GetMousePos()
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		return ptMouse;
	}

};
