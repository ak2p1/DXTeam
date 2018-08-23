#include "stdafx.h"
#include "Device.h"


CDevice::CDevice()
	: device(NULL)
{
	
}


CDevice::~CDevice()
{
	Release();
}

void CDevice::Init()
{
	//시스템의 물리적 하드웨어 장치에 대한 정보를 얻는 객체
	LPDIRECT3D9 d3d;

	d3d = Direct3DCreate9( D3D_SDK_VERSION );

	//Device 객체의 성격을 결정하는데 이용
	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param, sizeof(param));
	//TRUE : 창모드
	param.Windowed = TRUE;	

	//전체화면 할 경우
	//D3DDISPLAYMODE mode;
	//d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	//param.BackBufferWidth = mode.Width;
	//param.BackBufferHeight = mode.Height;
	//param.BackBufferFormat = mode.Format;




	param.SwapEffect = D3DSWAPEFFECT_DISCARD;	//플리핑 체인의 버퍼가 교환되는 방법을 지정하는
																										  //D3DWSWAPEFFECT열거형 맴버, 
																										  //DISCARD를 지정하는 것이 가장 효과적이다
	
	param.AutoDepthStencilFormat = D3DFMT_D16; 	//깊이,스텐실 버퍼의 포멧
	param.EnableAutoDepthStencil = TRUE;

	//VSync 끄기 (수직 동기화)
	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//VSync 켜기
	//param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&param,
		&device
	);

	DWORD dwD3DCount = d3d->Release();
	int a = 0;
}

void CDevice::Render_Begin(D3DCOLOR _BufferColor /*= D3DCOLOR_ARGB(255, 0, 0, 255)*/)
{
	device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//지울 대상 지정
		//target : 후면버퍼, zbuffer : 깊이버퍼
		_BufferColor,
		1.0f,
		0
	);

	device->BeginScene();//장면시작
}

void CDevice::Render_End()
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

void CDevice::Release()
{
	DWORD dwDeviceRefCount = device->Release();
	int a = 0;
}
