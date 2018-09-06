#include "stdafx.h"
#include "PLayerMana.h"


CPLayerMana::CPLayerMana(LPDIRECT3DDEVICE9 pDevice)
{
}


CPLayerMana::~CPLayerMana()
{
	Release();
}

void CPLayerMana::Init()
{
	nMana = 100;
	nDum = 0;
}

int CPLayerMana::Update(float _fTime)
{
	int DumTemp;
	DumTemp = TempReturn();
	if (nDum != DumTemp)
	{
		if(nDum % 10 == 9)
			nMana += 1;
		if (nMana > 100)
			nMana = 100;

		//cout << CountReturn() << endl;



		if (nMana < 0)
			nMana = 0;
	}
	nDum = TempReturn();
	return 0;
}

void CPLayerMana::Render()
{
}

void CPLayerMana::Release()
{
	nMana = NULL;
	nDum = NULL;
}
