#pragma once
#include "GameObject.h"
class CUIObject :
	public CGameObject
{
public:
	CUIObject(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CUIObject();

public:
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;
};

