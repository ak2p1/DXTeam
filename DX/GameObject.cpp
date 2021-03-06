#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	:m_pDevice(NULL)
	, VertexBuffer(NULL)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	
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
		D3DXVECTOR2 vMin = D3DXVECTOR2(-(_fWidth * 0.5f), -(_fHeight * 0.5f));
		D3DXVECTOR2 vMax = D3DXVECTOR2(_fWidth * 0.5f, _fHeight * 0.5f);

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

void CGameObject::SetBuffer(float _fWidth, float _fHeight)
{
	VERTEX_TEX* Vertex = NULL;

		D3DXVECTOR2 vMin = D3DXVECTOR2(-(_fWidth * 0.5f), -(_fHeight * 0.5f));
		D3DXVECTOR2 vMax = D3DXVECTOR2(_fWidth * 0.5f, _fHeight * 0.5f);
		Vertex = new VERTEX_TEX[6];
		Vertex[0].vPos = D3DXVECTOR3(vMin.x, vMin.y, 1);
		Vertex[1].vPos = D3DXVECTOR3(vMax.x, vMin.y, 1);
		Vertex[2].vPos = D3DXVECTOR3(vMin.x, vMax.y, 1);
		Vertex[3].vPos = D3DXVECTOR3(vMax.x, vMin.y, 1);
		Vertex[4].vPos = D3DXVECTOR3(vMax.x, vMax.y, 1);
		Vertex[5].vPos = D3DXVECTOR3(vMin.x, vMax.y, 1);

		Vertex[0].vTexUV = D3DXVECTOR2(0, 0);
		Vertex[1].vTexUV = D3DXVECTOR2(1, 0);
		Vertex[2].vTexUV = D3DXVECTOR2(0, 1);
		Vertex[3].vTexUV = D3DXVECTOR2(1, 0);
		Vertex[4].vTexUV = D3DXVECTOR2(1, 1);
		Vertex[5].vTexUV = D3DXVECTOR2(0, 1);

		UINT VertexSize = 6 * sizeof(VERTEX_TEX); //정점 6개 * 정점하나의 크기
	void* vertexData = NULL;
	VertexBuffer->Lock(0, VertexSize, &vertexData, NULL);
	memcpy(vertexData, Vertex, VertexSize);
	VertexBuffer->Unlock();
	SAFE_DELETE_ARRAY(Vertex);

	m_pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_TEX));
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

int CGameObject::Update(float _fTime /*= 0.0f*/)
{
	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matPos;
	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);
	D3DXMatrixRotationX(&matRotX, m_tInfo.vAngle.x);
	D3DXMatrixRotationY(&matRotY, m_tInfo.vAngle.y);
	D3DXMatrixRotationZ(&matRotZ, m_tInfo.vAngle.z);
	D3DXMatrixTranslation(&matPos, m_tInfo.vPos.x , m_tInfo.vPos.y , 0);
	m_tInfo.matWorld = matScale * matRotX * matRotY * matRotZ * matPos;

	return 0;
}

void CGameObject::Release()
{
	SAFE_RELEASE(VertexBuffer);
}
