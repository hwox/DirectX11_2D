#include "PhoneCallUI.h"
#include "Component/UIImage.h"
#include "EngineGlobals.h"


CPhoneCallUI::CPhoneCallUI()
{
	m_PhoneImage = nullptr;

	for (int i = 0; i < 4; i++)
	{
		m_PhoneBattery[i] = nullptr;
	}
}
CPhoneCallUI::~CPhoneCallUI()
{
	SAFE_RELEASE(m_PhoneImage);

	for (int i = 0; i < 4; i++)
	{
		SAFE_RELEASE(m_PhoneBattery[i]);
	}

}

bool CPhoneCallUI::Init()
{
	if (!CGameObject::Init())
		return false;

	m_PhoneImage = CGameObject::CreateComponent<CUIImage>("PhoneImageUI");
	m_PhoneBattery[0] = CGameObject::CreateComponent<CUIImage>("PhoneBattery0");

	SetRoot(m_PhoneImage);

	m_PhoneImage->AddChild(m_PhoneBattery[0], TR_POS);


	m_PhoneImage->SetRelativeScale(35.f, 80.f, 1.f);
	m_PhoneImage->SetRelativePos(50.f, 980.f, 1.f);
	m_PhoneImage->SetZOrder(1);


	m_PhoneBattery[0]->SetRelativeScale(80.f, 80.f, 1.f);
	m_PhoneBattery[0]->SetRelativePos(50.f, 0.f, 0.f);
	m_PhoneBattery[0]->SetZOrder(2);


	m_PhoneImage->SetTexture("PhoneImageUI", TEXT("UI/PlayerInfo/phone/phone_ui.png"));
	m_PhoneBattery[0]->SetTexture("PhoneBattery0", TEXT("UI/PlayerInfo/phone/phone_ui_battery_0.png"));


	return true;
}

void CPhoneCallUI::Begin()
{
	CGameObject::Begin();
}

void CPhoneCallUI::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CPhoneCallUI::Render(float fTime)
{
	CGameObject::Render(fTime);
}
