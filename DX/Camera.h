#pragma once
class CCamera
{
	STATIC_SINGLETON(CCamera)

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXMATRIX matMainView;
	D3DXMATRIX matProj;

	D3DXVECTOR3 m_vPos;

	D3DXVECTOR3 m_vBeforePos;

public:
	CCamera();
	~CCamera();

public:
	void Init(LPDIRECT3DDEVICE9 _pDevice);
	int Update(float _fTime = 0.0f);

public:
	D3DXVECTOR3 GetPos()
	{
		return m_vBeforePos;
	}

private:
	void Release();
};

