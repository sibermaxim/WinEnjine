#pragma once
#include "AppEnjine\WinApp.h"
#include "MyView.h"

class CTestEnjine : public CWinApp
{
public:
	CTestEnjine();
	virtual  ~CTestEnjine();

	virtual BOOL InitInstance();

private:

	CMyView m_view;
};

