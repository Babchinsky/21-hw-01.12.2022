#include "ReadFileThreadDlg.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	ReadFileThreadDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ReadFileThreadDlg::DlgProc);
}