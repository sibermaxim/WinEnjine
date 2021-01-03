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

	//Атрибуты
	HWND GetHwnd()const;
	
	//Обертка для WIn32 Api функций
	//Функции не виртуальные и не могут быть перегруженными
	BOOL IsWindow() const;
	BOOL ShowWindow(int showCmd = SW_NORMAL) const;

	operator HWND()const;
	
protected:

	//данные функции перегрузить и вызвать
	virtual void PreCreate(CREATESTRUCT&cs);
	virtual void PreregisterClass(WNDCLASS& wc);
	
private:

	HWND m_wnd;				//указатель на объект окна

	static LRESULT CALLBACK StaticWindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

	BOOL RegisterClass(WNDCLASS& wc);
	
};
#endif
