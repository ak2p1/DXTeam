#pragma once
#include "GameObject.h"
class CMapObject :
	public CGameObject
{
public:
	CMapObject(LPDIRECT3DDEVICE9 pDevice = NULL);
	~CMapObject();

public:
	virtual int Update(float _fTime = 0.0f) override = 0;
	virtual void Render() override = 0;

private:
	void Release();
};

