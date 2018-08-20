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

typedef struct TagObjectInfo		//��ü ����
{
	D3DXVECTOR3 vScale;				//ũ��
	D3DXVECTOR3 vAngle;				//ȸ��
	D3DXVECTOR3 vPos;					//��ġ
	D3DXMATRIX	matWorld;			//���� ���

	TagObjectInfo(
		D3DXVECTOR3 _vScale = D3DXVECTOR3(0,0,0),
		D3DXVECTOR3 _vAngle = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3 _vPos = D3DXVECTOR3(0, 0, 0))
		:vScale(_vScale)
		, vAngle(_vAngle)
		, vPos(vPos)
	{
		D3DXMatrixIdentity(&matWorld);
	}
	~TagObjectInfo() {};

}INFO;

typedef struct TagCamera
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vTarget;
	D3DXVECTOR3 vUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;

}CAMERA;

typedef struct TagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;

}TEXINFO;

typedef struct  TagImage
{
	TEXINFO* pTexture;				//�̹��� �迭���·� �����ϱ����� �����ͺ��� ����
	DWORD dwMaxCnt;				//�̹��� �ִ� ���

}IMAGE;


