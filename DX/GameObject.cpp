#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	:m_pDevice(pDevice)
{
	
}

CGameObject::~CGameObject()
{
	Release();
}

void CGameObject::Release()
{
	DWORD dwDeviceRefCount = m_pDevice->Release();
	m_pDevice = NULL;
}
