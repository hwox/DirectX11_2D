#include "CharacterMovementComponent.h"
#include "SceneComponent.h"

CCharacterMovementComponent::CCharacterMovementComponent()
{
	SetTypeID<CCharacterMovementComponent>();
}

CCharacterMovementComponent::CCharacterMovementComponent(const CCharacterMovementComponent & com) :
	CMovementComponent(com)
{
}

CCharacterMovementComponent::~CCharacterMovementComponent()
{
}

bool CCharacterMovementComponent::Init()
{
	if (!CMovementComponent::Init())
		return false;

	IsBackStep = false;
	m_UseGravity = false;

	return true;
}

void CCharacterMovementComponent::Begin()
{
	CMovementComponent::Begin();
}

void CCharacterMovementComponent::Update(float fTime)
{
	CMovementComponent::Update(fTime);
}

void CCharacterMovementComponent::PostUpdate(float fTime)
{
	if (!m_PathList.empty())
	{
		Vector3	vTarget = m_PathList.front();
		Vector3	vPos = m_pUpdateComponent->GetWorldPos();

		vPos.z = 0.f;
		vTarget.z = 0.f;

		if (vTarget.Distance(vPos) <= 3.f)
		{
			m_PathList.pop_front();

			if(!m_PathList.empty())
			{
				vTarget = m_PathList.front();
			}
		}

		if (!m_PathList.empty())
		{
			m_vVelocity = vTarget - vPos;
		}
	}

	if (IsBackStep)
	{
		AddMovement(Axis * -0.8f);
	}

	CMovementComponent::PostUpdate(fTime);
}

void CCharacterMovementComponent::BackStep(const Vector3 & _Axis)
{
	Axis = _Axis;

	IsBackStep = true;
}

void CCharacterMovementComponent::BackStepEnd()
{
	IsBackStep = false;
}

bool CCharacterMovementComponent::GetIsBackStep()
{
	return IsBackStep;
}

void CCharacterMovementComponent::SetGravityUse(Vector3 & _MinYPos)
{
	CMovementComponent::SetGravityUse(_MinYPos);
	MinYPos = _MinYPos;

}
