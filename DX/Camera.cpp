#include "stdafx.h"
#include "Camera.h"

CCamera::CCamera()
{

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
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

int CCamera::Update()
{
	return 0;
}

void CCamera::Release()
{
	m_pDevice = NULL;
}
