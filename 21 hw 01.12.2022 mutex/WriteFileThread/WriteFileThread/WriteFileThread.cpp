#include "WriteFileThreadDlg.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	WriteFileThreadDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WriteFileThreadDlg::DlgProc);
}