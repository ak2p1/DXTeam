#include "stdafx.h"
#include "UnitObject.h"

CUnitObject::CUnitObject(LPDIRECT3DDEVICE9 pDevice)
{

}

CUnitObject::~CUnitObject()
{
}

int CUnitObject::Update(float _fTime /*= 0.0f*/)
{
	return 0;
}

void CUnitObject::Render()
{

}

void CUnitObject::GetPlayerState(int _case)
{
	switch (_case)
	{
	case 0:
		Player = Idle;
		break;
	case 1:
		Player = Attack;
		break;
	case 2:
		Player = Critical;
		break;
	case 3:
		Player = Move;
		break;
	default:
		break;
	}
}
