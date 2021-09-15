#include<windows.h>
#include"Header.h"
#include<stdio.h>
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// global variable declarations
ISum *pISum=NULL;
ISubtract *pISubtract=NULL;
ISquare *pISquare=NULL;
ISquareRoot *pISquareRoot=NULL;
// WinMain

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErroMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErroMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErroMessage);
		LocalFree(szErroMessage);
	}
	else
	{
		swprintf_s(str, TEXT("Could not find description"));
	}
	MessageBox(hwnd, str, TEXT("COM ERROR"), MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[]=TEXT("ComClient");
	HRESULT hr;
	// code
    // COM Initialization
    hr=CoInitialize(NULL);
    if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("COM Library Can Not Be Initialized.\nProgram Will Now Exit."),TEXT("Program Error"),MB_OK);
		exit(0);
	}
	// WNDCLASSEX initialization
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
		              TEXT("Client Of COM Dll Server"),
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
    // COM Un-initialization
    CoUninitialize();
	return((int)msg.wParam);
}
// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	// function declarations
	void SafeInterfaceRelease(void);
	// variable declarations
	HRESULT hr;
	int iNum1, iNum2, iSum, iSubtraction;
	float fSquare, fSquareRoot;
	TCHAR str[255];
	// code
	switch(iMsg)
	{
	case WM_CREATE:
		hr=CoCreateInstance(CLSID_SumSubtract,NULL,CLSCTX_INPROC_SERVER,
		                    IID_ISquare,(void **)&pISquare);
		iNum1=30;
		fSquare = 0;
		// call MultiplicationOfTwoIntegers() of ISquare to get the Multiplication
		pISquare->SquareOfInteger(iNum1,&fSquare);
		// display the result
		swprintf(str,sizeof(str),TEXT("Square Of %d is %f"),iNum1,fSquare);
		MessageBox(hwnd,str,TEXT("Result"),MB_OK);
		// call QueryInterface() on ISquare's to get ISquareRoot pointer
		hr=pISquare->QueryInterface(IID_ISquareRoot,(void **)&pISquareRoot);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("ISquareRoot Interface Can Not Be Obtained"),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		// as ISquare is now not needed onwords, release it
		pISquare->Release();
		pISquare=NULL;// make relesed interface NULL
		// again initialize arguments hardcoded
		iNum1=200;
		iNum2=25;
		// call DivisionOfTwoIntegers() of ISquareRoot to get the Division
		pISquareRoot->SquareRootOfInteger(iNum1,&fSquareRoot);
		// display the result
		swprintf(str, sizeof(str), TEXT("Square Of %d is %f"), iNum1, fSquareRoot);
		MessageBox(hwnd,str,TEXT("Result"),MB_OK);
		// finally release ISquareRoot
		pISquareRoot->Release();
		pISquareRoot=NULL;// make relesed interface NULL
		// exit the application
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
void SafeInterfaceRelease(void)
{
	// code
	if(pISum)
	{
		pISum->Release();
		pISum=NULL;
	}
	if(pISubtract)
	{
		pISubtract->Release();
		pISubtract=NULL;
	}
	if(pISquare)
	{
		pISquare->Release();
		pISquare=NULL;
	}
	if(pISquareRoot)
	{
		pISquareRoot->Release();
		pISquareRoot=NULL;
	}
}
