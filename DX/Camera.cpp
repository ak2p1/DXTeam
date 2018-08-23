#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"

CCamera::CCamera()
{
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vBeforePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CCamera::~CCamera()
{
	Release();
}

void CCamera::Init(LPDIRECT3DDEVICE9 _pDevice)
{
	m_pDevice = _pDevice;
	D3DXMatrixIdentity(&matMainView);
	D3DXMatrixIdentity(&matProj);

	D3DVIEWPORT9 viewport;
	m_pDevice->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(
		&matProj,
		0.0f, 
		(float)viewport.Width,
		(float)viewport.Height,
		0.f,
		-1.0f,
		1.0f);

	m_pDevice->SetTransform(D3DTS_VIEW, &matMainView);
	
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	int a = 0;
}

int CCamera::Update(float _fTime /*= 0.0f*/)
{
	D3DXMATRIX matPos;
	D3DXMatrixIdentity(&matMainView);
	D3DXVECTOR3 vPlayerPos = Management->Get_ObjectType(OBJ_PLAYER)[0]->GetPos();
	D3DXMATRIX matPlayerWorld = Management->Get_ObjectType(OBJ_PLAYER)[0]->GetInfo().matWorld;
	D3DXVECTOR3 vWorldPos;
	vPlayerPos.x -= WIN_SIZE_X * 0.5f;
	vPlayerPos.y -= WIN_SIZE_Y * 0.5f;
	D3DXVECTOR3 vDir = vPlayerPos - m_vBeforePos;
	float fSize = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	if (fSize > 2.f)
		m_vBeforePos += vDir * (fSize * 1.8f) * _fTime;
	D3DXMatrixTranslation(&matPos, -m_vBeforePos.x, -m_vBeforePos.y,0);
	matMainView *= matPos;
	m_pDevice->SetTransform(D3DTS_VIEW, &matMainView);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
		return 0;
}

void CCamera::Release()
{
	m_pDevice = NULL;
}
