#include<Windows.h>
#include"ExeServerHeader.h"

ITrigo *pITrigo = NULL;
void InitComEngine()
{
	HRESULT hr;
	hr = CoInitialize(NULL);//Single Threaded Environment
}

void UnInitComEngine()
{
	CoUninitialize();
}

float GetSinOfAngle(float angle)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_Trigo, NULL, CLSCTX_LOCAL_SERVER, IID_ITrigo, (void **)&pITrigo);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ITrigo Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
	float result;
	pITrigo->SinOfAngle(angle, &result);
	return result;
}

float GetCosOfAngle(float angle)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_Trigo, NULL, CLSCTX_LOCAL_SERVER, IID_ITrigo, (void **)&pITrigo);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("ITrigo Interface cannot be loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
	}
	float result;
	pITrigo->CosOfAngle(angle, &result);
	return result;
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
