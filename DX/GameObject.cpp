#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	:m_pDevice(NULL)
	, VertexBuffer(NULL)
{
	
}

CGameObject::~CGameObject()
{
	Release();
}

void CGameObject::init(
	bool _isOriginSize /*= false */, 
	float _fWidth /*= 0.0f*/,
	float _fHeight /*= 0.0f*/)
{
	UINT VertexSize = 6 * sizeof(VERTEX_TEX); //정점 6개 * 정점하나의 크기

	m_pDevice->CreateVertexBuffer(
		VertexSize,
		0,
		FvF_3D_Textrue,
		D3DPOOL_DEFAULT,
		&VertexBuffer,
		NULL);

	VERTEX_TEX* Vertex = NULL;


	if (_isOriginSize)		//이미지 원본 사이즈
	{
		D3DXVECTOR2 vMin = D3DXVECTOR2(-(_fWidth * 0.5f), -(_fHeight * 0.5f));
		D3DXVECTOR2 vMax = D3DXVECTOR2(_fWidth * 0.5f, _fHeight * 0.5f);

		Vertex = new VERTEX_TEX[6];
		Vertex[0].vPos = D3DXVECTOR3(vMin.x , vMin.y , 1);
		Vertex[1].vPos = D3DXVECTOR3(vMax.x , vMin.y , 1);
		Vertex[2].vPos = D3DXVECTOR3(vMin.x , vMax.y , 1);
		Vertex[3].vPos = D3DXVECTOR3(vMax.x , vMin.y , 1);
		Vertex[4].vPos = D3DXVECTOR3(vMax.x , vMax.y , 1);
		Vertex[5].vPos = D3DXVECTOR3(vMin.x , vMax.y , 1);

		Vertex[0].vTexUV = D3DXVECTOR2(0, 0);
		Vertex[1].vTexUV = D3DXVECTOR2(1, 0);
		Vertex[2].vTexUV = D3DXVECTOR2(0, 1);
		Vertex[3].vTexUV = D3DXVECTOR2(1, 0);
		Vertex[4].vTexUV = D3DXVECTOR2(1, 1);
		Vertex[5].vTexUV = D3DXVECTOR2(0, 1);
	}
	else
	{
		D3DXVECTOR2 vMin = D3DXVECTOR2( -100.0f,  -100.0f);
		D3DXVECTOR2 vMax = D3DXVECTOR2( 100.0f,  100.0f);

		Vertex = new VERTEX_TEX[6];
		Vertex[0].vPos = D3DXVECTOR3(vMin.x, vMin.y, 1.0f);
		Vertex[1].vPos = D3DXVECTOR3(vMax.x, vMin.y, 1.0f);
		Vertex[2].vPos = D3DXVECTOR3(vMin.x, vMax.y, 1.0f);
		Vertex[3].vPos = D3DXVECTOR3(vMax.x, vMin.y, 1.0f);
		Vertex[4].vPos = D3DXVECTOR3(vMax.x, vMax.y, 1.0f);
		Vertex[5].vPos = D3DXVECTOR3(vMin.x, vMax.y, 1.0f);

		Vertex[0].vTexUV = D3DXVECTOR2(0.0f, 0.0f);
		Vertex[1].vTexUV = D3DXVECTOR2(1.0f, 0.0f);
		Vertex[2].vTexUV = D3DXVECTOR2(0.0f, 1.0f);
		Vertex[3].vTexUV = D3DXVECTOR2(1.0f, 0.0f);
		Vertex[4].vTexUV = D3DXVECTOR2(1.0f, 1.0f);
		Vertex[5].vTexUV = D3DXVECTOR2(0.0f, 1.0f);
	}

	void* vertexData = NULL;
	VertexBuffer->Lock(0, VertexSize, &vertexData, NULL);
	memcpy(vertexData, Vertex, VertexSize);
	VertexBuffer->Unlock();




	SAFE_DELETE_ARRAY(Vertex);
}

void CGameObject::SetBuffer()
{
	m_pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_TEX));
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void CGameObject::Release()
{
	SAFE_RELEASE(VertexBuffer);
}
