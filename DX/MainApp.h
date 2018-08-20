#pragma once

class CDevice;
class CBase;

class CMainApp
{
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	CMainApp();
	~CMainApp();

public:
	void Init();
	int Update();
	void Render();

private:
	void Release();
};