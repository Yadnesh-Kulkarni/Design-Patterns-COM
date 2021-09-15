#include<Windows.h>
#include<stdio.h>
#include"Monikers.h"

IOddNumber *pIOddNumber = NULL;
IOddNumberFactory *pIOddNumberFactory = NULL;
IBindCtx *pIBindCtx = NULL;
IMoniker *pIMoniker = NULL;

void InitComEngine()
{
	HRESULT hr;
	hr = CoInitialize(NULL);//Single Threaded Environment
}

void UnInitComEngine()
{
	CoUninitialize();
}

void GetIBind()
{
	HRESULT hr;
	if (hr = CreateBindCtx(0, &pIBindCtx) != S_OK)
	{
		MessageBox(NULL, TEXT("Failed To Get IBindCtx Interface Pointer"), TEXT("Error"), MB_OK);
	}
}

void GetIMoniker()
{
	ULONG uEaten;
	HRESULT hr;
	LPOLESTR szCLSID = NULL;
	wchar_t wszCLSID[255], wszTemp[255], *ptr;
	StringFromCLSID(CLSID_OddNumber, &szCLSID);
	wcscpy_s(wszTemp, szCLSID);
	ptr = wcschr(wszTemp, '{');
	ptr = ptr + 1;// to remove first opening '{' from CLSID string
	wcscpy_s(wszTemp, ptr);
	wszTemp[(int)wcslen(wszTemp) - 1] = '\0';// to remove last closing '}' from CLSID string
	wsprintf(wszCLSID, TEXT("clsid:%s"), wszTemp);
	// Get Moniker For This CLSID
	hr = MkParseDisplayName(pIBindCtx, wszCLSID, &uEaten, &pIMoniker);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed To Get IMoniker Interface Pointer"), TEXT("Error"), MB_OK);
		pIBindCtx->Release();
		pIBindCtx = NULL;
	}
}

void Bind()
{
	HRESULT hr;
	hr = pIMoniker->BindToObject(pIBindCtx, NULL, IID_IOddNumberFactory, (void**)&pIOddNumberFactory);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed To Get Custom Activation - IOddNumberFactory Interface Pointer"), TEXT("Error"), MB_OK);
		pIMoniker->Release();
		pIMoniker = NULL;
		pIBindCtx->Release();
		pIBindCtx = NULL;
	}
}

int SetFirstAndGetNextOddNumber(int iNum1)
{
	HRESULT hr;
	GetIBind();
	GetIMoniker();
	Bind();
	hr = pIOddNumberFactory->SetFirstOddNumber(iNum1, &pIOddNumber);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Can Not Obtain IOddNumber Interface"), TEXT("Error"), MB_OK);
	}
	pIOddNumberFactory->Release();
	pIOddNumberFactory = NULL;
	int iNum2;
	pIOddNumber->GetNextOddNumber(&iNum2);
	// Release IOddNumber Interface
	pIOddNumber->Release();
	pIOddNumber = NULL;
	return iNum2;
}

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		InitComEngine();
		break;
	case DLL_PROCESS_DETACH:
		UnInitComEngine();
		break;
	}
	return(TRUE);
}
