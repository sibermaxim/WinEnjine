#include <cassert>
#include <tchar.h>

#include "Wnd.h"
#include "WinApp.h"
#include "globalEnjine.h"

CWnd::CWnd(): m_wnd(nullptr)
{
}

CWnd::~CWnd()
{
}

/******************************************************************
 *	функция:		Create()
 *	назначение:		Создание окна с парамертрами по умолчанию.
 * 
 ****************************************************************/
HWND CWnd::Create(HWND parent /* = 0 */)
{
	assert(GetApp());

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	CREATESTRUCT cs;
	ZeroMemory(&cs, sizeof cs);

	PreregisterClass(wc);
	if (wc.lpszClassName)
	{
		RegisterClass(wc);
		cs.lpszClass = wc.lpszClassName;
	}
	else
		cs.lpszClass = _T("Win32++ Window");

	//Установка стилей по умолчанию
	const DWORD dwOverlappedStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	cs.style = WS_VISIBLE | (parent ? WS_CHILD : dwOverlappedStyle);

	if(nullptr == parent)
	{
		cs.x = CW_USEDEFAULT;
		cs.y = CW_USEDEFAULT;
		cs.cx = CW_USEDEFAULT;
		cs.cy = CW_USEDEFAULT;
	}
	
	//возможность изменить параметры CREATESTRUCT  
	PreCreate(cs);
	
	DWORD style = cs.style & ~WS_VISIBLE;
	HWND wnd;
	
	//создаем окно
#ifndef _WIN32_WCE
	wnd = CreateEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, style,
		cs.x, cs.y, cs.cx, cs.cy, parent, cs.hMenu, cs.lpCreateParams);

	if(cs.style & WS_VISIBLE)
	{
		if (cs.style & WS_MAXIMIZE)
			ShowWindow(SW_MAXIMIZE);
		
	}
#else
	
#endif
	return wnd;
}

/******************************************************************
*	функция:		CreateEx()
*	назначение:		Создание окна с указанными парамертрами.
*
****************************************************************/
HWND CWnd::CreateEx(DWORD extStyle, LPCTSTR pclassName, LPCTSTR pWindowName, DWORD style, int x, int y, int width, int height, HWND parent, HMENU idOrMenu, LPVOID lparam)
{
	assert(GetApp());
	assert(!IsWindow());

	LPCTSTR className;
	if (pclassName == 0 || pclassName[0] == _T('\0'))
		className = _T("Win32++ Window");
	else
		className =  pclassName;

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);
	wc.lpszClassName = className;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);

	if(RegisterClass(wc) == 0)
	{
		TRACE("*** RegisterClass failed ***\n");
		
	}

	::RegisterClass(&wc);
	HWND wnd = ::CreateWindowEx(extStyle, className, pWindowName, style, x, y, width, height,
		parent, idOrMenu, GetApp()->GetInstanceHandle(), lparam);

	if(wnd == nullptr)
	{
		
	}
	return wnd;
}

HWND CWnd::GetHwnd() const
{
	return m_wnd;
}

BOOL CWnd::IsWindow() const
{
	return ::IsWindow(*this);
}

/******************************************************************
*	функция:		ShowWindow()
*	назначение:		Устанавливает состояние окна.
*
****************************************************************/
BOOL CWnd::ShowWindow(int showCmd) const
{
	assert(IsWindow());
	return ::ShowWindow(*this, showCmd);
}

CWnd::operator HWND() const
{
	return GetHwnd();
}

void CWnd::PreCreate(CREATESTRUCT & cs)
{
	UNREFERENCED_PARAMETER(cs);
}

inline void CWnd::PreregisterClass(WNDCLASS& wc)
{
	UNREFERENCED_PARAMETER(wc);
}

LRESULT CWnd::StaticWindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(wnd, msg, wparam, lparam);
}

/******************************************************************
*	функция:		RegisterClass()
*	назначение:		Частная функция для регистрации классса окна.
*
****************************************************************/
BOOL CWnd::RegisterClass(WNDCLASS & wc)
{
	assert(GetApp());
	assert(('\0' != wc.lpszClassName[0] && lstrlen(wc.lpszClassName) <= MAX_STRING_SIZE));

	//проверка, класс уже зарегистрирован?
	WNDCLASS wcTest;
	ZeroMemory(&wcTest, sizeof wcTest);
	BOOL done = FALSE;

	if(::GetClassInfo(GetApp()->GetInstanceHandle(), wc.lpszClassName, &wcTest))
	{
		wc = wcTest;
		done = TRUE;
	}

	if(!done)
	{
		wc.hInstance = GetApp()->GetInstanceHandle();
		wc.lpfnWndProc = CWnd::StaticWindowProc;

		//регистрация
		VERIFY(::RegisterClass(&wc) != 0);
		done = TRUE;
	}
	return done;
}
