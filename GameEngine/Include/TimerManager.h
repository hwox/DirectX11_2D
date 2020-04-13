#pragma once

#include "GameEngine.h"

class ENGINE_DLL CTimerManager
{
private:
	unordered_map<size_t, class CTimer*>	m_mapTimer;

public:
	bool Init();
	bool CreateTimer(const string& strName);
	class CTimer* FindTimer(const string& strName);

	DECLARE_SINGLE(CTimerManager)
};

