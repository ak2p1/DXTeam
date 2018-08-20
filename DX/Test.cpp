#include "stdafx.h"
#include "Test.h"

CTest::CTest(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}

CTest::~CTest()
{
	Release();
}

void CTest::Init()
{
	CGameObject::init();
	pImage = TextureMgr->GetImage(L"Player");

}

int CTest::Update(float _fTime /*= 0.0f*/)
{
	m_tInfo.vScale.x = m_tInfo.vScale.y = m_tInfo.vScale.z = 10.0f;
	m_tInfo.vAngle.x = m_tInfo.vAngle.y = m_tInfo.vAngle.z = 1.0f;
	m_tInfo.vPos.x = m_tInfo.vPos.y = 500.0f;

	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matPos;
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixRotationX(&matRotX, m_tInfo.vAngle.x);
	D3DXMatrixRotationY(&matRotY, m_tInfo.vAngle.y);
	D3DXMatrixRotationZ(&matRotZ, m_tInfo.vAngle.z);
	D3DXMatrixTranslation(&matPos, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);

	m_tInfo.matWorld = matScale * matRotX * matRotY * matRotZ * matPos;
	return 0;
}

void CTest::Render()
{
	static int nTemp = 0;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo->pTexture);
	CGameObject::SetBuffer();
	++nTemp;

	if (nTemp > 37)
		nTemp = 0;

}

void CTest::Release()
{
	pImage = NULL;
	m_pDevice = NULL;
}
