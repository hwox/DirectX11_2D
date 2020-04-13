
#include "Object/GameObject.h"


class CMonsterInfoUI :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CMonsterInfoUI();
	~CMonsterInfoUI();

private:
	class CUIBar*	m_pBar;
	class CUIImage*	m_pBack;
	// class CMonster -> �ؼ� ������ ���� Ŭ���� �޾ƿͼ� hp �ݿ�
	float m_fHP;
	float m_fHPMax;


public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


};
