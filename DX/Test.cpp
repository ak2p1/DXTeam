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

	//���Ŀ����� �����ϰڴ�.
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//���Ŀ����� �ϴµ� �������� �����ϰڴ�.
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	//DEST : �ѷ����� �� ����� ����
	//SRC : �ѷ����� ����
	//SRCALPHA : �Ѹ� ������ ���İ�
	//INVSRCALPHA : 1 - SRCALPHA

	//�� ��� �����ٰ� �Ѹ� ������ ������ ���ϰڴ�.
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�Ѹ� ���򿡴ٰ� �ڱ��ڽ��� ���İ��� ���ϰڴ�.
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	static int nTemp = 0;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo[nTemp].pTexture);
	CGameObject::SetBuffer();
	//���Ŀ��� ������.
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
