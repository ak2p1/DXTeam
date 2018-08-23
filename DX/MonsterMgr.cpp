#include "stdafx.h"
#include "MonsterMgr.h"
#include "Monster.h"

CMonsterMgr::CMonsterMgr(LPDIRECT3DDEVICE9 pDevice)
{
}

CMonsterMgr::~CMonsterMgr()
{
}

int CMonsterMgr::Update(float _fTime)
{

	return 0;
}

void CMonsterMgr::Render()
{
		
	
}

void CMonsterMgr::Create()
{
	//srand(time(NULL));

	//m_tInfo.nMonNum = (rand() % 3)+1;

	//if (m_tInfo.nMonNum == 1)
	//{
	//	shader->Begin(NULL, NULL);
	//	shader->BeginPass(1);
	//	shader->SetFloatArray("color", (float*)&color, 4);

	//	static int nTemp = 0;
	//	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	//	m_pDevice->SetTexture(0, pImage->pTexInfo[nTemp].pTexture);
	//	CGameObject::SetBuffer(pImage->pTexInfo[nTemp].fWidth, pImage->pTexInfo[nTemp].fHeight);
	//	//알파연산 끝났다.
	//	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);





	//	if (m_fAnimationTime >= m_fAnimationLimitTime)
	//	{
	//		++nTemp;
	//		m_fAnimationTime = 0.f;
	//	}
	//	if (nTemp > 11)
	//		nTemp = 0;

	//	shader->EndPass();
	//	shader->End();
	//}

}

void CMonsterMgr::Die()
{
}
