#include "ParentProcessDlg.h"

ParentProcessDlg* ParentProcessDlg::ptr = NULL;

ParentProcessDlg::ParentProcessDlg(void)
{
	ptr = this;
}

ParentProcessDlg::~ParentProcessDlg(void)
{

}

void ParentProcessDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void ParentProcessDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1)
	{
		CreateMutex(0, FALSE, TEXT("{9611A39B-4BC4-43C3-8B29-D1E8D5EC2DBB}"));

		STARTUPINFO st = { sizeof(st) };
		PROCESS_INFORMATION pr;

		TCHAR filename[20];
		wsprintf(filename, TEXT("%s"), TEXT("WriteFileThread.exe"));

		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);

		ZeroMemory(&st, sizeof(st));
		st.cb = sizeof(st);

		wsprintf(filename, TEXT("%s"), TEXT("ReadFileThread.exe"));

		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);
	}
}

BOOL CALLBACK ParentProcessDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}