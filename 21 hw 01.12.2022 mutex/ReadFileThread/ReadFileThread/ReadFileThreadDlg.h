#pragma once
#include "header.h"

class ReadFileThreadDlg
{
public:
	ReadFileThreadDlg(void);
public:
	~ReadFileThreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ReadFileThreadDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};