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
	isMoveInit = false;
	isCriticalEffect = false;
	isAttackEffect = false;

	CreateShader(L"AlphaShader.hlsl", &shader);
	passNum = 4;

	pAttackImage = TextureMgr->GetImage(L"PlayerAttack");
	pAttackEffectImage = TextureMgr->GetImage(L"PlayerAttackEffect");
	pCriticalImage = TextureMgr->GetImage(L"PlayerCritical");
	pCriticalEffectImage = TextureMgr->GetImage(L"PlayerCriticalEffect");
	pRunImage = TextureMgr->GetImage(L"PlayerRun");
	pDashImage = TextureMgr->GetImage(L"PlayerDash");
	pDashEffectImage = TextureMgr->GetImage(L"PlayerDashEffect");

	CGameObject::init(false, pRunImage->pTexInfo[0].fWidth, pRunImage->pTexInfo[0].fHeight);

	m_tInfo.vPos.x = 350.0f;
	m_tInfo.vPos.y = 400.0f;
}

int CPlayer::Update(float _fTime)
{
	KeyInput();

	D3DXVECTOR3 vEnermyPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();
	if (m_tInfo.vPos.x >= vEnermyPos.x - 85)
		IsBattle(true);
	else
		IsBattle(false);
	fTime += _fTime;
	fRunTime = _fTime;
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

	if (!isRun && !isDashEffect)
	{
		if (nCritical < 10 + nCriticalPer)
		{


			shader->Begin(NULL, NULL);
			shader->BeginPass(passNum);
			CriticalEffect();

			m_pDevice->SetTexture(0, pCriticalImage->pTexInfo[nTemp].pTexture);
			CGameObject::SetBuffer(pCriticalImage->pTexInfo[0].fWidth, pCriticalImage->pTexInfo[0].fHeight);
			
			shader->EndPass();
			shader->End();
			if (nTemp == 31)
			{
				isAttacked = true;
				GetPlayerState(2);
				isCriticalEffect = true;
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
			shader->Begin(NULL, NULL);
			shader->BeginPass(passNum);
			AttackEffect();
			shader->EndPass();
			shader->End();
			m_pDevice->SetTexture(0, pAttackImage->pTexInfo[nTemp].pTexture);
			CGameObject::SetBuffer(pAttackImage->pTexInfo[0].fWidth, pAttackImage->pTexInfo[0].fHeight);
			if (nTemp == 28) { isAttacked = true; GetPlayerState(1); isAttackEffect = true; }
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
		else { isDashEffect = true; Dash(); DashEffect(); }
		if(nTemp > 35)
			EndImage();
	}

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
	isMoveInit = NULL;
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
	if (InputMgr->KeyDown(VK_UP)) nGameSpeed+=2;
	if (InputMgr->KeyDown(VK_DOWN)) nGameSpeed-+2;

	if (InputMgr->KeyDown(VK_UP)) nGameSpeed+=5;
	if (InputMgr->KeyDown(VK_DOWN)) nGameSpeed--;

	if (InputMgr->KeyDown(VK_UP)) nGameSpeed+=3;
	if (InputMgr->KeyDown(VK_DOWN)) nGameSpeed-=3;

	if (InputMgr->KeyDown('Q')) nCriticalPer += 5;
	if (InputMgr->KeyDown(VK_SPACE)) nClickCount++;
}

bool CPlayer::IsBattle(bool _isBattle)
{
	if (!isDashEffect)
	{
		if (_isBattle) return isRun = false;
		else isRun = true;
	}
	return true;
}

void CPlayer::PlayerMove()
{
	D3DXVECTOR3 vDir = { 0.5674f,-0.4326f,0.0f };
	if (isMoveInit)
	{
		m_tInfo.vPos += vDir * 1550 * fRunTime;
	}
	isMoveInit = true;
}

void CPlayer::Dash()
{

	if (!isRun) return;

	if (!isInit)	//모션 한가지가 뭐든지간에 끝난 후 isInit을 들어옴
	{
		m_pDevice->SetTexture(0, pDashImage->pTexInfo[nTemp].pTexture);
		CGameObject::SetBuffer( pDashImage->pTexInfo[nTemp].fWidth , pDashImage->pTexInfo[nTemp].fHeight);

	}
	//if (isDash)
	{
		
		D3DXVECTOR3 vEnermyPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();
		isDash = false;

		{
			m_tInfo.vPos.x = vEnermyPos.x - 80;
			m_tInfo.vPos.y = vEnermyPos.y + 20;
		}
	}
}

void CPlayer::DashEffect()
{
	int i = nTemp / 2 + 1;
	INFO info;
	if (isDashEffect)
	{
		info.vPos.x = m_tInfo.vPos.x - 90;
		info.vPos.y = m_tInfo.vPos.y + 110;
		float fAngleZ = D3DXToRadian(-44.f);
		D3DXMATRIX matEffectAngle , matEffectPos;
		D3DXMatrixIdentity(&matEffectAngle);
		D3DXMatrixIdentity(&matEffectPos);
		D3DXMatrixRotationZ(&matEffectAngle, D3DXToRadian(-45.f));
		D3DXMatrixTranslation(&matEffectPos, info.vPos.x, info.vPos.y, 0.0f);
		info.matWorld = matEffectAngle * matEffectPos;
		m_pDevice->SetTransform(D3DTS_WORLD, &info.matWorld);
		m_pDevice->SetTexture(0, pDashEffectImage->pTexInfo[i].pTexture);
		CGameObject::SetBuffer(pDashEffectImage->pTexInfo[i].fWidth * 2, pDashEffectImage->pTexInfo[i].fHeight);

		if (i > 15)
			isDashEffect = false;
	}
}

void CPlayer::AttackEffect()
{
	int i = nTemp / 9 - 1;
	INFO info;
	D3DXMATRIX matEffectPos;
	if (isAttackEffect)
	{
		if (i >= 10 || i < 0)
		{
			isAttackEffect = false;
			return;
		}
		D3DXVECTOR3 vEnermyPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();
		info.vPos = vEnermyPos;
		info.vPos.y = vEnermyPos.y + 83;
		D3DXMatrixIdentity(&matEffectPos);
		D3DXMatrixTranslation(&matEffectPos, info.vPos.x, info.vPos.y, 0.0f);
		info.matWorld = matEffectPos;
		m_pDevice->SetTransform(D3DTS_WORLD, &info.matWorld);
		m_pDevice->SetTexture(0, pAttackEffectImage->pTexInfo[i].pTexture);
		CGameObject::SetBuffer(pAttackEffectImage->pTexInfo[i].fWidth / 3 * 2, pAttackEffectImage->pTexInfo[i].fHeight / 5 * 3);
	}
	D3DXMatrixTranslation(&matEffectPos, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.0f);
	m_tInfo.matWorld = matEffectPos;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
}

void CPlayer::CriticalEffect()
{
	int i = nTemp / 11 - 1;
	INFO info;
	D3DXMATRIX matEffectPos;
	if (isCriticalEffect)
	{
		if (i >= 7 || i < 0)
		{
			isCriticalEffect = false;
			return;
		}
		D3DXVECTOR3 vEnermyPos = Management->Get_ObjectType(OBJ_MONSTER)[0]->GetPos();
		info.vPos = vEnermyPos;
		D3DXMatrixIdentity(&matEffectPos);
		D3DXMatrixTranslation(&matEffectPos, info.vPos.x, info.vPos.y, 0.0f);
		info.matWorld = matEffectPos;
		m_pDevice->SetTransform(D3DTS_WORLD, &info.matWorld);
		m_pDevice->SetTexture(0, pCriticalEffectImage->pTexInfo[i].pTexture);
		CGameObject::SetBuffer(pCriticalEffectImage->pTexInfo[i].fWidth * 2, pCriticalEffectImage->pTexInfo[i].fHeight * 1.5);
	}
	D3DXMatrixTranslation(&matEffectPos, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.0f);
	m_tInfo.matWorld = matEffectPos;
	m_pDevice->SetTransform(D3DTS_WORLD, &m_tInfo.matWorld);
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
			if (isDashEffect && isDash) nTemp = 0;
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
