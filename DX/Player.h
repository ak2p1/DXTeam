#pragma once
#include "GameObject.h"
class CPlayer :
	public CGameObject
{
private:
	IMAGE*	pAttackImage;
	IMAGE*	pCriticalImage;
	IMAGE*	pRunImage;
	IMAGE*	pDashImage;

private:
	int			nCritical;
	int			nCriticalPer;

	bool		isRun;
	bool		isInit;
	bool		isDash;

private://Speed
	int			nATKSpeed;
	float		fTime;
	int			nGameSpeed;

	void GameSpeedControl();

private://Click Count
	int			nClickCount;

private:
	//LPD3DXEFFECT	shader;
	//D3DXCOLOR		color;
public:
	CPlayer(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CPlayer();

public:
	void Init();
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;
	void Release();

public:
	void EndImage();
	void KeyInput();
	bool IsBattle(bool _isBattle);
	void PlayerMove();
	void Dash();
};

