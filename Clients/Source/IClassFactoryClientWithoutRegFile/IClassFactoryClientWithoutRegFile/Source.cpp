#include<Windows.h>
#include"ClassFactoryDll.h"
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	HRESULT hr;

	hr = CoInitialize(NULL);//Single Threaded Environment
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Could Not Be Loaded!! Exiting!!"),TEXT("Error"),MB_ICONERROR | MB_OK);
		return 0;
	}


	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance,IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIconSm = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = TEXT("My Class Factory Client Class");
	wndclass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL,TEXT("Class Could Not Be Loaded"),TEXT("ERROR"),MB_ICONERROR | MB_OK);
		return 0;
	}

	hwnd = CreateWindow(TEXT("My Class Factory Client Class"),TEXT("COM CLIENT"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	if (!hwnd)
	{
		MessageBox(NULL, TEXT("Window Could Not Be Loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		return 0;
	}

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize(); // Uninitialize COM library
	return (int)(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void SafeInterfaceRelease(void);
	
	int iNum1 = 0;
	int iNum2 = 0;
	int iNum3 = 0;
	int iNum4 = 0;
	HRESULT hr;
	TCHAR str[255];
	TCHAR szPath[MAX_PATH];
	TCHAR szRegSvr[MAX_PATH];
	TCHAR szCmdLinep[MAX_PATH];
	STARTUPINFO st;
	PROCESS_INFORMATION pInfo;
	DWORD Child = -1;
	BOOL bFlag;
	switch (iMsg)
	{
	case WM_CREATE :
		GetSystemDirectory(szPath,sizeof(szPath));
		wsprintf(szRegSvr,TEXT("%s\\regsvr32.exe"),szPath);
		MessageBox(hwnd,szRegSvr,TEXT("Sys Dir"),MB_OK);
		ZeroMemory(&st, sizeof(STARTUPINFO));
		ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
		wsprintf(szCmdLinep,TEXT("%s C:\\Users\\Yadnesh\\Documents\\Final_COM_Project\\Servers\\01-IClassFactory\\IClassFactoryWithoutRegFile.dll"),szRegSvr);
		CreateProcess(NULL, szCmdLinep, NULL, NULL, FALSE, 0, NULL, NULL, &st, &pInfo);
		WaitForInputIdle(pInfo.hProcess, INFINITE);
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("ISum Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
				DestroyWindow(hwnd);
			}

			iNum1 = 40;
			iNum2 = 50;

			pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);

			wsprintf(str, TEXT("%d + %d = %d"), iNum1, iNum2, iNum3);
			MessageBox(hwnd, str, TEXT("ISum"), MB_OK);

			hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("ISubtract Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
				DestroyWindow(hwnd);
			}

			pISum->Release();
			pISum = NULL;
			iNum1 = 50;
			iNum2 = 40;
			iNum3 = 0;

			pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum4);
			wsprintf(str, TEXT("%d - %d = %d"), iNum1, iNum2, iNum4);
			MessageBox(hwnd, str, TEXT("ISubtract"), MB_OK);

			pISubtract->Release();
			pISubtract = NULL;
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease()
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}

	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}