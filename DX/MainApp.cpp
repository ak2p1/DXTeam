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
	������Ʈ
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
	������ 
	*/


	Device->Render_End();
}

void CMainApp::Release()
{
}
