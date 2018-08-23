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
	//�ý����� ������ �ϵ���� ��ġ�� ���� ������ ��� ��ü
	LPDIRECT3D9 d3d;

	d3d = Direct3DCreate9( D3D_SDK_VERSION );

	//Device ��ü�� ������ �����ϴµ� �̿�
	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param, sizeof(param));
	//TRUE : â���
	param.Windowed = TRUE;	

	//��üȭ�� �� ���
	//D3DDISPLAYMODE mode;
	//d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	//param.BackBufferWidth = mode.Width;
	//param.BackBufferHeight = mode.Height;
	//param.BackBufferFormat = mode.Format;




	param.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�ø��� ü���� ���۰� ��ȯ�Ǵ� ����� �����ϴ�
																										  //D3DWSWAPEFFECT������ �ɹ�, 
																										  //DISCARD�� �����ϴ� ���� ���� ȿ�����̴�
	
	param.AutoDepthStencilFormat = D3DFMT_D16; 	//����,���ٽ� ������ ����
	param.EnableAutoDepthStencil = TRUE;

	//VSync ���� (���� ����ȭ)
	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//VSync �ѱ�
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
		//���� ��� ����
		//target : �ĸ����, zbuffer : ���̹���
		_BufferColor,
		1.0f,
		0
	);

	device->BeginScene();//������
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
