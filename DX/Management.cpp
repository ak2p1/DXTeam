#include "stdafx.h"
#include "Management.h"
#include "GameObject.h"
#include "Test.h"
#include "Player.h"
#include "Monster.h"

CManagement::CManagement()
{
}


CManagement::~CManagement()
{
	Release();
}

void CManagement::Init(LPDIRECT3DDEVICE9 _pDevice)
{
	m_bMonsterCreate = false;
	m_pDevice = _pDevice;
}

int CManagement::Update(float _fTime /*= 0.0f*/)
{
	for (DWORD i = 0; i < OBJ_END; ++i)
	{
		for (DWORD j = 0 ; j < vecObjectUpdate[i].size() ; ++j)
		{
			
			int nNum = vecObjectUpdate[i][j]->Update(_fTime);
			if (nNum == 1)
			{
				m_bMonsterCreate = true;
			}
		
		}
	}

	if (m_bMonsterCreate)
	{
		SAFE_DELETE(vecObjectUpdate[OBJ_MONSTER][0]);
		vecObjectUpdate[OBJ_MONSTER][0] = vecObjectUpdate[OBJ_MONSTER][1];
		vecRenderer[OBJ_MONSTER][0] = vecObjectUpdate[OBJ_MONSTER][1];
		CGameObject* pMonster = NULL;
		int nTemp = (rand() % 3); // 0, 1,2,3 
		switch (nTemp)
		{
		case 0:
		{
			pMonster = new CMonster(Device->GetDevice());
			((CMonster*)pMonster)->Init();
			break;
		}
		case 1:
		{
			
				pMonster = new CMonster(Device->GetDevice());
				((CMonster*)pMonster)->Init();
				break;
			
		}
		case 2:
		{
			pMonster = new CMonster(Device->GetDevice());
			((CMonster*)pMonster)->Init();
			break;
		}
		case 3:
		{
			pMonster = new CMonster(Device->GetDevice());
			((CMonster*)pMonster)->Init();
			break;
		}
		default:
			break;
		}
		
		if (pMonster != NULL)
		{
			vecObjectUpdate[OBJ_MONSTER][1] = pMonster;
			vecRenderer[OBJ_MONSTER][1] = pMonster;
			return 0;
		}
	}
	return 0;
}

void CManagement::Render()
{
	//ÀÓ½Ã ·»´õ¸µ
	//Y ¼ÒÆÃ °í¹ÎÁß
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
 	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (DWORD i = 0; i < OBJ_END; ++i)
	{
		for (DWORD j = 0; j < vecRenderer[i].size(); ++j)
		{
			vecRenderer[i][j]->Render();
		}
	}


	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CManagement::Release()
{
	for (DWORD i = 0 ; i < OBJ_END; ++i)
	{
		for (auto P : vecObjectUpdate[i])
		{
			SAFE_DELETE(P);
		}
		vecObjectUpdate[i].clear();
	}
	for (int i = 0; i < OBJ_END; ++i)
	{
		vecRenderer[i].clear();
	}
}

void CManagement::Add_Object(CGameObject* _pObject, eObjectType _eType)
{
	if(NULL != _pObject)
	{
		vecObjectUpdate[_eType].push_back(_pObject);
		vecRenderer[_eType].push_back(_pObject);
	}
	
}


