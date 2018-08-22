#pragma once
#include "UnitObject.h"
class CPlayer :
	public CUnitObject
{
private:
	IMAGE*	pAttackImage;
	IMAGE*	pCriticalImage;
	IMAGE*	pRunImage;
	IMAGE*	pDashImage;
	IMAGE*	pDashEffectImage;

private:
	int			nCritical;
	int			nCriticalPer;

	bool		isRun;
	bool		isInit;
	bool		isDash;
	bool		isAttacked;

private://Speed
	int			nATKSpeed;
	float		fTime;
	int			nGameSpeed;

	void GameSpeedControl();

private://Click Count
	int			nClickCount;

private://Shader
	LPD3DXEFFECT	shader;
	UINT			passNum;
	D3DXCOLOR		color;

	void CreateShader(wstring fileName, LPD3DXEFFECT * shader);
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

	bool isAttack();
};

