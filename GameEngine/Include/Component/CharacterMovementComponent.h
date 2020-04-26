#pragma once
#include "MovementComponent.h"
class ENGINE_DLL CCharacterMovementComponent :
	public CMovementComponent
{
	friend class CGameObject;

	bool IsBackStep;
	Vector3 Axis;

protected:
	CCharacterMovementComponent();
	CCharacterMovementComponent(const CCharacterMovementComponent& com);
	virtual ~CCharacterMovementComponent();

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);

	void BackStep(const Vector3 & vVelocity);
	void BackStepEnd();
	bool GetIsBackStep();
	void SetGravityUse(Vector3 & _MinYPos);
};

