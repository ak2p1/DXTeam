#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pDevice):
	m_bAttakted(false),
	m_fAnimationTime(0.f),
	m_fAnimationLimitTime(0.1f)
	//m_bLife(true)
{
	m_pDevice = pDevice;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));

	D3DXCreateEffectFromFile(pDevice,
		L"AlphaShader.hlsl", NULL, NULL,
		D3DXSHADER_DEBUG, NULL, &shader, NULL);

	passNum = 1;

}


CMonster::~CMonster()
{
}

void CMonster::Init()
{
	

	pImage = TextureMgr->GetImage(L"Monster1");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	CGameObject* pPlayer = Management->Get_ObjectType(OBJ_PLAYER)[0];
	((CPlayer*)pPlayer)->isAttack();
	m_tInfo.nMonNum= 1;
	m_nHP = 100;

	D3DXVECTOR3 vPlayerPos = Management->Get_ObjectType(OBJ_PLAYER)[0]->GetPos();


	m_tInfo.vPos.x = vPlayerPos.x + 250;
	m_tInfo.vPos.y = vPlayerPos.y - 150;


}

int CMonster::Update(float _fTime)
{
	m_fAnimationTime += _fTime;

	m_tInfo.vScale.x = 1.0f;
	m_tInfo.vScale.y = 1.0f;
	m_tInfo.vScale.z = 1.0f;

	CGameObject* pPlayer = Management->Get_ObjectType(OBJ_PLAYER)[0];

	if (((CPlayer*)pPlayer)->isAttack())
	{
		m_nHP -= 10;
	}

	if (m_nHP <= 0)
	{
		return 1;
	}

	CGameObject::Update();
	
	
	
	return 0;

}


void CMonster::Render()
{

	//if (m_bLife == true)
	
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


