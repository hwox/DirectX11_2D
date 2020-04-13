
#include "Navigation2D.h"
#include "../Component/TileMap.h"
#include "../Component/Tile.h"
#include <stack>

CNavigation2D::CNavigation2D()	:
	m_pTileMap(nullptr),
	m_iOpenCount(0),
	m_iUseCount(0)
{
}

CNavigation2D::~CNavigation2D()
{
}

list<Vector3> CNavigation2D::GetPathList() const
{
	return m_PathList;
}

void CNavigation2D::SetTileMap(CTileMap * pTileMap)
{
	m_pTileMap	= pTileMap;

	m_vecOpen.clear();
	m_vecUse.clear();

	m_vecOpen.resize(m_pTileMap->GetTileCount());
	m_vecUse.resize(m_pTileMap->GetTileCount());
}

bool CNavigation2D::FindPath(const Vector3 & vStart, const Vector3 & vEnd)
{
	if (!m_pTileMap)
		return false;

	CTile*	pStart = m_pTileMap->GetTile(vStart);

	if (!pStart)
		return false;

	CTile*	pEnd = m_pTileMap->GetTile(vEnd);

	if (!pEnd)
		return false;

	m_PathList.clear();

	m_iOpenCount = 0;
	m_iUseCount = 0;

	CTile*	pNode	= nullptr;

	m_vecOpen[m_iOpenCount]	= pStart;
	++m_iOpenCount;

	m_vecUse[m_iUseCount] = pStart;
	++m_iUseCount;
	m_vecUse[m_iUseCount] = pEnd;
	++m_iUseCount;

	while (m_iOpenCount > 0)
	{
		// ������Ͽ��� ����� ���� ���� ��带 ã�´�.
		pNode = m_vecOpen[0];

		int	iIndex = 0;

		for (int i = 1; i < m_iOpenCount; ++i)
		{
			if (pNode->GetG() > m_vecOpen[i]->GetG())
			{
				pNode = m_vecOpen[i];
				iIndex = i;
				break;
			}
		}

		pNode->SetNavInsertType(NIT_CLOSE);

		--m_iOpenCount;
		m_vecOpen[iIndex]	= m_vecOpen[m_iOpenCount];

		// ���س�带 �߽����� �ֺ� ��带 Ž���ؼ� �־�д�.
		if (FindNode(pNode, pEnd, vEnd))
		{
			m_PathList.push_back(vEnd);
			break;
		}
	}

	for (int i = 0; i < m_iUseCount; ++i)
	{
		m_vecUse[i]->ClearNav();
	}

	return !m_PathList.empty();
}

