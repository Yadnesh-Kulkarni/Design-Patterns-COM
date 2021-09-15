#include<Windows.h>
#include"ClassFactoryDll.h"

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

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
		MessageBox(NULL, TEXT("ISum Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
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

int GetSumOfTwoIntegers(int iNum1,int iNum2)
{
	HRESULT hr;

	if (pISum == NULL && pISubtract == NULL)
	{
	  GetISumInterface();
	}
	else if(pISum == NULL && pISubtract)
	{
		hr = pISubtract->QueryInterface(IID_ISum,(void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISum Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		}
	}

	int iNum3 = -999;
	pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
	return iNum3;
}

int GetSubstractionOfTwoIntegers(int iNum1,int iNum2)
{
	HRESULT hr = NULL;

	if (pISum == NULL && pISubtract == NULL)
	{
	 GetISubtractInterface();
	}
	else if(pISubtract == NULL && pISum)
	{
		hr = pISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		}
	}

	int iNum3 = -999;
	pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
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
