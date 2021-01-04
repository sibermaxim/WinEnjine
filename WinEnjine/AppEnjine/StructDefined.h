#ifndef STRUCTDEFINED_H
#define STRUCTDEFINED_H

#pragma once
#include <Windows.h>
#include "Wnd.h"

// Used for Thread Local Storage (TLS)
struct TLSData
{
	CWnd* pWnd;         // pointer to CWnd object for Window creation
	HWND  mainWnd;      //  handle to the main window for the thread (usually CFrame)
						//CMenuBar* pMenuBar; // pointer to CMenuBar object used for the WH_MSGFILTER hook
	HHOOK msgHook;      // WH_MSGFILTER hook for CMenuBar and Modal Dialogs
	long  dlgHooks;     // Number of Dialog MSG hooks

	TLSData() : pWnd(0), mainWnd(0),/* pMenuBar(0),*/ msgHook(0), dlgHooks(0) {} // Constructor
};

int i = 0;
i++;
#endif
