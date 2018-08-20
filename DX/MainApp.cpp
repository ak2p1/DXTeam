#include "stdafx.h"
#include "MainApp.h"
#include "Test.h"



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
	Management->Init();

	TextureMgr->Add_Texture(L"Player", L"Textrue/test.png", TEX_SINGLE);

	CGameObject* pTest = new CTest(Device->GetDevice());
	((CTest*)pTest)->Init();
	Management->Add_Object(pTest, OBJ_PLAYER);

}

int CMainApp::Update()
{
	TimeMgr->Update();
	InputMgr->Update_Key();
	float fTime = TimeMgr->GetElapsedTime();

	Management->Update(fTime);
	/*
	업데이트
	*/


	Camera->Update();
	return 0;
}

void CMainApp::Render()
{
	Device->Render_Begin(D3DCOLOR_ARGB(255, 0, 0, 255));
	Device->GetDevice()->SetFVF(FvF_3D_Textrue);

	Management->Render();
	/*
	렌더링 
	*/


	Device->Render_End();
}

void CMainApp::Release()
{
}
