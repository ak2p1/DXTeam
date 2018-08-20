#pragma once
class CDevice
{
	STATIC_SINGLETON(CDevice)

private:
	//3D 그래픽을 디스플레이 하는데 이용될 물리 하드웨어 장치를 나타내는 객체
	LPDIRECT3DDEVICE9 device;

public:
	CDevice();
	~CDevice();

public:
	void Init();
	void Render_Begin(D3DCOLOR _BufferColor = D3DCOLOR_ARGB(255, 0, 0, 255));
	void Render_End();

	//void Setfvf
	
private:
	void Release();

public:
	LPDIRECT3DDEVICE9 GetDevice() { return device; }
	

};

