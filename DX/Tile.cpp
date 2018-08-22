#include "stdafx.h"
#include "Tile.h"

CTile::CTile(LPDIRECT3DDEVICE9 pDevice /*= NULL*/)
{
	m_pDevice = pDevice;
	pImage = NULL;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo)); 
	//D3DXCreateEffectFromFile(m_pDevice, L"TestShader2.hlsl", NULL, NULL, D3DXSHADER_DEBUG, NULL, &shader, NULL);

	//color = { 1,1,1,1 }; //RGB A
}

CTile::~CTile()
{
	Release();
}

void CTile::Init()
{
	pImage = TextureMgr->GetImage(L"Tile");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);
	m_tInfo.vScale.x = m_tInfo.vScale.y = m_tInfo.vScale.z = 1.0f;
	m_tInfo.vPos.x = WIN_SIZE_X * 0.5f;
	m_tInfo.vPos.y = WIN_SIZE_Y * 0.5f;
	m_tInfo.vAngle.z = D3DXToRadian(-10.0f);
}

int CTile::Update(float _fTime /*= 0.0f*/)
{
	//static bool isUp = false;
	//static bool isDown = false;
	//static bool isLeft = false;
	//static bool isRight = false;
	//static int Debug_Moving_X = 0;
	//static int Debug_Moving_Y = 0;

	//if (GetAsyncKeyState(VK_NUMPAD8))
	//{
	//	Debug_Moving_Y -= 1;
	//	isUp = true;
	//}

	//if (GetAsyncKeyState(VK_NUMPAD5))
	//{
	//	Debug_Moving_Y += 1;
	//	isDown = true;
	//}
	//else if (!GetAsyncKeyState(VK_NUMPAD5) && isDown)
	//	isDown = false;

	//if (GetAsyncKeyState(VK_NUMPAD4))
	//{
	//	Debug_Moving_X -= 1;
	//	isLeft = true;
	//}
	//else if (!GetAsyncKeyState(VK_NUMPAD4) && isLeft)
	//	isLeft = false;

	//if (GetAsyncKeyState(VK_NUMPAD6))
	//{
	//	Debug_Moving_X += 1;
	//	isRight = true;
	//}
	//else if (!GetAsyncKeyState(VK_NUMPAD6) && isRight)
	//	isRight = false;

	CGameObject::Update();

	//static float fTemp = 0;
	//static bool isTemp = true;

	//if (isTemp)
	//{
	//	fTemp += _fTime;
	//	if (fTemp >= 1.f)
	//	{
	//		fTemp = 1.0f;
	//		isTemp = false;
	//	}
	//	
	//}
	//else
	//{
	//	fTemp -= _fTime;
	//	if (fTemp <= 0.0f)
	//	{
	//		fTemp = 0.0f;
	//		isTemp = true;
	//	}
	//}
	//
	//color.g = fTemp;
	//color.b = fTemp;

	return 0;
}

void CTile::Render()
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);

	////shader->SetFloatArray("color", (float*)&color, 4);
	//shader->Begin(NULL , NULL);
	//shader->BeginPass(4);
	m_pDevice->SetTexture(0, pImage->pTexInfo->pTexture);
	CGameObject::SetBuffer(pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	//shader->EndPass();
	//shader->End();
}

void CTile::Release()
{
	m_pDevice = NULL;
}
