#pragma once
#include "Bace.h"

class CGameObject :
	public CBase
{
protected:
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	CGameObject(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CGameObject();

public:
	virtual int Update(float _fTime = 0.0f) override = 0;
	virtual void Render() override = 0;

private:
	void Release();

};

