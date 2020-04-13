#include "FontManager.h"
#include "Device.h"

DEFINITION_SINGLE(CFontManager)

CFontManager::CFontManager() :
	m_pWriteFactory(nullptr)
{
}

CFontManager::~CFontManager()
{
	SAFE_RELEASE_NORMAL_MAP(m_mapTextFormat);
	SAFE_RELEASE_NORMAL_MAP(m_mapBrush);
	SAFE_RELEASE(m_pWriteFactory);
}

bool CFontManager::Init()
{
	// DirectWrite ���丮 ���� �Լ�
	// HRESULT DWriteCreateFactory(DWRITE_FACTORY_TYPE factoryType, REFIID iid, IUnknown **factory);

	// 1. DWRITE_FACTORY_TYPE factoryType - ���丮�� �������� �ݸ������� ���Ѵ�.  �ݸ��� �� DWRITE_FACTORY_TYPE_ISOLATED 
	// 2. REFIID iid - DirectWrite ���丮 �������̽��� �ĺ��ϴ� GUID ��
	// 3. ���� �� DirectWrite ���丮�� ��ȯ ���� ������
	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pWriteFactory), (IUnknown**)&m_pWriteFactory)))
		return false;

	CreateTextFormat("NormalText", TEXT("�ü�ü"), DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_EXPANDED, 20.f, TEXT("ko"));
	CreateTextFormat("NormalText1", TEXT("Noto Sans CJK KR Black"), DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_EXPANDED, 20.f, TEXT("ko"));

	return true;
}

