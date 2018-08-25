#include "stdafx.h"
#include "Monster1.h"
#include "Player.h"

CMonster1::CMonster1(LPDIRECT3DDEVICE9 pDevice):
	m_bAttakted(false),
	m_fAnimationTime(0.f),
	m_fAnimationLimitTime(0.1f)

{
	m_pDevice = pDevice;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));

	D3DXCreateEffectFromFile(pDevice,
		L"AlphaShader.hlsl", NULL, NULL,
		D3DXSHADER_DEBUG, NULL, &shader, NULL);

	passNum = 4;
}

CMonster1::~CMonster1()
{
}

void CMonster1::Init()
{
	pImage = TextureMgr->GetImage(L"Monster2");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	/*CGameObject* pMonster = Management->Get_ObjectType(OBJ_MONSTER)[0];
	((CPlayer*)pMonster)->isAttack();*/
	m_tInfo.nMonNum = 1;
	m_nHP = 100;

	D3DXVECTOR3 vMonsterPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();


	m_tInfo.vPos.x = vMonsterPos.x + 250;
	m_tInfo.vPos.y = vMonsterPos.y - 190;

	m_tInfo.vScale.x = 1.5f;
	m_tInfo.vScale.y = 1.25f;
	m_tInfo.vScale.z = 1.0f;
}

int CMonster1::Update(float _fTime)
{

	m_fAnimationTime += _fTime;


	//CGameObject* pPlayer = Management->Get_ObjectType(OBJ_PLAYER)[0];


	//if (((CPlayer*)pPlayer)->isAttack())
	//{
	//	m_nHP -= 40;
	//}

	if (m_nHP <= 0)
	{
		return 1;
	}

	CGameObject::Update();

	return 0;
}

void CMonster1::Render()
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
	if (nTemp > 17)
		nTemp = 0;

	shader->EndPass();
	shader->End();
}

int CMonster1::Attackted()
{
	
		m_nHP -= 20;

	return 0;
}

int CMonster1::Critical()
{
	m_nHP -= 30;

	return 0;
}
