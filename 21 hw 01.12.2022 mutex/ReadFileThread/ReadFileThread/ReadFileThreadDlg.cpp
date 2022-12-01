#include "ReadFileThreadDlg.h"

ReadFileThreadDlg* ReadFileThreadDlg::ptr = NULL;

ReadFileThreadDlg::ReadFileThreadDlg(void)
{
	ptr = this;
}

ReadFileThreadDlg::~ReadFileThreadDlg(void)
{

}

void ReadFileThreadDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI ReadFile_Thread(LPVOID lp)
{
	ReadFileThreadDlg* ptr = (ReadFileThreadDlg*)lp;
	char buf[4096];

	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{9611A39B-4BC4-43C3-8B29-D1E8D5EC2DBB}"));
	// ждём сигнальное состояние
	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	// если готов работать, запускаем запись
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ifstream in(TEXT("array.txt"), ios::in);
		if (!in)
		{
			MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
			return 1;
		}
		ofstream out("CopyArray.txt", ios::binary | ios::out || ios::trunc);
		while (!in.eof())
		{
			in.read(buf, 4096);
			int n = in.gcount();
			out.write(buf, n);
		}
		out.close();
		in.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Чтение данных из файла array.txt завершено!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

BOOL ReadFileThreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, ReadFile_Thread, this, 0, NULL);
	return TRUE;
}


BOOL CALLBACK ReadFileThreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}