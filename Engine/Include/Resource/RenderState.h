#pragma once

#include "../Ref.h"

class ENGINE_DLL CRenderState :
	public CRef
{
	friend class CResourceManager;

protected:
	CRenderState();
	virtual ~CRenderState();

protected:
	ID3D11DeviceChild*	m_pState;
	ID3D11DeviceChild*	m_pPrevState;
	RENDER_STATE_TYPE	m_eRenderStateType;

public:
	RENDER_STATE_TYPE GetRenderStateType()	const;

public:
	virtual void SetState() = 0;
	virtual void ResetState() = 0;
};

