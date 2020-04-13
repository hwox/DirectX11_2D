#include "Collision.h"
#include "ColliderRect.h"
#include "ColliderSphere2D.h"
#include "ColliderOBB2D.h"
#include "ColliderPixel.h"

bool CCollision::CollisionRectToRect(CColliderRect * pSrc, CColliderRect * pDest)
{
	Vector3	vIntersect;

	if (CollisionRectToRect(vIntersect, pSrc->GetMin(), pSrc->GetMax(), pDest->GetMin(), pDest->GetMax()))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionSphere2DToSphere2D(CColliderSphere2D * pSrc, CColliderSphere2D * pDest)
{
	Vector3	vIntersect;

	if (CollisionSphere2DToSphere2D(vIntersect, pSrc->GetCenter(), pSrc->GetRadius(),
		pDest->GetCenter(), pDest->GetRadius()))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionOBB2DToOBB2D(CColliderOBB2D * pSrc, CColliderOBB2D * pDest)
{
	Vector3	vIntersect;

	if (CollisionOBB2DToOBB2D(vIntersect, pSrc->GetCenter(), pSrc->m_vAxis, pSrc->m_fLength,
		pDest->GetCenter(), pDest->m_vAxis, pDest->m_fLength))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionRectToPixel(CColliderRect * pSrc, CColliderPixel * pDest)
{
	Vector3	vIntersect;

	if (CollisionRectToPixel(vIntersect, pSrc->GetMin(), pSrc->GetMax(), pDest->GetColliderSectionMin(),
		pDest->GetColliderSectionMax(), pDest->GetPixel(), pDest->GetPixelSize(),
		pDest->GetPixelCountX(), pDest->GetPixelCountY(), pDest->GetIgnoreColor()))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionRectToMouse(CColliderRect * pSrc, const Vector2 & vMousePos)
{
	Vector3	vMin = pSrc->GetMin();
	Vector3 vMax = pSrc->GetMax();

	if (vMin.x > vMousePos.x)
		return false;

	else if (vMax.x < vMousePos.x)
		return false;

	else if (vMin.y > vMousePos.y)
		return false;

	else if (vMax.y < vMousePos.y)
		return false;

	pSrc->m_vIntersect	= Vector3(vMousePos.x, vMousePos.y, 0.f);

	return true;
}

bool CCollision::CollisionSphere2DToMouse(CColliderSphere2D * pSrc, const Vector2 & vMousePos)
{
	Vector2	vCenter	= Vector2(pSrc->GetCenter().x, pSrc->GetCenter().y);
	float	fDist = vCenter.Distance(vMousePos);

	if (fDist <= pSrc->GetRadius())
	{
		pSrc->m_vIntersect = Vector3(vMousePos.x, vMousePos.y, 0.f);

		return true;
	}

	return false;
}

bool CCollision::CollisionOBB2DToMouse(CColliderOBB2D * pSrc, const Vector2 & vMousePos)
{
	return false;
}

bool CCollision::CollisionPixelToMouse(CColliderPixel * pSrc, const Vector2 & vMousePos)
{
	return false;
}

bool CCollision::CollisionRectToRect(Vector3& vIntersect, const Vector3 & vSrcMin, const Vector3 & vSrcMax, 
	const Vector3 & vDestMin, const Vector3 & vDestMax)
{
	if (vSrcMin.x > vDestMax.x)
		return false;

	else if (vSrcMax.x < vDestMin.x)
		return false;

	else if (vSrcMin.y > vDestMax.y)
		return false;

	else if (vSrcMax.y < vDestMin.y)
		return false;

	float l = vSrcMin.x > vDestMin.x ? vSrcMin.x : vDestMin.x;
	float r = vSrcMax.x < vDestMax.x ? vSrcMax.x : vDestMax.x;
	float t = vSrcMax.y < vDestMax.y ? vSrcMax.y : vDestMax.y;
	float b = vSrcMin.y > vDestMin.y ? vSrcMin.y : vDestMin.y;

	vIntersect.x = (l + r) / 2.f;
	vIntersect.y = (t + b) / 2.f;
	vIntersect.z = 0.f;

	return true;
}

bool CCollision::CollisionSphere2DToSphere2D(Vector3 & vIntersect, const Vector3 & vSrcCenter,
	float fSrcRadius, const Vector3 & vDestCenter, float fDestRadius)
{
	float	fDist = vSrcCenter.Distance(vDestCenter);

	if (fDist <= fSrcRadius + fDestRadius)
	{
		Vector3	vSrcMin, vSrcMax, vDestMin, vDestMax;
		vSrcMin = vSrcCenter - fSrcRadius;
		vSrcMax = vSrcCenter + fSrcRadius;

		vDestMin = vDestCenter - fDestRadius;
		vDestMax = vDestCenter + fDestRadius;

		Vector3	vIntersectMin, vIntersectMax;
		vIntersectMin.x = vSrcMin.x > vDestMin.x ? vSrcMin.x : vDestMin.x;
		vIntersectMin.y = vSrcMin.y > vDestMin.y ? vSrcMin.y : vDestMin.y;
		vIntersectMax.x = vSrcMax.x < vDestMax.x ? vSrcMax.x : vDestMax.x;
		vIntersectMax.y = vSrcMax.y < vDestMax.y ? vSrcMax.y : vDestMax.y;

		vIntersect = (vIntersectMin + vIntersectMax) / 2.f;

		return true;
	}

	return false;
}

bool CCollision::CollisionOBB2DToOBB2D(Vector3 & vIntersect, const Vector3 & vSrcCenter,
	Vector3 vSrcAxis[2], float fSrcLength[2], const Vector3 & vDestCenter, 
	Vector3 vDestAxis[2], float fDestLength[2])
{
	Vector3	vAxis = vSrcAxis[0];

	Vector3 vL = vSrcCenter - vDestCenter;

	float	fDist = abs(vAxis.Dot(vL));
	float	fRadius[2] = {};
	fRadius[0] = fSrcLength[0];
	fRadius[1] = abs(vAxis.Dot(vDestAxis[0])) * fDestLength[0] + abs(vAxis.Dot(vDestAxis[1])) * fDestLength[1];

	if (fDist > fRadius[0] + fRadius[1])
		return false;

	vAxis = vSrcAxis[1];
	fDist = abs(vAxis.Dot(vL));
	fRadius[0] = fSrcLength[1];
	fRadius[1] = abs(vAxis.Dot(vDestAxis[0])) * fDestLength[0] + abs(vAxis.Dot(vDestAxis[1])) * fDestLength[1];

	if (fDist > fRadius[0] + fRadius[1])
		return false;

	vAxis = vDestAxis[0];
	fDist = abs(vAxis.Dot(vL));
	fRadius[0] = fDestLength[0];
	fRadius[1] = abs(vAxis.Dot(vSrcAxis[0])) * fSrcLength[0] + abs(vAxis.Dot(vSrcAxis[1])) * fSrcLength[1];

	if (fDist > fRadius[0] + fRadius[1])
		return false;

	vAxis = vDestAxis[1];
	fDist = abs(vAxis.Dot(vL));
	fRadius[0] = fDestLength[1];
	fRadius[1] = abs(vAxis.Dot(vSrcAxis[0])) * fSrcLength[0] + abs(vAxis.Dot(vSrcAxis[1])) * fSrcLength[1];

	if (fDist > fRadius[0] + fRadius[1])
		return false;

	return true;
}

bool CCollision::CollisionRectToPixel(Vector3 & vIntersect, const Vector3 & vSrcMin, 
	const Vector3 & vSrcMax, const Vector3 & vDestMin, const Vector3 & vDestMax, 
	unsigned char * pPixel, int iPixelSize, int iPixelCountX, int iPixelCountY, 
	unsigned char * pIgnoreColor)
{
	if(!CollisionRectToRect(vIntersect, vSrcMin, vSrcMax, vDestMin, vDestMax))
		return false;

	// 두 사각형의 교집합을 구한다.
	float l = vSrcMin.x > vDestMin.x ? vSrcMin.x : vDestMin.x;
	float r = vSrcMax.x < vDestMax.x ? vSrcMax.x : vDestMax.x;
	float t = vSrcMax.y < vDestMax.y ? vSrcMax.y : vDestMax.y;
	float b = vSrcMin.y > vDestMin.y ? vSrcMin.y : vDestMin.y;

	// 이게 아니라면 픽셀을 조사해야 한다.
	for (int y = b; y <= t; ++y)	
	{
		int	iY = y - vDestMin.y;

		if (iY == iPixelCountY)
			continue;

		for (int x = l; x <= r; ++x)
		{
			int	iX = x - vDestMin.x;

			if (iX == iPixelCountX)
				continue;

			int	iIndex = iY * iPixelCountX * iPixelSize + iX * iPixelSize;

			if (pPixel[iIndex] == pIgnoreColor[0] && pPixel[iIndex + 1] == pIgnoreColor[1] &&
				pPixel[iIndex + 2] == pIgnoreColor[2])
				continue;

			vIntersect.x = x;
			vIntersect.y = y;
			return true;
		}
	}

	return false;
}
