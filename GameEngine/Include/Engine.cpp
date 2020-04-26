#include "Engine.h"
#include "Device.h"
#include "TimerManager.h"
#include "Timer.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Scheduler.h"
#include "CollisionManager.h"
#include "Render/RenderManager.h"
#include "FontManager.h"

DEFINITION_SINGLE(CEngine)

#define	LECTURE

bool CEngine::m_bLoop = true;

CEngine::CEngine()	:
	m_pTimer(nullptr)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(1279);

	m_bEditorBegin	= false;
}

CEngine::~CEngine()
{
	DESTROY_SINGLE(CSceneManager);

	DESTROY_SINGLE(CRenderManager);
	DESTROY_SINGLE(CCollisionManager);
	DESTROY_SINGLE(CScheduler);
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CResourceManager);
	
	DESTROY_SINGLE(CTimerManager);
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CFontManager);

	DESTROY_SINGLE(CDevice);
}

bool CEngine::Init(const TCHAR * pClass, const TCHAR * pTitle, 
	HINSTANCE hInst, int iIconID, int iSmallIconID, int iWidth, 
	int iHeight, bool bWindowMode)
{
	m_hInst = hInst;

	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;

	Register(pClass, iIconID, iSmallIconID);
	Create(pClass, pTitle);

	return Init(m_hInst, m_hWnd, iWidth, iHeight, bWindowMode);
}

bool CEngine::Init(HINSTANCE hInst, HWND hWnd, int iWidth, int iHeight,
	bool bWindowMode)
{
	m_tRS.iWidth = iWidth;
	m_tRS.iHeight = iHeight;
	m_hWnd = hWnd;
	m_hInst = hInst;

	// Device �ʱ�ȭ
	if (!GET_SINGLE(CDevice)->Init(hWnd, iWidth, iHeight, bWindowMode))
		return false;

	// Timer ������ �ʱ�ȭ
	if (!GET_SINGLE(CTimerManager)->Init())
		return false;

	// ��ΰ����� �ʱ�ȭ
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	GET_SINGLE(CTimerManager)->CreateTimer("Main");
	m_pTimer = GET_SINGLE(CTimerManager)->FindTimer("Main");

	// ��Ʈ ������ �ʱ�ȭ
	if (!GET_SINGLE(CFontManager)->Init())
		return false;

	// ������ ������ �ʱ�ȭ
	if (!GET_SINGLE(CScheduler)->Init())
		return false;

	// ���ҽ� ������ �ʱ�ȭ
	if (!GET_SINGLE(CResourceManager)->Init())
		return false;

	// �浹������ �ʱ�ȭ
	if (!GET_SINGLE(CCollisionManager)->Init())
		return false;

	// �Է� ������ �ʱ�ȭ
	if (!GET_SINGLE(CInput)->Init())
		return false;

	// ������ ������ �ʱ�ȭ
	if(!GET_SINGLE(CRenderManager)->Init())
		return false;

	// ��� ������ �ʱ�ȭ
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	return true;
}

int CEngine::Run()
{
	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}

void CEngine::Logic()
{
	m_pTimer->Update();

	float	fTime = m_pTimer->GetDeltaTime();

	GET_SINGLE(CInput)->Update(fTime);

	if(Update(fTime) == SC_CHANGE)
		return;

	if(PostUpdate(fTime) == SC_CHANGE)
		return;

	GET_SINGLE(CScheduler)->Update(fTime);

	Render(fTime);
}

int CEngine::Update(float fTime)
{
	return GET_SINGLE(CSceneManager)->Update(fTime);
}

int CEngine::PostUpdate(float fTime)
{
	SCENE_CHANGE sc = GET_SINGLE(CSceneManager)->PostUpdate(fTime);

	GET_SINGLE(CCollisionManager)->Collision(fTime);

	return sc;
}

void CEngine::Render(float fTime)
{
	GET_SINGLE(CDevice)->ClearTarget();

	GET_SINGLE(CSceneManager)->Render(fTime);

	// ����� �����س���.
	GET_SINGLE(CRenderManager)->ComputeRender();

	GET_SINGLE(CRenderManager)->Render(fTime);

	GET_SINGLE(CDevice)->Present();

	GET_SINGLE(CCollisionManager)->Clear();
}

ATOM CEngine::Register(const TCHAR * pClass, int iIconID, int iSmallIconID)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(iIconID));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_MY191101);
	wcex.lpszClassName = pClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(iSmallIconID));

	return RegisterClassExW(&wcex);
}

BOOL CEngine::Create(const TCHAR * pClass, const TCHAR * pTitle)
{
	int	x = 0, y = 0;

#ifdef LECTURE
	x = 0;
	y = 0;
#endif // LECTURE


	m_hWnd = CreateWindowW(pClass, pTitle,
		WS_OVERLAPPEDWINDOW,
		x, y, m_tRS.iWidth,
		m_tRS.iHeight, nullptr, nullptr,
		m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	RECT	rc = { 0, 0, m_tRS.iWidth, m_tRS.iHeight };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, x, y,
		rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CEngine::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
