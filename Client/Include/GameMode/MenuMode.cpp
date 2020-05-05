#include "MenuMode.h"
#include "../Object/StartButton.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Resource/ResourceManager.h"

CMenuMode::CMenuMode()
{
}

CMenuMode::~CMenuMode()
{
}

bool CMenuMode::Init()
{
	CGameMode::Init();

	CStartButton*	pStartButton = m_pScene->SpawnObject<CStartButton>();
	pStartButton->SetT(2);
	SAFE_RELEASE(pStartButton);

	return true;
}
