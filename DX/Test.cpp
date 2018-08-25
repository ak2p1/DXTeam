#include "stdafx.h"
#include "Test.h"

CTest::CTest(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	pImage = NULL;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}

CTest::~CTest()
{
	Release();
}

void CTest::Init()
{
	pImage = TextureMgr->GetImage(L"Player");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth , pImage->pTexInfo[0].fHeight);
	m_tInfo.vScale.x = m_tInfo.vScale.y = m_tInfo.vScale.z = 1.f;
	m_tInfo.vPos = {WIN_SIZE_X * 0.5f ,WIN_SIZE_Y * 0.5f , 0.f };
}

int CTest::Update(float _fTime /*= 0.0f*/)
{
	m_fTime = _fTime;
	D3DXVECTOR3 vDir = { 0.5f,-0.5f,0.0f };
	if (InputMgr->keyPress(VK_UP))
	{
		m_tInfo.vPos += vDir * 300 * _fTime;
	}
	if (InputMgr->keyPress(VK_DOWN))
	{
		m_tInfo.vPos -= vDir * 300 * _fTime;
	}
	CGameObject::Update();
	return 0;
}

void CTest::Render()
{
	static int nTemp = 0;
	static float fTime = 0.0f;

	fTime += m_fTime;

	if (fTime > 0.01f)
	{
		fTime = 0.0f;
		++nTemp;
		if (nTemp >= pImage->dwMaxCnt)
		{
			nTemp = 0;
		}
	}
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	//m_pDevice->SetTexture(0, pImage->pTexInfo[nTemp].pTexture);
	//CGameObject::SetBuffer();
}

void CTest::Release()
{
	pImage = NULL;
	m_pDevice = NULL;
}
