#include<Windows.h>
#include<stdio.h>

void RegisterExe(TCHAR szExePath[255])
{
	STARTUPINFO st;
	PROCESS_INFORMATION pInfo;
	TCHAR szCmdLinep[MAX_PATH];
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	wsprintf(szCmdLinep, TEXT("%sExeServer.exe register"), szExePath);
	CreateProcess(NULL, szCmdLinep, NULL, NULL, FALSE, 0, NULL, NULL, &st, &pInfo);
	WaitForInputIdle(pInfo.hProcess, INFINITE);
}

void UnRegisterExe(TCHAR szExePath[255])
{
	STARTUPINFO st;
	PROCESS_INFORMATION pInfo;
	TCHAR szCmdLinep[MAX_PATH];
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	wsprintf(szCmdLinep, TEXT("%sExeServer.exe unregister"), szExePath);
	CreateProcess(NULL, szCmdLinep, NULL, NULL, FALSE, 0, NULL, NULL, &st, &pInfo);
	WaitForInputIdle(pInfo.hProcess, INFINITE);
}

void RegisterServer(TCHAR szDllPath[255])
{
	TCHAR szPath[MAX_PATH];
	TCHAR szRegSvr[MAX_PATH];
	TCHAR szCmdLinep[MAX_PATH];
	STARTUPINFO st;
	PROCESS_INFORMATION pInfo;
	GetSystemDirectory(szPath, sizeof(szPath));
	wsprintf(szRegSvr, TEXT("%s\\regsvr32.exe"), szPath);
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	wsprintf(szCmdLinep, TEXT("%s /s %s"), szRegSvr,szDllPath);
	CreateProcess(NULL, szCmdLinep, NULL, NULL, FALSE, 0, NULL, NULL, &st, &pInfo);
	WaitForInputIdle(pInfo.hProcess, INFINITE);
}

void UnRegisterServer(TCHAR szDllPath[255])
{
	TCHAR szPath[MAX_PATH];
	TCHAR szRegSvr[MAX_PATH];
	TCHAR szCmdLinep[MAX_PATH];
	STARTUPINFO st;
	PROCESS_INFORMATION pInfo;
	GetSystemDirectory(szPath, sizeof(szPath));
	wsprintf(szRegSvr, TEXT("%s\\regsvr32.exe"), szPath);
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	wsprintf(szCmdLinep, TEXT("%s /s /u %s"), szRegSvr, szDllPath);
	CreateProcess(NULL, szCmdLinep, NULL, NULL, FALSE, 0, NULL, NULL, &st, &pInfo);
	WaitForInputIdle(pInfo.hProcess, INFINITE);
}

void RegisterServers()
{
	RegisterServer(TEXT("..\\..\\Servers\\01-IClassFactory\\IClassFactoryWithoutRegFile.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\02-Containment\\Inner_Component\\InnerComponent.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\02-Containment\\Outer_Component\\OuterComponent.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\03-Aggregation\\InnerComponent\\InnerComponent.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\03-Aggregation\\OuterComponent\\OuterComponent.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\04-Automation\\AutomationServerWithoutRegFile.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\04-Automation\\AutomationServerPrxoyStubDll.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\05-Moniker\\Monikers.dll"));
	RegisterServer(TEXT("..\\..\\Servers\\06-ExeServer\\ProxyStubExe.dll"));
	RegisterExe(TEXT("..\\..\\Servers\\06-ExeServer\\"));
}

void UnRegisterServers()
{
	UnRegisterServer(TEXT("..\\..\\Servers\\01-IClassFactory\\IClassFactoryWithoutRegFile.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\02-Containment\\Inner_Component\\InnerComponent.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\02-Containment\\Outer_Component\\OuterComponent.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\03-Aggregation\\InnerComponent\\InnerComponent.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\03-Aggregation\\OuterComponent\\OuterComponent.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\04-Automation\\AutomationServerWithoutRegFile.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\04-Automation\\AutomationServerPrxoyStubDll.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\05-Moniker\\Monikers.dll"));
	UnRegisterServer(TEXT("..\\..\\Servers\\06-ExeServer\\ProxyStubExe.dll"));
	UnRegisterExe(TEXT("..\\..\\Servers\\06-ExeServer\\"));
}

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}
