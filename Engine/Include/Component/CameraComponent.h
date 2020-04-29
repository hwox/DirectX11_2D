#pragma once
#include "SceneComponent.h"
class ENGINE_DLL CCameraComponent :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& com);
	~CCameraComponent();

protected:
	CAMERA_TYPE		m_eCameraType;
	Matrix			m_matView;
	Matrix			m_matProj;


	bool LimitSetComplete;
	bool DontComputeCamY;
	bool DontComputeCamX;
public:
	CAMERA_TYPE GetCameraType()	const;
	void SetCameraType(CAMERA_TYPE eType);
	Matrix GetViewMatrix()	const;
	Matrix GetProjMatrix()	const;

	float minX;
	float maxX;
	float minY;
	float maxY;

	void SetCameraPosLimit(float _minX, float _maxX, float _minY, float _maxY);

private:
	void ComputeMatrix();

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	virtual void SetLimitSetComplete(bool enable);
	virtual bool GetLimitSetComplete();

	virtual void SetDontComputeCamY(bool enable);
	virtual bool GetDontComputeCamY();

	virtual void SetDontComputeCamX(bool enable);
	virtual bool GetDontComputeCamX();
};

