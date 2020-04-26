#include "PlayerHpBar.h"
#include "Component/UIBar.h"
#include "Component/UIImage.h"
#include "EngineGlobals.h"

CPlayerHpBar::CPlayerHpBar()
{
	m_pBack = nullptr;
	m_pBar = nullptr;
}
CPlayerHpBar::~CPlayerHpBar()
{
	SAFE_RELEASE(m_pBack);
	SAFE_RELEASE(m_pBar);
}

bool CPlayerHpBar::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pBar = CGameObject::CreateComponent<CUIBar>("PlayerInfo_HPBar");
	m_pBack = CGameObject::CreateComponent<CUIImage>("PlayerInfo_HPBack");

	SetRoot(m_pBack);

	m_pBack->AddChild(m_pBar, TR_POS);

	m_pBack->SetRelativeScale(300.f, 110.f, 1.f);
	m_pBack->SetRelativePos(900.f, 20.f, 0.f);
	m_pBack->SetZOrder(1);

	m_pBar->SetRelativeScale(300.f, 110.f, 1.f);
	m_pBar->SetRelativePos(0.f, 0.f, 0.f);
	m_pBar->SetZOrder(2);

	m_pBack->SetTexture("PlayerInfo_HPBar", TEXT("UI/PlayerInfo/hp/kirby_hp_back.png"));
	m_pBar->SetTexture("PlayerInfo_HPBack", TEXT("UI/PlayerInfo/hp/kirby_hp.png"));

	m_fHP = 1000;
	m_fHPMax = 1000;

	return true;

}

void CPlayerHpBar::Begin()
{
	CGameObject::Begin();
}

void CPlayerHpBar::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		m_fHP -= 300.f * fTime;

		if (m_fHP < 0)
			m_fHP = 0;

		m_pBar->SetPercent(m_fHP / m_fHPMax);
	}

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		m_fHP += 300.f * fTime;

		if (m_fHP >= m_fHPMax)
			m_fHP = m_fHPMax;

		m_pBar->SetPercent(m_fHP / m_fHPMax);
	}
}

void CPlayerHpBar::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CPlayerHpBar::SetPercentHPBar(float percent)
{
	m_pBar->SetPercent(percent);
}