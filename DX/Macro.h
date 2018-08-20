#pragma once

#define STATIC_SINGLETON(CLASSNAME)	    \
public:									\
	static CLASSNAME* GetInstance()		\
	{									\
		static CLASSNAME instance;		\
		return &instance;				\
	}									


#define SAFE_DELETE(P)					\
if (NULL != P)							\
{										\
	delete P;							\
	P = NULL;							\
}

#define SAFE_DELETE_ARRAY(P)			\
if (NULL != P)							\
{										\
	delete[] P;							\
	P = NULL;							\
}

#define SAFE_RELEASE(P) \
if (NULL != P)							\
{										\
	P->Release();						\
	P = NULL;							\
}
