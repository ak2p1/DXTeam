#pragma once
#include "MapObject.h"
class CTile :
	public CMapObject
{
private:
	IMAGE * pImage;
	IMAGE * pSkyImage;

	vector<D3DXVECTOR3> vecPos;
public:
	CTile(LPDIRECT3DDEVICE9 pDevice = NULL);
	virtual ~CTile();

public:
	void Init();
	virtual int Update(float _fTime = 0.0f) override;
	virtual void Render() override;

private:
	void Release();
};

