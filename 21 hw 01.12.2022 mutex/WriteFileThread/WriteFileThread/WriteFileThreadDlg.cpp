#include "WriteFileThreadDlg.h"

WriteFileThreadDlg* WriteFileThreadDlg::ptr = NULL;

WriteFileThreadDlg::WriteFileThreadDlg(void)
{
	ptr = this;
}

WriteFileThreadDlg::~WriteFileThreadDlg(void)
{

}

void WriteFileThreadDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI WriteFile_Thread(LPVOID lp)
{
	WriteFileThreadDlg* ptr = (WriteFileThreadDlg*)lp;
	char buf[4096];

	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("9611A39B-4BC4-43C3-8B29-D1E8D5EC2DBB"));
	// ждём сигнальное состояние
	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	// если готов работать, запускаем запись
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ofstream out(TEXT("array.txt"), ios::trunc);
		if (!out.is_open())
		{
			MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
			return 1;
		}
		int A[100];
		for (int i = 0; i < 100; i++)
		{
			A[i] = rand() % 50;
			out << A[i] << ' ';
		}
		out.close();

		ReleaseMutex(hMutex);

		MessageBox(0, TEXT("Поток записал информацию в файл"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

BOOL WriteFileThreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, WriteFile_Thread, this, 0, NULL);
	return TRUE;
}


BOOL CALLBACK WriteFileThreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}