#include "stdafx.h"
#include "MainApp.h"
#include "Test.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"

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
	//디바이스 초기화
	Device->Init();
	m_pDevice = Device->GetDevice();

	//인풋 매니저 초기화
	InputMgr->Init();

	//타임 매니저 초기화
	TimeMgr->Init();

	//텍스쳐 매니저 초기화
	TextureMgr->Init(m_pDevice);

	//카메라 초기화
	Camera->Init(m_pDevice);

	//매니지먼트 초기화
	Management->Init(m_pDevice);

	TextureMgr->Add_Texture(L"PlayerAttack", L"Textrue/PlayerMotion/Attack1/", TEX_MULTI, 65, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerCritical", L"Textrue/PlayerMotion/Attack3/", TEX_MULTI, 64, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerDash", L"Textrue/PlayerMotion/Attack2/", TEX_MULTI, 64, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerRun", L"Textrue/PlayerMotion/Run/", TEX_MULTI, 37, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"Tile", L"Textrue/Tile/TestTile.png", TEX_SINGLE );
	TextureMgr->Add_Texture(L"Monster1", L"Textrue/image/Enemy/Monster1/IDLE/", TEX_MULTI, 12, 0);
	TextureMgr->Add_Texture(L"PlayerAttack", L"Textrue/PlayerMotion/Attack1/", TEX_MULTI, 65, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerCritical", L"Textrue/PlayerMotion/Attack3/", TEX_MULTI, 64, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerDash", L"Textrue/PlayerMotion/Attack2/", TEX_MULTI, 64, D3DCOLOR_ARGB(255, 255, 255, 255));
	TextureMgr->Add_Texture(L"PlayerRun", L"Textrue/PlayerMotion/Run/", TEX_MULTI, 37, D3DCOLOR_ARGB(255, 255, 255, 255));


	CGameObject* pTest = new CTile(Device->GetDevice());
	((CTile*)pTest)->Init();
	Management->Add_Object(pTest, OBJ_BACKGROUND);

	CGameObject* m_pPlayer;
	m_pPlayer = new CPlayer(Device->GetDevice());
	((CPlayer*)m_pPlayer)->Init();
	Management->Add_Object(m_pPlayer, OBJ_PLAYER);

	CGameObject* pMonster1 = new CMonster(Device->GetDevice());
	((CMonster*)pMonster1)->Init();
	Management->Add_Object(pMonster1, OBJ_MONSTER);





	// 	pTest = new CTest(Device->GetDevice());
	// 	((CTest*)pTest)->Init();
	// 	Management->Add_Object(pTest, OBJ_PLAYER);


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
