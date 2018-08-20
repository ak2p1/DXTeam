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
	
	pImage = TextureMgr->GetImage(L"Player");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth , pImage->pTexInfo[0].fHeight);
}

int CTest::Update(float _fTime /*= 0.0f*/)
{
	m_tInfo.vScale.x = 1.0f;
	m_tInfo.vScale.y = 1.0f;
	m_tInfo.vScale.z = 1.0f;
	

	//m_tInfo.vAngle.x = m_tInfo.vAngle.y = m_tInfo.vAngle.z = 1.0f;
	m_tInfo.vPos.x = m_tInfo.vPos.y = 500.0f;

	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matPos;
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixRotationX(&matRotX, m_tInfo.vAngle.x);
	D3DXMatrixRotationY(&matRotY, m_tInfo.vAngle.y);
	D3DXMatrixRotationZ(&matRotZ, m_tInfo.vAngle.z);
	D3DXMatrixTranslation(&matPos, m_tInfo.vPos.x, m_tInfo.vPos.y,0);

	m_tInfo.matWorld = matScale * matRotX * matRotY * matRotZ * matPos;
	return 0;
}

void CTest::Render()
{

	//알파연산을 시작하겠다.
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//알파연산을 하는데 덧셈으로 연산하겠다.
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	//DEST : 뿌려지는 뒷 배경의 색깔
	//SRC : 뿌려지는 색깔
	//SRCALPHA : 뿌릴 색깔의 알파값
	//INVSRCALPHA : 1 - SRCALPHA

	//뒷 배경 색에다가 뿌릴 색깔의 역수를 곱하겠다.
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//뿌릴 색깔에다가 자기자신의 알파값을 곱하겠다.
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	static int nTemp = 0;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo[nTemp].pTexture);
	CGameObject::SetBuffer();
	//알파연산 끝났다.
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	

	++nTemp;

	if (nTemp > 37)
		nTemp = 0;

}

void CTest::Release()
{
	pImage = NULL;
	m_pDevice = NULL;
}
