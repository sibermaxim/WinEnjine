#include "TestEnjine.h"



CTestEnjine::CTestEnjine()
{
}


CTestEnjine::~CTestEnjine()
{
}

BOOL CTestEnjine::InitInstance()
{
	m_view.Create();
	
	return TRUE;
}
