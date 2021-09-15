#include<Windows.h>
#include<stdio.h>
#include"Automation.h"

IDispatch *pIDispatch = NULL;
DISPID dispid;
OLECHAR *szFunctionName1 = L"CubeOfInteger";
OLECHAR *szFunctionName2 = L"CubeRootOfInteger";
VARIANT vArg[1], vRet;
DISPPARAMS param = { vArg,0,1,NULL };

void InitComEngine()
{
	HRESULT hr;
	hr = CoInitialize(NULL);//Single Threaded Environment
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library can not be initialized"), TEXT("COM Error"), MB_OK);
		return;
	}
}

void UnInitComEngine()
{
	CoUninitialize();
}

void GetIDispatchInterface()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_CubeCubeRoot,NULL,CLSCTX_INPROC_SERVER,IID_IDispatch,(void **)&pIDispatch);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Component Can Not Be Created"), TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
	}
}

void SafeInterfaceRelease()
{
	if (pIDispatch)
	{
		pIDispatch->Release();
		pIDispatch = NULL;
	}
}

float GetCubeOfInteger(int iNum1)
{
	HRESULT hr;
	TCHAR str[255];
	VariantInit(vArg);
	vArg[0].vt = VT_INT;
	vArg[0].intVal = iNum1;
	param.cArgs = 1;
	param.cNamedArgs = 0;
	param.rgdispidNamedArgs = NULL;
	// return value
	VariantInit(&vRet);

	hr = pIDispatch->GetIDsOfNames(IID_NULL,&szFunctionName1,1,GetUserDefaultLCID(),&dispid);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Can Not Get ID For CubeOfInteger()"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
	}
	hr = pIDispatch->Invoke(dispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,&param,&vRet,NULL,NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Can Not Invoke Function"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
	}
	return vRet.fltVal;
}

float GetCubeRootOfInteger(int iNum1)
{
	HRESULT hr;
	TCHAR str[255];
	VariantInit(vArg);
	vArg[0].vt = VT_INT;
	vArg[0].intVal = iNum1;
	param.cArgs = 1;
	param.cNamedArgs = 0;
	param.rgdispidNamedArgs = NULL;
	// return value
	VariantInit(&vRet);

	hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Can Not Get ID For CubeRootOfInteger()"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
	}
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Can Not Invoke Function"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
	}
	return vRet.fltVal;
}

void CleanUp()
{
	VariantClear(vArg);
	VariantClear(&vRet);
}

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		InitComEngine();
		GetIDispatchInterface();
		break;
	case DLL_PROCESS_DETACH:
		CleanUp();
		SafeInterfaceRelease();
		UnInitComEngine();
		break;
	}
	return(TRUE);
}
