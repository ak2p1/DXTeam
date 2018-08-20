#include "stdafx.h"
#include "TextureMgr.h"

CTextureMgr::CTextureMgr()
	:pDevice(NULL)
{

}

CTextureMgr::~CTextureMgr()
{
	Release();
}

void CTextureMgr::Init(LPDIRECT3DDEVICE9 _pDevice)
{
	pDevice = _pDevice;
}
void CTextureMgr::Add_Texture(
	const TCHAR* _szFileKey, 
	const TCHAR* _szFilePath, 
	eTextureType _eType /*= TEX_SINGLE */, 
	DWORD _dwTextureCount /*= 1*/)
{
	IMAGE* pImage = new IMAGE; //이미지 할당

	//이미지 장수
	pImage->dwMaxCnt = _dwTextureCount;	

	//이미지 장수 만큼 할당
	pImage->pTexture = new TEXINFO[_dwTextureCount];



}

void CTextureMgr::Release()
{

}

