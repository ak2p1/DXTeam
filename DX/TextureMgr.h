#pragma once
class CTextureMgr
{
	STATIC_SINGLETON(CTextureMgr)

private:
	map<const TCHAR*, IMAGE* > mapImage;
	LPDIRECT3DDEVICE9 pDevice;

public:
	CTextureMgr();
	~CTextureMgr();

public:
	void Init(LPDIRECT3DDEVICE9 _pDevice);
	void Add_Texture(
		const TCHAR* _szImageKey , 
		const TCHAR* _szFilePath ,
		eTextureType _eType  = TEX_SINGLE, 
		DWORD _dwTextureCount = 1,
		DWORD _dwBackDeleteColor = D3DCOLOR_ARGB(255,255,0,255) );

	IMAGE* GetImage(const TCHAR* _szImageKey);

private:
	void Release();

};

