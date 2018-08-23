#pragma once

typedef struct TagVertexColor
{
	D3DXVECTOR3 vPos;
	DWORD dwColor;

	TagVertexColor(D3DXVECTOR3 _vPos = D3DXVECTOR3(0,0,0) , DWORD _dwColor = 0)
		:vPos(_vPos)
		, dwColor(_dwColor)
	{};

	~TagVertexColor() {};

}VERTEX_COLOR;

typedef struct TagVertexTextrue
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vTexUV;

	TagVertexTextrue(
		D3DXVECTOR3 _vPos = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR2 _vTexUV = D3DXVECTOR2(0, 0))
		:vPos(_vPos)
		, vTexUV(_vTexUV)
	{};

	~TagVertexTextrue() {};

}VERTEX_TEX;

const DWORD FvF_3D_Color = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const DWORD FvF_3D_Textrue = D3DFVF_XYZ | D3DFVF_TEX1;

typedef struct TagObjectInfo		//객체 정보
{
	D3DXVECTOR3 vScale;				//크기
	D3DXVECTOR3 vAngle;				//회전
	D3DXVECTOR3 vPos;					//위치
	D3DXMATRIX		matWorld;			//월드 행렬
	int			nMonNum;

	TagObjectInfo(
		D3DXVECTOR3 _vScale = D3DXVECTOR3(0,0,0),
		D3DXVECTOR3 _vAngle = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3 _vPos = D3DXVECTOR3(0, 0, 0),
		int         _nMonNum = 0)
		:vScale(_vScale)
		, vAngle(_vAngle)
		, vPos(_vPos)
		, nMonNum(_nMonNum)
	{
		D3DXMatrixIdentity(&matWorld);
	}
	~TagObjectInfo() {};

}INFO;

typedef struct TagCamera
{
	D3DXVECTOR3	 vPos;
	D3DXVECTOR3	 vTarget;
	D3DXVECTOR3	 vUp;
	D3DXMATRIX		 matView;
	D3DXMATRIX		 matProj;

}CAMERA;

typedef struct TagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture; //텍스쳐
	float fWidth;		//텍스쳐 실제 가로 크기
	float fHeight;	//텍스쳐 실제 세로 크기

}TEXINFO;

typedef struct  TagImage
{
	TEXINFO* pTexInfo;				//이미지 배열형태로 저장하기위해 포인터변수 선언
	DWORD dwMaxCnt;				//이미지 최대 장수

}IMAGE;


