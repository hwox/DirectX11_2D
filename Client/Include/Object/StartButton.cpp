#include "StartButton.h"
#include "Component/UIButton.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "..\GameMode\Stage1Mode.h"


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


	m_pButton->SetRelativeScale(300.f, 100.f, 1.f);
	m_pButton->SetRelativePos(800.f, 100.f, 0.f);



	m_pButton->SetButtonStyleTexture(BS_NORMAL, "StartButton", TEXT("START.png"));
	m_pButton->SetButtonStyleTexture(BS_MOUSEON, "StartButton2", TEXT("START_2.png"));
	m_pButton->SetButtonStyleTexture(BS_CLICK, "StartButton", TEXT("START.png"));
	m_pButton->SetButtonStyleTexture(BS_DISABLE, "StartButton2", TEXT("START_2.png"));

	m_pButton->SetButtonStyleColor(BS_NORMAL, Vector4(0.8f, 0.8f, 0.8f, 1.f));
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
}

void CStartButton::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CStartButton::ClickCallback(float fTime)
{
	CScene*	pNextScene = GET_SINGLE(CSceneManager)->CreateNextScene();

	pNextScene->SetGameMode<CStage1Mode>();
}
