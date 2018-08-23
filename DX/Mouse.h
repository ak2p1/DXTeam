#pragma once

#include "stdafx.h"

class CMouse
{
public:
	CMouse(){}
	~CMouse(){}

public:
	static inline D3DXVECTOR2 GetMousePos()
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		
		return D3DXVECTOR2((float)ptMouse.x , (float)ptMouse.y);
	}

};
