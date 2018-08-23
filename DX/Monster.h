#pragma once
#include "MonsterMgr.h"
class CMonster :
	public CMonsterMgr
{
private:

	
	int m_nHP;
	bool m_bAttakted;
	float m_fAnimationTime;
	float m_fAnimationLimitTime;
	IMAGE * pImage;

	LPD3DXEFFECT shader;
	D3DXCOLOR color;

	float colorValue;
	UINT passNum;

	bool m_bLife;



public:
	CMonster(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CMonster();

public:
	virtual void Init();
	virtual int Update(float _fTime = 0.0f);
	virtual void Render() override;

};

