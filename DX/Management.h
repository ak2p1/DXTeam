#pragma once
class CGameObject;

class CManagement
{
	STATIC_SINGLETON(CManagement)
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	vector<CGameObject*> vecObjectUpdate[OBJ_END];
	vector<CGameObject*> vecRenderer[OBJ_END];
	
private:
	CManagement();
	~CManagement();

public:
	void Init(LPDIRECT3DDEVICE9 _pDevice);
	int Update(float _fTime = 0.0f);
	void Render();

private:
	void Release();

public:
	void Add_Object(CGameObject* _pObject, eObjectType _eType);
	vector<CGameObject*>  Get_ObjectType(eObjectType _eType)
	{
		return vecObjectUpdate[_eType];
	}
};

