#include "Title.h"
#include "Component/Text.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"


CTitle::CTitle()
{
	m_pText = nullptr;
}


CTitle::~CTitle()
{
	SAFE_RELEASE(m_pText);
}

bool CTitle::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pText = CGameObject::CreateComponent<CText>("TitleText");

	SetRoot(m_pText);



	return true;
}

void CTitle::Begin()
{
	CGameObject::Begin();
}

void CTitle::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		if (DebugText)
			DebugText = false;
		else
			DebugText = true;
	}

	if (DebugText)
	{
		Vector3 pPos = GetScene()->GetGameMode()->GetPlayer()->GetWorldPos();

		m_pText->SetRelativePos(200.f, 800.f, 0.f);
		m_pText->SetRenderArea(800.f, 800.f, 1000.f, 700.f);


		TCHAR	strFileName[MAX_PATH] = {};
		wstring str = TEXT("X: %d / Y: %d  \n");

		wsprintf(strFileName, str.c_str(), (int)pPos.x, (int)pPos.y);


		m_pText->SetText(strFileName);
		//m_pText->SetShadow(true);
		//m_pText->SetShadowColor(0.2f, 0.2f, 0.2f, 1.f);
		//m_pText->SetShadowOffset(Vector3(2.f, -2.f, 0.f));
		//m_pText->SetShadowOpacity(0.6f);
		m_pText->ShadowAlphaBlend(true);
		m_pText->SetFont("NormalText1");
		m_pText->SetSize(20.f);

		m_pText->SetColor(1.f, 0.f,0.f, 1.f);
		m_pText->SetOpacity(0.8f);
		m_pText->AlphaBlend(true);

	}
}

void CTitle::Render(float fTime)
{
	CGameObject::Render(fTime);
}
