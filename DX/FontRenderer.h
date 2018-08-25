#pragma once
#include "GameObject.h"
class CFontRenderer :
	public CGameObject
{
private:
	IMAGE * pImage;
	float m_fTime;
	float m_LimitTime;

	int m_iLen;
	char szTime[MAX_PATH];
	bool isChack;

	bool isMonsterHunting;

	LPD3DXEFFECT	m_pShader;

	D3DXCOLOR dwColor;
	float fColorValue;
public:
	CFontRenderer(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CFontRenderer();

public:
	void Init();
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;

	bool IsHunting()
	{
		return isMonsterHunting;
	}
	
private:
	void Release();

};

