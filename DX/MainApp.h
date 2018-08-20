#pragma once

class CDevice;
class CBase;

class CMainApp
{
	LPDIRECT3DDEVICE9 m_pDevice;
	CGameObject* m_pPlayer;
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