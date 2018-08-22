#pragma once
#include "GameObject.h"
class CMonsterMgr :
	public CGameObject
{

private:
	bool m_bCreated;
	bool m_bLife;
	int m_nMonsterCount;


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

