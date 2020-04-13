#include "TimerManager.h"
#include "Timer.h"

DEFINITION_SINGLE(CTimerManager)

CTimerManager::CTimerManager()
{
}

CTimerManager::~CTimerManager()
{
	SAFE_DELETE_NORMAL_MAP(m_mapTimer);
}

bool CTimerManager::Init()
{
	return true;
}

bool CTimerManager::CreateTimer(const string & strName)
{
	CTimer*	pTimer = FindTimer(strName);

	if (pTimer)
		return false;

	pTimer = new CTimer;

	pTimer->Init();

	hash<string>	hs;
	size_t iKey = hs(strName);

	m_mapTimer.insert(make_pair(iKey, pTimer));

	return true;
}

CTimer * CTimerManager::FindTimer(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapTimer.find(iKey);

	if (iter == m_mapTimer.end())
		return nullptr;

	return iter->second;
}
