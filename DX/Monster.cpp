#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pDevice):
	m_nMonsterNum(1),
	m_bAttakted(false),
	m_fAnimationTime(0.f),
	m_fAnimationLimitTime(0.16f)
{
	m_pDevice = pDevice;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}


CMonster::~CMonster()
{
}

void CMonster::Init()
{
	pImage = TextureMgr->GetImage(L"Monster1");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	m_nMonsterNum = 1;
	m_nHP = 100;

	D3DXVECTOR3 vPlayerPos = Management->Get_ObjectType(OBJ_PLAYER)[0]->GetPos();


	m_tInfo.vPos.x =750;
	m_tInfo.vPos.y =250;



}

int CMonster::Update(float _fTime)
{
	m_fAnimationTime += _fTime;

	m_tInfo.vScale.x = 1.0f;
	m_tInfo.vScale.y = 1.0f;
	m_tInfo.vScale.z = 1.0f;


	CGameObject::Update();
	return 0;

}


void CMonster::Render()
{
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//¾ËÆÄ¿¬»êÀ» ÇÏ´Âµ¥ µ¡¼ÀÀ¸·Î ¿¬»êÇÏ°Ú´Ù.
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	//DEST : »Ñ·ÁÁö´Â µÞ ¹è°æÀÇ »ö±ò
	//SRC : »Ñ·ÁÁö´Â »ö±ò
	//SRCALPHA : »Ñ¸± »ö±òÀÇ ¾ËÆÄ°ª
	//INVSRCALPHA : 1 - SRCALPHA

	//µÞ ¹è°æ »ö¿¡´Ù°¡ »Ñ¸± »ö±òÀÇ ¿ª¼ö¸¦ °öÇÏ°Ú´Ù.
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//»Ñ¸± »ö±ò¿¡´Ù°¡ ÀÚ±âÀÚ½ÅÀÇ ¾ËÆÄ°ªÀ» °öÇÏ°Ú´Ù.
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	static int nTemp = 0;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo[nTemp].pTexture);
	CGameObject::SetBuffer(pImage->pTexInfo[nTemp].fWidth , pImage->pTexInfo[nTemp].fHeight);
	//¾ËÆÄ¿¬»ê ³¡³µ´Ù.
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	if (m_fAnimationTime >= m_fAnimationLimitTime)
	{
		++nTemp;
		m_fAnimationTime = 0.f;
	}
	if (nTemp > 11)
		nTemp = 0;
}