bool CFontManager::CreateTextFormat(const string& strName, const TCHAR * pFontName, int iWeight, int iStyle, int iStretch, float fSize,
	const TCHAR * pLocalName)
{
	IDWriteTextFormat*	pFormat = FindFont(strName);

	if (pFormat)
		return false;

	/*
	�ؽ�Ʈ ���̾ƿ��� ���Ǵ� �ؽ�Ʈ �������

	HRESULT CreateTextFormat(1, 2, 3, 4, 5, 6, 7, 8)
	1. WCHAR const* fontFamilyName	-	��Ʈ�� �̸�.
	2. IDWriteFontCollection* fontCollection	- �� ���� nullptr, ex) Arial ��Ʈ�� Arial Baclk ���� �÷����� ������ �ִ�.
	3. DWRITE_FONT_WEIGHT fontWeight	- ��Ʈ�� ����, DWRITE_FONT_WEIGHT ����ü�� �� �� ������ ũ��� ������ ���� �ȴ�.
	4. DWRITE_FONT_STYLE fontStyle	-	��Ʈ ��Ÿ��, DWRITE_FONT_STYLE ����ü / ����, ���, ����� ��Ÿ�ϵ��� �ִ�.
	5. DWRITE_FONT_STRETCH fontStretch	-	���� ����ũ�⿡�� �þ����� ����
	6. FLOAT fontSize	-	���� ũ��
	7. WCHAR const* localeName	- ����� ���� �̸�. �̱��� en-us �̰� �ѱ��� ko-KR �Ϻ��� ja-JP �̸� ������ en-uk �̴�.
	8. IDWriteTextFormat** textFormat	-	����� ����� IDWriteTextFormat ������
	*/

	if (FAILED(m_pWriteFactory->CreateTextFormat(pFontName, nullptr, (DWRITE_FONT_WEIGHT)iWeight,
		(DWRITE_FONT_STYLE)iStyle, (DWRITE_FONT_STRETCH)iStretch, fSize, pLocalName, &pFormat)))
		return false;

	m_mapTextFormat.insert(make_pair(strName, pFormat));

	return true;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(float r, float g, float b, float a)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(r, g, b, a);

	if (pBrush)
		return pBrush;

	// ������ ���� �⺻ �������� 1.f�� �� �귯���� �����.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF ����ü, �ܼ� r,g,b,a �� ä���ִ� ����ü�̴�.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	��ȯ ���� �귯���� ������
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(CreateColorKey(r, g, b, a), pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(r, g, b, a);

	if (pBrush)
		return pBrush;

	// ������ ���� �⺻ �������� 1.f�� �� �귯���� �����.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF ����ü, �ܼ� r,g,b,a �� ä���ִ� ����ü�̴�.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	��ȯ ���� �귯���� ������
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(r / 255.f, g / 255.f, b / 255.f, a / 255.f), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(CreateColorKey(r, g, b, a), pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(const Vector4 & vColor)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(vColor);

	if (pBrush)
		return pBrush;

	// ������ ���� �⺻ �������� 1.f�� �� �귯���� �����.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF ����ü, �ܼ� r,g,b,a �� ä���ִ� ����ü�̴�.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	��ȯ ���� �귯���� ������
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(vColor.x, vColor.y, vColor.z, vColor.w), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(CreateColorKey(vColor), pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::CreateColor(UINT iColor)
{
	ID2D1SolidColorBrush*	pBrush = FindBrush(iColor);

	if (pBrush)
		return pBrush;

	// floatŸ������  iColor��  �и��Ѵ�.
	float	r, g, b, a;

	b = (iColor & 0x000000ff) / 255.f;
	g = ((iColor >> 8) & 0x000000ff) / 255.f;
	r = ((iColor >> 16) & 0x000000ff) / 255.f;
	a = ((iColor >> 24) & 0x000000ff) / 255.f;

	// ������ ���� �⺻ �������� 1.f�� �� �귯���� �����.
	// HRESULT ID2D1RenderTarget::CreateSolidColorBrush(1, 2)
	// 1. const D2D1_COLOR_F &color		- D2D1::ColorF ����ü, �ܼ� r,g,b,a �� ä���ִ� ����ü�̴�.
	// 2. ID2D1SolidColorBrush **solidColorBrush	-	��ȯ ���� �귯���� ������
	if (FAILED(_RENDERTARGET2D->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &pBrush)))
		return nullptr;

	m_mapBrush.insert(make_pair(iColor, pBrush));

	return pBrush;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(float r, float g, float b, float a)
{
	UINT	iKey = CreateColorKey(r, g, b, a);

	auto	iter = m_mapBrush.find(iKey);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(BYTE r, BYTE g, BYTE b, BYTE a)
{
	UINT	iKey = CreateColorKey(r, g, b, a);

	auto	iter = m_mapBrush.find(iKey);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(const Vector4 & vColor)
{
	UINT	iKey = CreateColorKey(vColor);

	auto	iter = m_mapBrush.find(iKey);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

ID2D1SolidColorBrush * CFontManager::FindBrush(UINT iColor)
{
	auto	iter = m_mapBrush.find(iColor);

	if (iter == m_mapBrush.end())
		return nullptr;

	return iter->second;
}

UINT CFontManager::CreateColorKey(float r, float g, float b, float a)
{
	UINT	iColor = 0;		// 4Byte ������ �����. 1Byte �� A, R, G, B ���� �����Ŵ�.
	BYTE	R, G, B, A;		// ���� ǥ���� ���� 1Byte���� 4���� �����.

	R = (BYTE)(r * 255);	// R = { 0 < R < 1 } �� ���̴�. % ������ ���ϱ� ���� (���� ���� * 255) �� ���ش�.
	G = (BYTE)(g * 255);
	B = (BYTE)(b * 255);
	A = (BYTE)(a * 255);


	// ������ R,G,B,A ���� �ƴ϶� A,R,G,B ������ �� ���̴�.
	// ���� A(����) ���� ��Ʈ�� �־��ش�.
	// ���⼭ �߿��Ѱ� ��Ʈ�� �����ʿ������� ä������.
	// A = 0x3A   �̰�� int�� ����ȯ�Ǽ� 0x0000003A �� �ȴ�.
	// iColor = iColor | A; �� �ص� �Ȱ���
	iColor = A;

	iColor = (iColor << 8) | R;	// ��Ʈ�� 8ĭ(1Byte) �������� �о� �ְ�, �� ���� �� R���� ���� ��Ʈ�� OR ������ �Ͽ� ������ 8ĭ(1Byte)�� ä���ش�.
	iColor = (iColor << 8) | G; // ��Ʈ�� 8ĭ(1Byte) �� �������� �о� �ְ�, �� ���� �� G���� ���� ��Ʈ�� OR ������ �Ͽ� ������ 8ĭ(1Byte)�� ä���ش�.
	iColor = (iColor << 8) | B;

	return iColor;
}

UINT CFontManager::CreateColorKey(BYTE r, BYTE g, BYTE b, BYTE a)
{
	UINT	iColor = 0;

	iColor = a;

	iColor = (iColor << 8) | r;
	iColor = (iColor << 8) | g;
	iColor = (iColor << 8) | b;

	return iColor;
}

UINT CFontManager::CreateColorKey(const Vector4 & vColor)
{
	UINT	iColor = 0;
	BYTE	r, g, b, a;

	r = (BYTE)(vColor.x * 255);
	g = (BYTE)(vColor.y * 255);
	b = (BYTE)(vColor.z * 255);
	a = (BYTE)(vColor.w * 255);

	iColor = a;

	iColor = (iColor << 8) | r;
	iColor = (iColor << 8) | g;
	iColor = (iColor << 8) | b;

	return iColor;
}

IDWriteTextLayout * CFontManager::CreateTextLayout(const TCHAR * pText, IDWriteTextFormat * pFormat, float fWidth, float fHeight)
{
	IDWriteTextLayout*	pLayout = nullptr;

	// ���ڿ�, �ؽ�Ʈ ���� ����(Layout)�� �����.
	//HRESULT IDWriteFactory::CreateTextLayout(1, 2, 3, 4, 5, 6)

	// 1. WCHAR const *string	-	������ ���ڿ�
	// 2. UINT32 stringLength	-	���ڿ��� ����
	// 3. IDWriteTextFormat *textFormat	-	���ڿ��� ���� �� ������ ��Ÿ���� ��ü�� ���� ������
	// 4. FLOAT maxWidth		-	���ڿ��� ��� ������ �ʺ�
	// 5. FLOAT maxHeight		-	���ڿ��� ��� ������ ����
	// 6. IDWriteTextLayout **textLayout	-	��ȯ ���� ���̾ƿ��� ������

	if (FAILED(m_pWriteFactory->CreateTextLayout(pText, lstrlen(pText), pFormat, fWidth, fHeight, &pLayout)))
		return nullptr;

	return pLayout;
}

IDWriteTextLayout * CFontManager::CreateTextLayout(const TCHAR * pText, const string & strFormat, float fWidth, float fHeight)
{
	IDWriteTextFormat*	pFormat = FindFont(strFormat);

	if (!pFormat)
		return nullptr;

	IDWriteTextLayout*	pLayout = nullptr;

	// ���ڿ�, �ؽ�Ʈ ���� ����(Layout)�� �����.
	//HRESULT IDWriteFactory::CreateTextLayout(1, 2, 3, 4, 5, 6)

	// 1. WCHAR const* string	-	������ ���ڿ�
	// 2. UINT32 stringLength	-	���ڿ��� ����
	// 3. IDWriteTextFormat* textFormat	-	���ڿ��� ���� �� ������ ��Ÿ���� ��ü�� ���� ������
	// 4. FLOAT maxWidth	-	���ڿ��� ��� ������ �ʺ�
	// 5. FLOAT maxHeight	-	���ڿ��� ��� ������ ����
	// 6. IDWriteTextLayout** textLayout	-	��ȯ ���� ���̾ƿ��� ������

	if (FAILED(m_pWriteFactory->CreateTextLayout(pText, lstrlen(pText), pFormat, fWidth, fHeight, &pLayout)))
		return nullptr;

	return pLayout;
}

IDWriteTextFormat * CFontManager::FindFont(const string & strName)
{
	unordered_map<string, IDWriteTextFormat*>::iterator	iter = m_mapTextFormat.find(strName);

	if (iter == m_mapTextFormat.end())
		return nullptr;

	return iter->second;
}
