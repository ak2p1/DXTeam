#pragma once
#include "GameObject.h"
class CTest :
	public CGameObject
{
private:
	IMAGE * pImage;
	INFO m_tInfo;
public:
	CTest(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CTest();

public:
	void Init();
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;
	void Release();

};

