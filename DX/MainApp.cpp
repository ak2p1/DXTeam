#include "stdafx.h"
#include "MainApp.h"
#include "Test.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "FontRenderer.h"
#include "Monster1.h"

CMainApp::CMainApp()
	:m_pDevice(NULL)
{
	#ifdef DEBUG_MODE
		FILE* pFile = NULL;
		AllocConsole();
		freopen_s(&pFile, "CONOUT$", "wt", stdout);
		SetConsoleTitleA("Debug");
	#endif
}

CMainApp::~CMainApp()
{
	#ifdef DEBUG_MODE
		FreeConsole();
	#endif

	Release();
}

void CMainApp::Init()
{
	srand(unsigned int(time(NULL)));
	//����̽� �ʱ�ȭ
	Device->Init();
	m_pDevice = Device->GetDevice();

	//��ǲ �Ŵ��� �ʱ�ȭ
	InputMgr->Init();

	//Ÿ�� �Ŵ��� �ʱ�ȭ
	TimeMgr->Init();

	//�ؽ��� �Ŵ��� �ʱ�ȭ
	TextureMgr->Init(m_pDevice);

	//ī�޶� �ʱ�ȭ
	Camera->Init(m_pDevice);

	//�Ŵ�����Ʈ �ʱ�ȭ
	Management->Init(m_pDevice);

	TextureMgr->Add_Texture(L"PlayerAttack", L"Textrue/PlayerMotion/Attack1/", TEX_MULTI, 65);
	TextureMgr->Add_Texture(L"PlayerCritical", L"Textrue/PlayerMotion/Attack3/", TEX_MULTI, 64);
	TextureMgr->Add_Texture(L"PlayerRun", L"Textrue/PlayerMotion/Run/", TEX_MULTI, 37);
	TextureMgr->Add_Texture(L"Monster1", L"Textrue/image/Enemy/Monster3/IDLE/", TEX_MULTI, 28, 0);
	TextureMgr->Add_Texture(L"Monster1Die", L"Textrue/image/Enemy/Monster3/DIE/", TEX_MULTI, 35, 0);
	TextureMgr->Add_Texture(L"Monster2", L"Textrue/image/Enemy/Monster4/IDLE/", TEX_MULTI, 18, 0);
	TextureMgr->Add_Texture(L"Monster3", L"Textrue/image/Enemy/Monster5/IDLE/", TEX_MULTI, 32, 0);
	TextureMgr->Add_Texture(L"Monster4", L"Textrue/image/Enemy/Monster6/IDLE/", TEX_MULTI, 8, 0);
	TextureMgr->Add_Texture(L"PlayerDash", L"Textrue/PlayerMotion/Attack2/", TEX_MULTI, 64, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerDashEffect", L"Textrue/Effect/Dash/", TEX_MULTI, 27, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerAttackEffect", L"Textrue/Effect/Attack/", TEX_MULTI, 10, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerCriticalEffect", L"Textrue/Effect/Critical/", TEX_MULTI, 7, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerAttack", L"Textrue/PlayerMotion/Attack1/", TEX_MULTI, 65);
	TextureMgr->Add_Texture(L"PlayerCritical", L"Textrue/PlayerMotion/Attack3/", TEX_MULTI, 64);
	TextureMgr->Add_Texture(L"PlayerRun", L"Textrue/PlayerMotion/Run/", TEX_MULTI, 37);

	TextureMgr->Add_Texture(L"Tile", L"Textrue/Tile/TestTile.png", TEX_SINGLE);
	TextureMgr->Add_Texture(L"Sky", L"Textrue/Sky.jpg", TEX_SINGLE);
	TextureMgr->Add_Texture(L"Font", L"Textrue/Font/", TEX_MULTI, 11);

	CGameObject* pFontRenderer = new CFontRenderer(Device->GetDevice());
	((CFontRenderer*)pFontRenderer)->Init();
	Management->Add_Object(pFontRenderer, OBJ_UI);

	CGameObject* pTile = new CTile(Device->GetDevice());
	((CTile*)pTile)->Init();
	Management->Add_Object(pTile, OBJ_BACKGROUND);

	CGameObject* m_pPlayer;
	m_pPlayer = new CPlayer(Device->GetDevice());
	((CPlayer*)m_pPlayer)->Init();
	Management->Add_Object(m_pPlayer, OBJ_PLAYER);

	CGameObject* pMonster1 = new CMonster(Device->GetDevice());
	((CMonster*)pMonster1)->Init(true);
	Management->Add_Object(pMonster1, OBJ_MONSTER);

	CGameObject* pMonster2 = new CMonster1(Device->GetDevice());
	((CMonster1*)pMonster2)->Init();
	Management->Add_Object(pMonster2, OBJ_MONSTER);
}

int CMainApp::Update()
{
	TimeMgr->Update();
	InputMgr->Update_Key();
	float fTime = TimeMgr->GetElapsedTime();

	Management->Update(fTime);

	Camera->Update(fTime);
	return 0;
}

void CMainApp::Render()
{
	Device->Render_Begin(D3DCOLOR_ARGB(255, 0, 0, 255));
	Device->GetDevice()->SetFVF(FvF_3D_Textrue);

	Management->Render();

	Device->Render_End();
}

void CMainApp::Release()
{
}