bool CNavigation2D::FindNode(CTile * pNode, CTile * pEnd, const Vector3& vEnd)
{
	// 8���� �̿���带 ���Ѵ�.
	int		iIndexX = pNode->GetIndexX();
	int		iIndexY = pNode->GetIndexY();

	Vector3	vSize = pNode->GetTileSize();

	CTile*	pNeighbor[NND_END] = {};

	switch (m_pTileMap->GetTileType())
	{
	case TT_RECT:
		pNeighbor[NND_LT] = m_pTileMap->GetTileFromIndex(iIndexX - 1, iIndexY + 1);
		pNeighbor[NND_T] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY + 1);
		pNeighbor[NND_RT] = m_pTileMap->GetTileFromIndex(iIndexX + 1, iIndexY + 1);
		pNeighbor[NND_R] = m_pTileMap->GetTileFromIndex(iIndexX + 1, iIndexY);
		pNeighbor[NND_RB] = m_pTileMap->GetTileFromIndex(iIndexX + 1, iIndexY - 1);
		pNeighbor[NND_B] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY - 1);
		pNeighbor[NND_LB] = m_pTileMap->GetTileFromIndex(iIndexX - 1, iIndexY - 1);
		pNeighbor[NND_L] = m_pTileMap->GetTileFromIndex(iIndexX - 1, iIndexY);
		break;

	case TT_ISOMETRIC:
		if (iIndexY % 2 == 0)
		{
			pNeighbor[NND_LT] = m_pTileMap->GetTileFromIndex(iIndexX - 1, iIndexY + 1);
			pNeighbor[NND_RT] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY + 1);
			pNeighbor[NND_RB] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY - 1);
			pNeighbor[NND_LB] = m_pTileMap->GetTileFromIndex(iIndexX - 1, iIndexY - 1);
		}

		else
		{
			pNeighbor[NND_LT] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY + 1);
			pNeighbor[NND_RT] = m_pTileMap->GetTileFromIndex(iIndexX + 1, iIndexY + 1);
			pNeighbor[NND_RB] = m_pTileMap->GetTileFromIndex(iIndexX + 1, iIndexY - 1);
			pNeighbor[NND_LB] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY - 1);
		}

		pNeighbor[NND_T] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY + 2);
		pNeighbor[NND_R] = m_pTileMap->GetTileFromIndex(iIndexX + 1, iIndexY);
		pNeighbor[NND_B] = m_pTileMap->GetTileFromIndex(iIndexX, iIndexY - 2);
		pNeighbor[NND_L] = m_pTileMap->GetTileFromIndex(iIndexX - 1, iIndexY);
		break;
	}

	for (int i = 0; i < NND_END; i++)
	{
		if (!pNeighbor[i])
			continue;

		if (pNeighbor[i]->GetTileOption() == TO_NOMOVE)
			continue;

		NAV_NODE_DIR	eFN1 = NND_END, eFN2 = NND_END;

		if (m_pTileMap->GetTileType() == TT_RECT)
		{
			// ���� ����� ���ʰ� ������ Ÿ���� ������ Ÿ���̰� ������ �� Ÿ���� ���� �ִ� Ÿ���̶��
			// ���������� �ϱ� ���� �밢�� ���� Ÿ���� ���� Ÿ���� ���Ѵ�.
			switch (i)
			{
			case NND_LT:	// ���� �� Ÿ���� ���� Ÿ��
				eFN1 = NND_L;
				eFN2 = NND_T;
				break;
			case NND_RT:
				eFN1 = NND_R;
				eFN2 = NND_T;
				break;
			case NND_LB:
				eFN1 = NND_L;
				eFN2 = NND_B;
				break;
			case NND_RB:
				eFN1 = NND_R;
				eFN2 = NND_B;
				break;
			}
		}

		else
		{
			switch (i)
			{
			case NND_L:
				eFN1 = NND_LT;
				eFN2 = NND_LB;
				break;
			case NND_R:
				eFN1 = NND_RT;
				eFN2 = NND_RB;
				break;
			case NND_T:
				eFN1 = NND_LT;
				eFN2 = NND_RT;
				break;
			case NND_B:
				eFN1 = NND_LB;
				eFN2 = NND_RB;
				break;
			}
		}

		if (eFN1 != NND_END || eFN2 != NND_END)
		{
			if (pNeighbor[eFN1] && pNeighbor[eFN2])
			{
				if (pNeighbor[eFN1]->GetTileOption() == TO_NOMOVE && pNeighbor[eFN2]->GetTileOption() == TO_NOMOVE)
					continue;
			}

			else if (pNeighbor[eFN1])
			{
				if (pNeighbor[eFN1]->GetTileOption() == TO_NOMOVE)
					continue;
			}

			else if (pNeighbor[eFN2])
			{
				if (pNeighbor[eFN2]->GetTileOption() == TO_NOMOVE)
					continue;
			}
		}

		// �̿������ �������� �ִٸ� Ž���� ������.
		if (pNeighbor[i] == pEnd)
		{
			pEnd->SetParent(pNode);

			m_PathList.clear();

			stack<CTile*>	data;

			CTile*	pParent = pNode;

			while (pParent)
			{
				data.push(pParent);
				pParent = pParent->GetParent();
			}

			while (!data.empty())
			{
				CTile*	pData = data.top();
				data.pop();

				Vector3	vCenter(pData->GetCenter().x, pData->GetCenter().y, 0.f);

				m_PathList.push_back(vCenter);
			}

			return true;
		}

		// �̿���尡 ������Ͽ� ���ִ� ����� ��������� ����Ͽ� �� ���� ����������� ��ü�Ѵ�.
		// ��������̶�� �����ϰ� ó�� �߰��Ǵ� ����� ������Ͽ� �߰��Ѵ�.
		if (pNeighbor[i]->GetNavType() == NIT_CLOSE)
			continue;

		// �̿� ��忡������ ���� ���������� ���� �Ÿ��� ���Ѵ�. ���� ���̿� ������ Ÿ���� �ְ� ���� ��� ����.
		float	fH = pNeighbor[i]->GetCenter().Distance(pEnd->GetCenter());

		// ���� ������ ��������� ��������� �����Ѵ�.
		float	fG = 0.f;

		switch (m_pTileMap->GetTileType())
		{
		case TT_RECT:
			switch (i)
			{
			case NND_T:
			case NND_B:
				fG = pNode->GetG() + pNeighbor[i]->GetTileSize().y;
				break;

			case NND_R:
			case NND_L:
				fG = pNode->GetG() + pNeighbor[i]->GetTileSize().x;
				break;

			default:
				fG = pNode->GetG() + sqrtf(vSize.x * vSize.x + vSize.y * vSize.y);
				break;
			}
			break;

		case TT_ISOMETRIC:
			switch (i)
			{
			case NND_T:
			case NND_B:
				fG = pNode->GetG() + pNeighbor[i]->GetTileSize().y;
				break;

			case NND_R:
			case NND_L:
				fG = pNode->GetG() + pNeighbor[i]->GetTileSize().x;
				break;

			default:
			{
				float	fWidth = vSize.x / 2.f;
				float	fHeight = vSize.y / 2.f;
				fG = pNode->GetG() + sqrtf(fWidth * fWidth + fHeight * fHeight);
			}
			break;
			}
			break;
		}

		if (pNeighbor[i]->GetNavType() == NIT_OPEN)
		{
			// GetG() ���� ���� ��忡 ������� ��� ��������� ����ִ�.
			if (pNeighbor[i]->GetG() > fG)
			{
				pNeighbor[i]->SetParent(pNode);
				pNeighbor[i]->SetCost(fG, fH);
			}
		}

		else
		{
			m_vecUse[m_iUseCount] = pNeighbor[i];
			++m_iUseCount;
			pNeighbor[i]->SetNavInsertType(NIT_OPEN);
			pNeighbor[i]->SetParent(pNode);
			pNeighbor[i]->SetCost(fG, fH);

			m_vecOpen[m_iOpenCount] = pNeighbor[i];
			++m_iOpenCount;
		}
	}

	return false;
}
