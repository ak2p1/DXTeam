#pragma once
#include "Player.h"
class CPLayerMana :
	public CPlayer
{
private:
	int			nMana;
	int			nDum;
public:
	CPLayerMana(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CPLayerMana();

public:
	void Init();
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;
	void Release();
};

