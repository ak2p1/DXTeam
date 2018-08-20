#include "stdafx.h"
#include "Management.h"
#include "GameObject.h"
#include "Test.h"

CManagement::CManagement()
{
}


CManagement::~CManagement()
{
	Release();
}
void CManagement::Init()
{

}

int CManagement::Update(float _fTime /*= 0.0f*/)
{
	for (DWORD i = 0; i < OBJ_END; ++i)
	{
		for (DWORD j = 0 ; j < vecObjectUpdate[i].size() ; ++j)
		{
			vecObjectUpdate[i][j]->Update(_fTime);
		}
	}
	return 0;
}

void CManagement::Render()
{
	//¿”Ω√ ∑ª¥ı∏µ
	//Y º“∆√ ∞ÌπŒ¡ﬂ
	for (DWORD i = 0; i < OBJ_END; ++i)
	{
		for (DWORD j = 0; j < vecRenderer[i].size(); ++j)
		{
			vecRenderer[i][j]->Render();
		}
	}
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
