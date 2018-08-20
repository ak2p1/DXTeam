#pragma once
#include "Bace.h"

class CGameObject :
	public CBase
{
protected:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;

public:
	CGameObject();
	virtual ~CGameObject();

protected:
	void init(bool _isOriginSize = false , float _fWidth = 0.0f, float _fHeight = 0.0f);
	void SetBuffer();

public:
	virtual int Update(float _fTime = 0.0f) override = 0;
	virtual void Render() override = 0;

private:
	void Release();

};

