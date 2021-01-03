#ifndef WND_H
#define WND_H

#pragma once
#include <Windows.h>

// Defines the maximum size for TCHAR strings
enum Constants
{
	MAX_MENU_STRING = 80,
	MAX_STRING_SIZE = 255
};

class CWnd
{
	friend class CWinApp;
	
public:

	CWnd();
	virtual ~CWnd();
	
	virtual HWND Create(HWND parent = nullptr);
	virtual HWND CreateEx(DWORD extStyle, LPCTSTR pclassName, LPCTSTR pWindowName,
						  DWORD style, int x, int y, int width, int height, HWND parent,
						  HMENU idOrMenu, LPVOID lparam = nullptr);

	//��������
	HWND GetHwnd()const;
	
	//������� ��� WIn32 Api �������
	//������� �� ����������� � �� ����� ���� ��������������
	BOOL IsWindow() const;
	BOOL ShowWindow(int showCmd = SW_NORMAL) const;

	operator HWND()const;
	
protected:

	//������ ������� ����������� � �������
	virtual void PreCreate(CREATESTRUCT&cs);
	virtual void PreregisterClass(WNDCLASS& wc);
	
private:

	HWND m_wnd;				//��������� �� ������ ����

	static LRESULT CALLBACK StaticWindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

	BOOL RegisterClass(WNDCLASS& wc);
	
};
#endif
