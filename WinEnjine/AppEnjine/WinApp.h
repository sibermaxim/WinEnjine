#ifndef WINAPP_H
#define WINAPP_H
#pragma once

#include <windows.h>

// Define the VERIFY macro
// In debug mode, VERIFY asserts if the expression evaluates to zero
// In release mode, VERIFY evaluates the expression, but doesn't assert.
#ifndef VERIFY
#ifdef NDEBUG
#define VERIFY(f) ((void)(f))
#else
#define VERIFY(f) assert(f)
#endif
#endif


class CWinApp
{
	friend CWinApp* GetApp();

	friend class CWnd;
	
public:
	CWinApp();
	virtual ~CWinApp();

	virtual  BOOL InitInstance();
	virtual int Run();

private:

	WNDPROC m_Callback;				//адрес функции CWnd::StaticWndowProc

	HINSTANCE m_instance;
	
	void SetCallback();

	static CWinApp* SetnGetThis(CWinApp* pThis = 0, bool reset = false);

	HINSTANCE GetInstanceHandle() const;
	
};

#endif

