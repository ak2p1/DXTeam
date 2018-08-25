#pragma once
#include "UnitObject.h"

class CMonster1
	: public CUnitObject
{
private:
	int m_nHP;
	bool m_bAttakted;
	float m_fAnimationTime;
	float m_fAnimationLimitTime;
	float attacktedTime;
	float attacktedLimitTime;
	IMAGE * pImage;

	LPD3DXEFFECT shader;
	D3DXCOLOR color;

	float colorValue;
	UINT passNum;
public:
	CMonster1(LPDIRECT3DDEVICE9 pDevice = NULL);
	~CMonster1();



public:
	virtual void Init();
	virtual int Update(float _fTime = 0.0f);
	virtual void Render() override;

public:
	int Attackted();
	int Critical();




};

