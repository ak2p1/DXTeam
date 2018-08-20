#pragma once

//#define DEBUG_MODE

#define WIN_START_X 100
#define WIN_START_Y 0

#define  WIN_SIZE_X 1024
#define  WIN_SIZE_Y 768

#define PI 3.14159265359f
#define EPSILON 0.00001f

#define InputMgr CInput::GetInstance()
#define TimeMgr CTimeManager::GetInstance()
#define TextureMgr CTextureMgr::GetInstance()
#define Device CDevice::GetInstance()
#define Camera CCamera::GetInstance()
#define Management CManagement::GetInstance()