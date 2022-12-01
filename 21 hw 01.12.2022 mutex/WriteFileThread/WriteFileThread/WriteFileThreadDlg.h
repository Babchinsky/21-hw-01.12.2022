#pragma once
#include "header.h"

class WriteFileThreadDlg
{
public:
	WriteFileThreadDlg(void);
public:
	~WriteFileThreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static WriteFileThreadDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};
