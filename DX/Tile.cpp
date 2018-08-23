#include "stdafx.h"
#include "Tile.h"
#include "Mouse.h"

CTile::CTile(LPDIRECT3DDEVICE9 pDevice /*= NULL*/)
{
	m_pDevice = pDevice;
	pImage = NULL;
	pSkyImage = NULL;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo)); 
	//ZeroMemory(&m_vTile2Pos, sizeof(m_vTile2Pos));
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
	pSkyImage = TextureMgr->GetImage(L"Sky");
	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);
	m_tInfo.vScale.x = m_tInfo.vScale.y = m_tInfo.vScale.z = 1.0f;
	m_tInfo.vPos.x = WIN_SIZE_X * 0.5f;
	m_tInfo.vPos.y = WIN_SIZE_Y * 0.5f;
	//m_vTile2Pos = { 0,0,0 };
	//m_vTile3Pos = { 0,0,0 };
	m_tInfo.vAngle.z = D3DXToRadian(-10.0f);

	vecPos.push_back(D3DXVECTOR3(WIN_SIZE_X * 0.5f + (404 * 3), WIN_SIZE_Y * 0.5f - (308 * 3), 0.0f));		//1
	vecPos.push_back(D3DXVECTOR3(WIN_SIZE_X * 0.5f + (404 * 2 ), WIN_SIZE_Y * 0.5f - (308 * 2), 0.0f ) );	//2
	vecPos.push_back(D3DXVECTOR3(WIN_SIZE_X * 0.5f + 404 , WIN_SIZE_Y * 0.5f - 308, 0.0f ));						//3
	vecPos.push_back(D3DXVECTOR3(WIN_SIZE_X * 0.5f, WIN_SIZE_Y * 0.5f, 0.0f));												//4

}

int CTile::Update(float _fTime /*= 0.0f*/)
{

	static int nTileInterval = 4;
	D3DXVECTOR3 vPlayerPos = Management->Get_ObjectType(OBJ_PLAYER)[0]->GetPos();
	
	//D3DXVECTOR2 ptMouse = CMouse::GetMousePos();

	float fSize = D3DXVec3Length( &(vecPos[3] - vPlayerPos));

	if (fSize >= 950)
	{
		vecPos[3] = vecPos[2];
		vecPos[2] = vecPos[1];
		vecPos[1] = vecPos[0];
		vecPos[0] = D3DXVECTOR3(WIN_SIZE_X * 0.5f + (404 * nTileInterval), WIN_SIZE_Y * 0.5f - (308 * nTileInterval), 0.0f);
			++nTileInterval;
	}

	static bool isUp = false;
	static bool isDown = false;
	static bool isLeft = false;
	static bool isRight = false;
	static int Debug_Moving_X = 0;
	static int Debug_Moving_Y = 0;

	if (InputMgr->keyPress('I'))
	{
		Debug_Moving_Y -= 1;
	}

	if (InputMgr->keyPress('K'))
	{
		Debug_Moving_Y += 1;
	}

	if (InputMgr->keyPress('J'))
	{
		Debug_Moving_X -= 1;
	}

	if (InputMgr->keyPress('L'))
	{
		Debug_Moving_X += 1;
	}
	//m_vTile2Pos = { (float)Debug_Moving_X  , (float)Debug_Moving_Y , 0};

	//D3DXVECTOR3 vTemp = m_tInfo.vPos - m_vTile2Pos;
	//m_vTile2Pos.x = m_tInfo.vPos.x + 404.0f;
	//m_vTile2Pos.y = m_tInfo.vPos.y - 308.f;
	//cout << vTemp.x << " " << vTemp.y << endl;
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
	D3DXMATRIX matSky;
	D3DXMatrixIdentity(&matSky);
	memcpy(&(matSky.m[3][0]), Camera->GetPos(), sizeof(D3DXVECTOR3));
	m_pDevice->SetTransform(D3DTS_WORLD, &matSky);
	m_pDevice->SetTexture(0, pSkyImage->pTexInfo->pTexture);
	CGameObject::SetBuffer(WIN_SIZE_X * 2.0f , WIN_SIZE_Y* 2.0f);
	////shader->SetFloatArray("color", (float*)&color, 4);
	//shader->Begin(NULL , NULL);
	//shader->BeginPass(4);

	//shader->EndPass();
	//shader->End();

	memcpy( &(m_tInfo.matWorld.m[3][0] ), vecPos[0], sizeof(D3DXVECTOR3));
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo->pTexture);
	CGameObject::SetBuffer(pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	memcpy(&(m_tInfo.matWorld.m[3][0]), vecPos[1], sizeof(D3DXVECTOR3));
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo->pTexture);
	CGameObject::SetBuffer(pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	memcpy(&(m_tInfo.matWorld.m[3][0]), vecPos[2], sizeof(D3DXVECTOR3));
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo->pTexture);
	CGameObject::SetBuffer(pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

	memcpy(&(m_tInfo.matWorld.m[3][0]), vecPos[3], sizeof(D3DXVECTOR3));
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	m_pDevice->SetTexture(0, pImage->pTexInfo->pTexture);
	CGameObject::SetBuffer(pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);

}

void CTile::Release()
{
	m_pDevice = NULL;
}
