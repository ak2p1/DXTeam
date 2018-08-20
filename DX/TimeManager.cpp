#include "stdafx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager()
{
}


CTimeManager::~CTimeManager()
{
}

void CTimeManager::Init()
{
	//m_dwElapsedTime = 0;
	//m_dwPrevTimeStamp = GetTickCount();

	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);
}

int CTimeManager::Update()
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;

// 	DWORD dwCurrTimeStamp = GetTickCount();
// 	m_dwElapsedTime = dwCurrTimeStamp - m_dwPrevTimeStamp;
// 	m_dwPrevTimeStamp = dwCurrTimeStamp;

	return 0;
}

float CTimeManager::GetElapsedTime()
{
	//return m_dwElapsedTime / 1000.f;
	return m_fTime;
}
