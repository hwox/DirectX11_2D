#include "StartButton.h"
#include "Component/UIButton.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "..\GameMode\Stage1Mode.h"
#include "..\GameMode\Stage2Mode.h"
#include "..\GameMode\Stage3Mode.h"
#include "..\GameMode\MenuMode.h"

CStartButton::CStartButton()
{
	m_pButton = nullptr;
}

CStartButton::~CStartButton()
{
	SAFE_RELEASE(m_pButton);
}

bool CStartButton::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pButton = CGameObject::CreateComponent<CUIButton>("StartButton");

	SetRoot(m_pButton);


	m_pButton->SetRelativeScale(600.f, 100.f, 1.f);
	m_pButton->SetRelativePos(650.f, 100.f, 0.f);



	m_pButton->SetButtonStyleTexture(BS_NORMAL, "StartButton", TEXT("MainTitle\\press_start.png"));
	m_pButton->SetButtonStyleTexture(BS_MOUSEON, "StartButton2", TEXT("MainTitle\\press_start_hover.png"));
	m_pButton->SetButtonStyleTexture(BS_CLICK, "StartButton", TEXT("MainTitle\\press_start.png"));
	m_pButton->SetButtonStyleTexture(BS_DISABLE, "StartButton2", TEXT("MainTitle\\press_start_hover.png"));

	m_pButton->SetButtonStyleColor(BS_NORMAL, Vector4(1.f, 1.f, 1.f, 1.f));
	m_pButton->SetButtonStyleColor(BS_MOUSEON, Vector4(1.f, 1.f, 1.f, 1.f));
	m_pButton->SetButtonStyleColor(BS_CLICK, Vector4(0.6f, 0.6f, 0.6f, 1.f));
	m_pButton->SetButtonStyleColor(BS_DISABLE, Vector4(0.3f, 0.3f, 0.3f, 1.f));

	m_pButton->SetButtonEvent(BE_CLICK, this, &CStartButton::ClickCallback);

	return true;
}

void CStartButton::Begin()
{
	CGameObject::Begin();
}

void CStartButton::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		ClickCallback(fTime);
	}
}

void CStartButton::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CStartButton::SetT(int _t)
{
	t = _t;
}

void CStartButton::ClickCallback(float fTime)
{
	if (t == 1)
	{
	
		CScene*	pNextScene = GET_SINGLE(CSceneManager)->CreateNextScene();

		pNextScene->SetGameMode<CStage1Mode>();

	}
	else if (t == 2)
	{	
		CScene*	pNextScene = GET_SINGLE(CSceneManager)->CreateNextScene();
		pNextScene->SetGameMode<CMenuMode>();
	}

	//CScene*	pNextScene = GET_SINGLE(CSceneManager)->CreateNextScene();
	//
	//pNextScene->SetGameMode<CStage1Mode>();
}
