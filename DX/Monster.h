#pragma once
#include "UnitObject.h"
class CMonster
	: public CUnitObject
{
private:

	
	int m_nHP;
	bool m_bAttakted;
	float m_fAnimationTime;
	float m_fAnimationLimitTime;
	IMAGE * pImage;
	IMAGE * pImage1;


	LPD3DXEFFECT shader;
	D3DXCOLOR color;

	float colorValue;
	UINT passNum;

	bool m_bLife;
	bool m_bFirstLocation;

	float attacktedTime;
	float attacktedLimitTime;

public:
	CMonster(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CMonster();

public:
	void Init(bool isFirst);
	virtual int Update(float _fTime = 0.0f);
	virtual void Render() override;


public :
	int Attackted();
	int Critical();
public:
	

};

