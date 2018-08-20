#pragma once
class CTimeManager
{
	STATIC_SINGLETON(CTimeManager)

private:
// 	int m_dwPrevTimeStamp;
// 	float m_dwElapsedTime;

	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTick;
	float m_fTime;

private:
	CTimeManager();
	~CTimeManager();

public:
	void Init();
	int Update();
	float GetElapsedTime();
};

