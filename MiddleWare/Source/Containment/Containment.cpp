#include<Windows.h>
#include"Containment.h"

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
IMultiplication *pIMultiply = NULL;
IDivision *pIDivide = NULL;

void InitComEngine()
{
	HRESULT hr;
	hr = CoInitialize(NULL);//Single Threaded Environment
}

void UnInitComEngine()
{
	CoUninitialize();
}

void GetISumInterface()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ISum Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
}

void GetISubtractInterface()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISubtract, (void **)&pISubtract);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ISubtract Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
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

/*int GetSumOfTwoIntegers(int iNum1,int iNum2)
{
	HRESULT hr;

	GetISumInterface();

	int iNum3 = -999;
	pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
	pISum->Release();
	return iNum3;
}

int GetSubstractionOfTwoIntegers(int iNum1,int iNum2)
{
	HRESULT hr = NULL;

    GetISubtractInterface();

	int iNum3 = -999;
	pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
	pISubtract->Release();

	return iNum3;
}*/

int GetMultiplicationOfTwoIntegers(int iNum1, int iNum2)
{
	HRESULT hr;
	GetISumInterface();
	hr = pISum->QueryInterface(IID_IMultiplication,(void**)&pIMultiply);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiply Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
	pISum->Release();

	int iNum3 = -999;
	pIMultiply->MultiplicationOfTwoIntegers(iNum1,iNum2,&iNum3);
	pIMultiply->Release();

	return iNum3;	
}

int GetDivisionOfTwoIntegers(int iNum1, int iNum2)
{
	HRESULT hr;
	GetISubtractInterface();
	hr = pISubtract->QueryInterface(IID_IDivision, (void**)&pIDivide);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivide Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
	pISubtract->Release();

	int iNum3 = -999;
	pIDivide->DivisionOfTwoIntegers(iNum1, iNum2, &iNum3);
	pIDivide->Release();
	
	return iNum3;	
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
