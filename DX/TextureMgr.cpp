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
	DWORD _dwTextureCount /*= 1*/,
	DWORD _dwBackDeleteColor /*= D3DCOLOR_ARGB(255, 255, 0, 255)*/ )
{
	IMAGE* pImage = NULL;

	//이미지 싱글 타입
	if (_eType == TEX_SINGLE)	
	{
		map<const TCHAR*, IMAGE* >::iterator iter;
		iter = mapImage.find(_szFileKey); //이미 추가된 이미지 인지 아닌지 검사한다.

		if (iter != mapImage.end()) //이미지가 이미 추가되있다면
			return;

		pImage = new IMAGE; 
		pImage->dwMaxCnt = 1;	
		pImage->pTexInfo = new TEXINFO;

		D3DXCreateTextureFromFileEx(
			pDevice,
			_szFilePath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			_dwBackDeleteColor,
			NULL,
			NULL,
			&(pImage->pTexInfo->pTexture) );

		D3DSURFACE_DESC desc;
		pImage->pTexInfo->pTexture->GetLevelDesc(0, &desc);

		pImage->pTexInfo->fWidth = (float)desc.Width;
		pImage->pTexInfo->fHeight = (float)desc.Height;

		mapImage.insert(make_pair(_szFileKey , pImage) );

	}
	else //이미지 멀티 타입
	{
		map<const TCHAR*, IMAGE* >::iterator iter;
		iter = mapImage.find(_szFileKey); //이미 추가된 이미지 인지 아닌지 검사한다.

		if (iter != mapImage.end()) //이미지가 이미 추가되있다면
			return;

		pImage = new IMAGE;
		pImage->dwMaxCnt = _dwTextureCount;
		pImage->pTexInfo = new TEXINFO[_dwTextureCount];

		TCHAR szTotal[MAX_PATH] = L"";
		TCHAR szNum[MAX_PATH] = L"";
		
		// 1부터 ~ 
		for (DWORD i = 0; i < _dwTextureCount; ++i)
		{
			TCHAR szNum[MAX_PATH] = L"";
			_itot_s(i + 1 , szNum , 10);
			lstrcat(szNum, L".png");
			lstrcpy(szTotal, _szFilePath);
			lstrcat(szTotal , szNum);
			//wsprintf(szTotal, _szFilePath, i);	//경로에 파일이름 (숫자)을 합친다.

			if (S_OK == D3DXCreateTextureFromFileEx(
				pDevice,
				szTotal,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				1,
				NULL,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_FILTER_NONE,
				D3DX_FILTER_NONE,
				_dwBackDeleteColor,
				NULL,
				NULL,
				&(pImage->pTexInfo[i].pTexture)))
			{
				int a = 0;
			}
			
			

			D3DSURFACE_DESC desc;
			pImage->pTexInfo[i].pTexture->GetLevelDesc(0, &desc);

			pImage->pTexInfo[i].fWidth = (float)desc.Width;
			pImage->pTexInfo[i].fHeight = (float)desc.Height;
		}
		mapImage.insert(make_pair(_szFileKey, pImage));
	}
}

IMAGE* CTextureMgr::GetImage(const TCHAR* _szImageKey)
{
	map<const TCHAR*, IMAGE* >::iterator iter;
	iter = mapImage.find(_szImageKey); 

	if (iter == mapImage.end()) 
		return NULL;

	return iter->second;
}

void CTextureMgr::Release()
{
	map<const TCHAR*, IMAGE* >::iterator iter = mapImage.begin();
	map<const TCHAR*, IMAGE* >::iterator iter_end = mapImage.end();

	for (iter ; iter != iter_end ; ++iter)
	{
		if (iter->second->dwMaxCnt == 1)		//이미지가 한장이라면
		{
			SAFE_RELEASE(iter->second->pTexInfo->pTexture);
			SAFE_DELETE(iter->second->pTexInfo);
			SAFE_DELETE(iter->second);
		}
		else
		{
			for (DWORD i = 0 ; i < iter->second->dwMaxCnt ; ++i)
			{
				SAFE_RELEASE(iter->second->pTexInfo[i].pTexture);
			}
			SAFE_DELETE_ARRAY(iter->second->pTexInfo);
			SAFE_DELETE(iter->second);
		}
	}
	mapImage.clear();
}

