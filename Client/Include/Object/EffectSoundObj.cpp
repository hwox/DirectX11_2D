#include "EffectSoundObj.h"
#include "Component/Audio.h"

CEffectSoundObj::CEffectSoundObj() :
	m_pAudio(nullptr)
{
}

CEffectSoundObj::~CEffectSoundObj()
{
	SAFE_RELEASE(m_pAudio);
}

void CEffectSoundObj::SetSound(const string & strKey, const char * pFileName)
{
	m_pAudio->SetSound(strKey, false, pFileName);
	m_pAudio->Play();
}

void CEffectSoundObj::SetLifeTime(float time)
{
}

bool CEffectSoundObj::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");

	/*m_pAudio->SetSound("Demasia", false, "Demasia.mp3");
	m_pAudio->Play();*/

	SetRoot(m_pAudio);

	return true;
}

void CEffectSoundObj::Begin()
{
	CGameObject::Begin();
}

void CEffectSoundObj::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (!m_pAudio->IsPlay())
	{
		Kill();
	}
}

void CEffectSoundObj::Render(float fTime)
{
	CGameObject::Render(fTime);
}
