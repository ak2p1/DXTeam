#pragma once
#include "UnitObject.h"
class CMonsterMgr :
	public CUnitObject
{

private:
	bool m_bCreated;
	bool m_bLife;
	int m_nMonsterCount;

	LPD3DXEFFECT shader;
	D3DXCOLOR color;
	//int m_nMonsterNum;
public:
	CMonsterMgr(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CMonsterMgr();

public:
	virtual int Update(float _fTime = 0.0f);
	virtual void Render() override;

public:
	void Create();
	void Die();

};

