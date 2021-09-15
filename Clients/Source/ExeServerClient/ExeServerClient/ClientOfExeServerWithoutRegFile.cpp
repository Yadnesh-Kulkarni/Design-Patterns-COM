#include<windows.h>
#include"ExeServerWithoutRegFile.h"
#include<stdio.h>
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[]=TEXT("Client");
	// code
	wndclass.cbSize=sizeof(wndclass);
	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance=hInstance;
	wndclass.lpszClassName=AppName;
	wndclass.lpszMenuName=NULL;
	wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
    // register window class
	RegisterClassEx(&wndclass);
	// create window
	hwnd=CreateWindow(AppName,
		              TEXT("Client Of Exe Server"),
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
                      NULL,
                      NULL,
					  hInstance,
					  NULL);
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	// message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(msg.wParam);
}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// variable declarations
	ITrigo *pITrigo=NULL;
	HRESULT hr;
	float angle,result;
	TCHAR str[255];
	// code
	switch(iMsg)
	{
	case WM_CREATE:
		// initialize COM library
		hr=CoInitialize(NULL);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("COM library can not be initialized"),TEXT("COM Error"),MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		// get ITrigo Interface
		hr=CoCreateInstance(CLSID_Trigo,NULL,CLSCTX_LOCAL_SERVER,IID_ITrigo,(void **)&pITrigo);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("Component Can Not Be Created"),TEXT("COM Error"),MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		angle = 45.0f;
		pITrigo->SinOfAngle(angle,&result);
		swprintf_s(str, TEXT("Sin of %f = %f"), angle, result);
		MessageBox(hwnd,str,TEXT("Sin"),MB_OK);

		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
