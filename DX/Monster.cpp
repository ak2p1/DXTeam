#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pDevice):
	m_bAttakted(false),
	m_fAnimationTime(0.f),
	m_fAnimationLimitTime(0.1f),
	attacktedTime(0.f),
	attacktedLimitTime(0.3f),
	m_bLife(true)

{
	m_pDevice = pDevice;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));

	D3DXCreateEffectFromFile(pDevice,
		L"AlphaShader.hlsl", NULL, NULL,
		D3DXSHADER_DEBUG, NULL, &shader, NULL);

	passNum = 4;

}


CMonster::~CMonster()
{
}

void CMonster::Init(bool isFirst)
{
	
	
	pImage = TextureMgr->GetImage(L"Monster1");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);
	pImage1 = TextureMgr->GetImage(L"Monster1Die");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	
	CGameObject* pPlayer = Management->Get_ObjectType(OBJ_PLAYER)[0];
	m_tInfo.nMonNum= 1;
	m_nHP = 180;


	D3DXVECTOR3 vPlayerPos = Management->Get_ObjectType(OBJ_PLAYER)[0]->GetPos();
	if (isFirst)
	{
		m_tInfo.vPos.x = vPlayerPos.x + 250;
		m_tInfo.vPos.y = vPlayerPos.y - 150;
	}

	else
	{
		D3DXVECTOR3 vMonsterPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();
		m_tInfo.vPos.x = vMonsterPos.x + 250;
		m_tInfo.vPos.y = vMonsterPos.y - 190;
	}
	m_tInfo.vScale.x = 1.5f;
	m_tInfo.vScale.y = 1.25f;
	m_tInfo.vScale.z = 1.0f;

	
}

int CMonster::Update(float _fTime)
{
	m_fAnimationTime += _fTime;
	attacktedTime += _fTime;

	if (m_nHP <= 0)
	{	
		m_bLife = false;
		return 1;
	}

	

	cout << m_nHP << endl;


	CGameObject::Update();
	
	
	
	return 0;

}


void CMonster::Render()
{
	if (m_bLife)
	{
		shader->Begin(NULL, NULL);
		shader->BeginPass(passNum);

		static int nTemp = 0;
		m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
		m_pDevice->SetTexture(0, pImage->pTexInfo[nTemp].pTexture);
		CGameObject::SetBuffer(pImage->pTexInfo[nTemp].fWidth, pImage->pTexInfo[nTemp].fHeight);

		if (m_fAnimationTime >= m_fAnimationLimitTime)
		{
			++nTemp;
			m_fAnimationTime = 0.f;
		}
		if (nTemp > 27)
			nTemp = 0;

		shader->EndPass();
		shader->End();
	}

	else
	{
		shader->Begin(NULL, NULL);
		shader->BeginPass(passNum);

		static int nTemp = 0;
		m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
		m_pDevice->SetTexture(0, pImage1->pTexInfo[nTemp].pTexture);
		CGameObject::SetBuffer(pImage1->pTexInfo[nTemp].fWidth, pImage1->pTexInfo[nTemp].fHeight);

		if (m_fAnimationTime >= m_fAnimationLimitTime)
		{
			++nTemp;
			m_fAnimationTime = 0.f;
		}
		if (nTemp > 34)
			nTemp = 0;

		shader->EndPass();
		shader->End();
	}
}

int CMonster::Attackted()
{
	
	m_nHP -= 20;
	return 0;
}

int CMonster::Critical()
{
	m_nHP -= 30;
	return 0;
}



