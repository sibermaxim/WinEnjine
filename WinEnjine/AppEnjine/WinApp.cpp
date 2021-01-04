#include <cassert>
#include <tchar.h>

#include "WinApp.h"
#include "Wnd.h"

CWinApp::CWinApp():m_Callback(nullptr)
{
	if(nullptr != SetnGetThis())
	{
		
	}
	SetnGetThis(this);

	m_instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

	SetCallback();
}

CWinApp::~CWinApp()
{
}

BOOL CWinApp::InitInstance()
{
	return 0;
}

inline int CWinApp::Run()
{
	if(InitInstance())
	{
		
	}
	return 0;
}

TLSData * CWinApp::SetTlsData()
{
	return nullptr;
}

/***************************************************
 *
 *
 *
 * 
 **************************************************/
inline void CWinApp::SetCallback()
{
	WNDCLASS defaultWC;
	ZeroMemory(&defaultWC, sizeof defaultWC);

	LPCTSTR pClassName = _T("Win32++ Temporary Window Class");
	defaultWC.hInstance = GetInstanceHandle();
	defaultWC.lpfnWndProc = CWnd::StaticWindowProc;
	defaultWC.lpszClassName = pClassName;

	VERIFY(::RegisterClass(&defaultWC) != 0);

	ZeroMemory(&defaultWC, sizeof defaultWC);
	::GetClassInfo(GetInstanceHandle(), pClassName, &defaultWC);

	assert(defaultWC.lpfnWndProc);
	m_Callback = defaultWC.lpfnWndProc;
	VERIFY(::UnregisterClass(pClassName, GetInstanceHandle()) != 0);
}

CWinApp* CWinApp::SetnGetThis(CWinApp * pThis, bool reset)
{
	static CWinApp* pWinApp = nullptr;

	if (pWinApp == nullptr)
		pWinApp = pThis;
	else
		assert(pThis == nullptr);
	
	return pWinApp;
}

HINSTANCE CWinApp::GetInstanceHandle() const
{
	return m_instance;
}
