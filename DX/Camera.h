#pragma once
class CCamera
{
	STATIC_SINGLETON(CCamera)

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXMATRIX matMainView;
	D3DXMATRIX matProj;

public:
	CCamera();
	~CCamera();

public:
	void Init(LPDIRECT3DDEVICE9 _pDevice);
	int Update();

private:
	void Release();
};

