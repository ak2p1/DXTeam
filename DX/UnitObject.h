#pragma once
#include "GameObject.h"
class CUnitObject :
	public CGameObject
{
public:
	CUnitObject(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CUnitObject();

public:
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;
};

