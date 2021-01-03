#include "globalEnjine.h"

//глобальные функции
inline CWinApp* GetApp()
{
	CWinApp* pApp = CWinApp::SetnGetThis();
	return pApp;
}
