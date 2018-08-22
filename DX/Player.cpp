#include "stdafx.h"
#include "Player.h"

static int nTemp = 0;

void CPlayer::CreateShader(wstring fileName, LPD3DXEFFECT * shader)
{
	HRESULT result = D3DXCreateEffectFromFile(Device->GetDevice(),
		fileName.c_str(), NULL, NULL,
		D3DXSHADER_DEBUG, NULL, shader, NULL);
	//D3DXCreateEffectFromFile(Device->GetDevice(),\
		L"ColorShader.hlsl", NULL, NULL,\
		D3DXSHADER_DEBUG, NULL, shader, NULL);
}

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init()
{
	nCritical = 0;
	nATKSpeed = 1;
	nGameSpeed = 10;
	nCriticalPer = 0;
	isRun = true;
	isInit = false;
	isAttacked = false;

	CreateShader(L"AlphaShader.hlsl", &shader);
	passNum = 4;

	pAttackImage = TextureMgr->GetImage(L"PlayerAttack");
	pCriticalImage = TextureMgr->GetImage(L"PlayerCritical");
	pRunImage = TextureMgr->GetImage(L"PlayerRun");
	pDashImage = TextureMgr->GetImage(L"PlayerDash");
	pDashEffectImage = TextureMgr->GetImage(L"PlayerDashEffect");

	CGameObject::init(false, pRunImage->pTexInfo[0].fWidth, pRunImage->pTexInfo[0].fHeight);

	m_tInfo.vPos.x = 500.0f;
	m_tInfo.vPos.y = 400.0f;
}

int CPlayer::Update(float _fTime)
{
	KeyInput();

	D3DXVECTOR3 vEnermyPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();
	if (m_tInfo.vPos.x >= vEnermyPos.x - 50)
		IsBattle(true);

	fTime += _fTime;
	m_tInfo.vScale.x = 1.0f;
	m_tInfo.vScale.y = 1.0f;
	m_tInfo.vScale.z = 1.0f;

	CGameObject::Update();
	return 0;
}

void CPlayer::Render()
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	GameSpeedControl();

	if (!isRun)
	{
		if (nCritical < 10 + nCriticalPer)
		{
			shader->Begin(NULL, NULL);
			shader->BeginPass(passNum);
			
			m_pDevice->SetTexture(0, pCriticalImage->pTexInfo[nTemp].pTexture);
			CGameObject::SetBuffer(pCriticalImage->pTexInfo[0].fWidth, pCriticalImage->pTexInfo[0].fHeight);
			
			shader->EndPass();
			shader->End();

			if (nTemp == 31)
			{
				isAttacked = true;
				GetPlayerState(2);
			}
			else
			{ 
				isAttacked = false;
				GetPlayerState(0);
			}
		}
		else
		{
			nCritical = 1500;
			m_pDevice->SetTexture(0, pAttackImage->pTexInfo[nTemp].pTexture);
			CGameObject::SetBuffer(pAttackImage->pTexInfo[0].fWidth, pAttackImage->pTexInfo[0].fHeight);

			if (nTemp == 28) { isAttacked = true; GetPlayerState(1); }
			else { isAttacked = false; GetPlayerState(0); }
		}

		if (nClickCount > 0)
		{
			nTemp += 4;
		}

		if (nTemp > 62)
			EndImage();
	}
	else
	{
		GetPlayerState(3);
		if (nClickCount == 0)
		{
			m_pDevice->SetTexture(0, pRunImage->pTexInfo[nTemp].pTexture);
			CGameObject::SetBuffer(pRunImage->pTexInfo[0].fWidth, pRunImage->pTexInfo[0].fHeight);
		}
		else Dash();
	}
	//CGameObject::SetBuffer();

}

void CPlayer::Release()
{
	m_pDevice = NULL;
	pAttackImage = NULL;
	pCriticalImage = NULL;
	pRunImage = NULL;
	pDashImage = NULL;

	nClickCount = NULL;
	isRun = NULL;
	isDash = NULL;
	nCriticalPer = NULL;
	isInit = NULL;

	nATKSpeed = NULL;
	fTime = NULL;
	nGameSpeed = NULL;

	nClickCount = NULL;
	pDashEffectImage = NULL;
}

void CPlayer::EndImage()
{
	nTemp = 0;
	nCritical = rand() % 100;
	if (nClickCount > 0)
		nClickCount--;
	isInit = false;
}

void CPlayer::KeyInput()
{
	if (InputMgr->KeyDown(VK_UP)) nGameSpeed+=3;
	if (InputMgr->KeyDown(VK_DOWN)) nGameSpeed-=3;
	if (InputMgr->KeyDown('Q')) nCriticalPer += 5;
	if (InputMgr->KeyDown(VK_SPACE)) nClickCount++;
}

bool CPlayer::IsBattle(bool _isBattle)
{
	if (_isBattle) return isRun = false;
	else isRun = true;
	return false;
}

void CPlayer::PlayerMove()
{
	m_tInfo.vPos.x += 1.4;
	m_tInfo.vPos.y -= 1;
}

void CPlayer::Dash()
{
	if (!isRun) return;
	int i = nTemp / 3 + 1;

	if (!isInit)	//모션 한가지가 뭐든지간에 끝난 후 isInit을 들어옴
	{
		m_pDevice->SetTexture(0, pDashImage->pTexInfo[nTemp].pTexture);
		CGameObject::SetBuffer( pDashImage->pTexInfo[nTemp].fWidth , pDashImage->pTexInfo[nTemp].fHeight);

		
		m_pDevice->SetTexture(0, pDashEffectImage->pTexInfo[i].pTexture);
		CGameObject::SetBuffer(pDashEffectImage->pTexInfo[i].fWidth, pDashEffectImage->pTexInfo[i].fHeight);
	}
		
	
	if (isDash)
	{
		if (nTemp < 5)
		{
			D3DXVECTOR3 vEnermyPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();

			m_tInfo.vPos.x = vEnermyPos.x - 50;
			m_tInfo.vPos.y = vEnermyPos.y + 0;
		}
		isDash = false;
	}
}

bool CPlayer::isAttack()
{
	return isAttacked;
}

void CPlayer::GameSpeedControl()
{
	if (fTime * nGameSpeed >= nATKSpeed)
	{
		if(nTemp == 0)
			isDash = true;
		nTemp++;
		if (nTemp > 63) nTemp = 0;
		if (isRun)
		{

			if (nClickCount > 0)
			{
				if (nTemp > 62)
				{
					EndImage();
					nClickCount--;
					if (nClickCount < 0) nClickCount = 0;
				}
			}
			else
			{
				PlayerMove();

				if (nTemp > 36) {
					EndImage();
				}
			}
		}
		fTime = 0.0f;
	}
}
