#pragma once
#include "GameObject.h"
class CUnitObject :
	public CGameObject
{
protected:
	enum eCharacterState
	{
		Attack,
		Critical,
		Move,
		Idle,
		IsHitted
	};

	eCharacterState Player;
	eCharacterState Monster;

	void GetPlayerState(int _case = 0);
public:
	CUnitObject(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CUnitObject();

public:
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;
};

