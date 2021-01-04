#ifndef GLOBALENJINE_H
#define GLOBALENJINE_H
#pragma once

#include <atlbase.h>
#include "WinApp.h"

// Trace sends a string to the debug/output pane, or an external debugger
inline void Trace(LPCSTR str)
{
	USES_CONVERSION;
	LPCWSTR w = A2W(str);
	OutputDebugString((w));
}

#ifndef TRACE
	#ifdef NDEBUG
		#define TRACE(str) (void(0))
	#else
		#define TRACE(str) Trace(str)
	#endif
#endif



extern inline CWinApp* GetApp();

#endif
