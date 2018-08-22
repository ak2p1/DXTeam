#include "stdafx.h"
#include "Player.h"

static int nTemp = 0;

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

	pAttackImage = TextureMgr->GetImage(L"PlayerAttack");
	pCriticalImage = TextureMgr->GetImage(L"PlayerCritical");
	pRunImage = TextureMgr->GetImage(L"PlayerRun");
	pDashImage = TextureMgr->GetImage(L"PlayerDash");
	CGameObject::init(true, pRunImage->pTexInfo[0].fWidth, pRunImage->pTexInfo[0].fHeight);

	m_tInfo.vPos.x = 500.0f;
	m_tInfo.vPos.y = 400.0f;
}

int CPlayer::Update(float _fTime)
{
	fTime += _fTime;

	m_tInfo.vScale.x = 1.0f;
	m_tInfo.vScale.y = 1.0f;
	m_tInfo.vScale.z = 1.0f;

	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matPos;
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixRotationX(&matRotX, m_tInfo.vAngle.x);
	D3DXMatrixRotationY(&matRotY, m_tInfo.vAngle.y);
	D3DXMatrixRotationZ(&matRotZ, m_tInfo.vAngle.z);
	D3DXMatrixTranslation(&matPos, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

	m_tInfo.matWorld = matScale * matRotX * matRotY * matRotZ * matPos;
	return 0;
}

void CPlayer::Render()
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
	GameSpeedControl();
	KeyInput();

	if (!isRun)
	{
		if (nCritical < 10 + nCriticalPer)
		{
			if (!isInit) CGameObject::init(true, pCriticalImage->pTexInfo[0].fWidth, pCriticalImage->pTexInfo[0].fHeight);
			m_pDevice->SetTexture(0, pCriticalImage->pTexInfo[nTemp].pTexture);
		}
		else
		{
			nCritical = 1500;
			if (!isInit) CGameObject::init(true, pAttackImage->pTexInfo[0].fWidth, pAttackImage->pTexInfo[0].fHeight);
			m_pDevice->SetTexture(0, pAttackImage->pTexInfo[nTemp].pTexture);
		}

		if (nClickCount > 0)
			nTemp += 4;

		if (nTemp > 62)
			EndImage();
	}
	else
	{
		if (nClickCount == 0)
		{
			if (!isInit) CGameObject::init(true, pRunImage->pTexInfo[0].fWidth, pRunImage->pTexInfo[0].fHeight);
			m_pDevice->SetTexture(0, pRunImage->pTexInfo[nTemp].pTexture);
		}
	}
	CGameObject::SetBuffer();
	cout << nClickCount << endl;

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

}

void CPlayer::EndImage()
{
	nTemp = 0;
	nCritical = rand() % 100;

	if(!isRun) isRun = true;
	else isRun = false;

	isInit = false;
}

void CPlayer::KeyInput()
{
	if (InputMgr->KeyDown(VK_UP)) nGameSpeed++;
	if (InputMgr->KeyDown(VK_DOWN)) nGameSpeed--;
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
	m_tInfo.vPos.x += 1;
	m_tInfo.vPos.y -= 1;
}

void CPlayer::Dash()
{
	if (!isRun) return;

	if (!isInit) CGameObject::init(true, pDashImage->pTexInfo[0].fWidth, pDashImage->pTexInfo[0].fHeight);
	m_pDevice->SetTexture(0, pDashImage->pTexInfo[nTemp].pTexture);
	if (isDash)
	{
		if (nTemp < 5)
		{
			m_tInfo.vPos.x += 100;
			m_tInfo.vPos.y -= 100;
		}
		isDash = false;
	}
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
				Dash();

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
