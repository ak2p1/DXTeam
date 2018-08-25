#include "stdafx.h"
#include "FontRenderer.h"

CFontRenderer::CFontRenderer(LPDIRECT3DDEVICE9 pDevice /*= NULL*/)
{
	m_pDevice = pDevice;
	m_LimitTime = 0.0f;
	memset(szTime, 0, sizeof(szTime));
	isChack = false;
	isMonsterHunting = false;
	m_pShader = NULL;
	dwColor = {1,1,1,1};
	fColorValue = 0.1f;
}

CFontRenderer::~CFontRenderer()
{
	Release();
}

void CFontRenderer::Init()
{
	pImage = TextureMgr->GetImage(L"Font");

	D3DXCreateEffectFromFile(Device->GetDevice(),
		L"UIFontShader.hlsl", NULL, NULL,
		D3DXSHADER_DEBUG, NULL, &m_pShader, NULL);

	CGameObject::init(true, pImage->pTexInfo[0].fWidth, pImage->pTexInfo[0].fHeight);
	m_tInfo.vScale.x = m_tInfo.vScale.y = m_tInfo.vScale.z = 1.f;
	m_tInfo.vPos = { WIN_SIZE_X * 0.5f ,WIN_SIZE_Y * 0.5f , 0.f };
	isMonsterHunting = true;
	m_LimitTime = 33.0f;
}

int CFontRenderer::Update(float _fTime /*= 0.0f*/)
{
	m_fTime = _fTime;
	m_LimitTime -= m_fTime;
	sprintf_s(szTime, "%.1f"  , m_LimitTime);
	m_iLen = strlen(szTime);

	if (m_LimitTime <= 0.0f)
		isMonsterHunting = false;
	else if (m_LimitTime <= 5.0f)
	{
	dwColor.g -= fColorValue;
	dwColor.b -= fColorValue;

	if (dwColor.g <= 0 || dwColor.g >= 1)
		fColorValue *= -1;
	}

	m_tInfo.vPos = 
	{
		Camera->GetPos().x  + (WIN_SIZE_X * 0.5f), 
		Camera->GetPos().y + (WIN_SIZE_Y * 0.1f),
		0.0f
	};

	CGameObject::Update();
	return 0;
}

void CFontRenderer::Render()
{
	if (isMonsterHunting)
	{
		char szNum1[MAX_PATH];
		char *p1 = NULL;
		char *p2 = NULL;
		char *p3 = NULL;
		char *p4 = NULL;
		const char szTemp = '.';
		p1 = strtok_s(szTime, &szTemp, &p3);
		strncpy_s(szNum1, p1, 1);
		p2 = strtok_s(szTime, szNum1, &p4);
		int iNum1 = atoi(szNum1);
		int iNum2 = 0;
		if (p2 != NULL)
			iNum2 = atoi(p2);
		else
			iNum2 = atoi(szNum1);
		int iNum3 = atoi(p3);

		m_pShader->SetFloatArray("vColor", (float*)&dwColor, 4);
		m_pShader->Begin(NULL, NULL);
		m_pShader->BeginPass(0);
	
		if (m_LimitTime > 10.0f)
		{
			m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
			m_pDevice->SetTexture(0, pImage->pTexInfo[iNum1].pTexture);
			CGameObject::SetBuffer(pImage->pTexInfo[iNum1].fWidth, pImage->pTexInfo[iNum1].fHeight);
		}

		memcpy(&m_tInfo.matWorld.m[3][0], D3DXVECTOR3(m_tInfo.vPos.x + 30, m_tInfo.vPos.y, 0.0f), sizeof(D3DXVECTOR3));
		m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
		m_pDevice->SetTexture(0, pImage->pTexInfo[iNum2].pTexture);
		CGameObject::SetBuffer(pImage->pTexInfo[iNum2].fWidth, pImage->pTexInfo[iNum2].fHeight);

		memcpy(&m_tInfo.matWorld.m[3][0], D3DXVECTOR3(m_tInfo.vPos.x + 55, m_tInfo.vPos.y + 14, 0.0f), sizeof(D3DXVECTOR3));
		m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
		m_pDevice->SetTexture(0, pImage->pTexInfo[10].pTexture);
		CGameObject::SetBuffer(pImage->pTexInfo[10].fWidth * 0.5f, pImage->pTexInfo[10].fHeight* 0.5f);

		memcpy(&m_tInfo.matWorld.m[3][0], D3DXVECTOR3(m_tInfo.vPos.x + 80, m_tInfo.vPos.y, 0.0f), sizeof(D3DXVECTOR3));
		m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
		m_pDevice->SetTexture(0, pImage->pTexInfo[iNum3].pTexture);
		CGameObject::SetBuffer(pImage->pTexInfo[iNum3].fWidth, pImage->pTexInfo[iNum3].fHeight);

		m_pShader->EndPass();
		m_pShader->End();
	}
	
}

void CFontRenderer::Release()
{

}
