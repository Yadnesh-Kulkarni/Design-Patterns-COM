#include<Windows.h>
#include"Aggregation.h"

ISquare *pISquare = NULL;
ISquareRoot *pISquareRoot = NULL;

void InitComEngine()
{
	HRESULT hr;
	hr = CoInitialize(NULL);//Single Threaded Environment
}

void UnInitComEngine()
{
	CoUninitialize();
}

void GetISquareInterface()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISquare, (void **)&pISquare);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ISum Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
}

void GetISquareRootInterface()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISquareRoot, (void **)&pISquareRoot);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ISum Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
}

void SafeInterfaceRelease()
{
	if (pISquare)
	{
		pISquare->Release();
		pISquare = NULL;
	}

	if (pISquareRoot)
	{
		pISquareRoot->Release();
		pISquareRoot = NULL;
	}
}

float GetSquareOfInteger(int iNum1)
{
	GetISquareInterface();
	float fSquare = 0;
	pISquare->SquareOfInteger(iNum1, &fSquare);
	return fSquare;
}

float GetSquareRootOfInteger(int iNum1)
{
	GetISquareRootInterface();
	float fSquareRoot = 0;
	pISquareRoot->SquareRootOfInteger(iNum1, &fSquareRoot);
	return fSquareRoot;
}

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		InitComEngine();
		break;
	case DLL_PROCESS_DETACH:
		SafeInterfaceRelease();
		UnInitComEngine();
		break;
	}
	return(TRUE);
}
