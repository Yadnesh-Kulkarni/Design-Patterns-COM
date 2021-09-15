// Header Files
#include <windows.h>
#include <stdio.h> // for swprintf_s()
#include <math.h>
#include "AutomationServerWithoutRegFile.h"

// class declarations
// coclass
class CCubeCubeRoot :public ICubeCubeRoot
{
private:
	long m_cRef;
	ITypeInfo *m_pITypeInfo;
public:
	// constructor method declarations
	CCubeCubeRoot(void);
	// destructor method declarations
	~CCubeCubeRoot(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IDispatch specific method declarations (inherited)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);
	
	//IMyMath Specific Methofs
	HRESULT __stdcall CubeOfInteger(int,float *);
	HRESULT __stdcall CubeRootOfInteger(int,float *);

	// custom methods
	HRESULT InitInstance(void);
};

// class factory
class CCubeCubeRootClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CCubeCubeRootClassFactory(void);
	// destructor method declarations
	~CCubeCubeRootClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0;// number of active components
long glNumberOfServerLocks = 0;// number of locks on this dll

HMODULE ghModule;
//{19C61D07-8D87-46A7-98C3-2D6050E6F079}
const GUID LIBID_AutomationServer = { 0x19c61d07, 0x8d87, 0x46a7,{ 0x98, 0xc3, 0x2d, 0x60, 0x50, 0xe6, 0xf0, 0x79 } };

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	// code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		ghModule = hDll;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

// Implementation Of CCubeCubeRoot's Constructor Method
CCubeCubeRoot::CCubeCubeRoot(void)
{
	// code
	m_cRef = 1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}

// Implementation Of CCubeCubeRoot's Destructor Method
CCubeCubeRoot::~CCubeCubeRoot(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}

// Implementation Of CMyMath's IUnknown's Methods
HRESULT CCubeCubeRoot::QueryInterface(REFIID riid, void **ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<ICubeCubeRoot *>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<ICubeCubeRoot *>(this);
	else if (riid == IID_ICubeCubeRoot)
		*ppv = static_cast<ICubeCubeRoot *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CCubeCubeRoot::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CCubeCubeRoot::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation Of ICubeCubeRoot's Methods
HRESULT CCubeCubeRoot::CubeOfInteger(int num1,float *fCube)
{
	// code
	*fCube = num1 * num1 * num1;
	return(S_OK);
}

HRESULT CCubeCubeRoot::CubeRootOfInteger(int num1,float *fCubeRoot)
{
	// code
	*fCubeRoot = cbrt(num1);
	return(S_OK);
}

HRESULT CCubeCubeRoot::InitInstance(void)
{
	// function declarations
	void ComErrorDescriptionString(HWND, HRESULT);
	// variable declarations
	HRESULT hr;
	ITypeLib *pITypeLib = NULL;
	// code
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			 1, 0,// major/minor version numbers
			 0x00,// LANG_NEUTRAL
			 &pITypeLib);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_ICubeCubeRoot, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}

// Implementation Of CMyMathClassFactory's Constructor Method
CCubeCubeRootClassFactory::CCubeCubeRootClassFactory(void)
{
	// code
	m_cRef = 1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}

// Implementation Of CMyMathClassFactory's Destructor Method
CCubeCubeRootClassFactory::~CCubeCubeRootClassFactory(void)
{
	// code
}

// Implementation Of CMyMathClassFactory's IClassFactory's IUnknown's Methods
HRESULT CCubeCubeRootClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CCubeCubeRootClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CCubeCubeRootClassFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

// Implementation Of CMyMathClassFactory's IClassFactory's Methods
HRESULT CCubeCubeRootClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	// variable declarations
	CCubeCubeRoot *pCCubeCubeRoot = NULL;
	HRESULT hr;
	// code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CMyMath class
	pCCubeCubeRoot = new CCubeCubeRoot;
	if (pCCubeCubeRoot == NULL)
		return(E_OUTOFMEMORY);

	// call automation related init method
	pCCubeCubeRoot->InitInstance();

	// get the requested interface
	hr = pCCubeCubeRoot->QueryInterface(riid, ppv);
	pCCubeCubeRoot->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT CCubeCubeRootClassFactory::LockServer(BOOL fLock)
{
	// code
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

// Implementation of IDispatch's methods
HRESULT CCubeCubeRoot::GetTypeInfoCount(UINT *pCountTypeInfo)

{
	// code
	// as we have type library it is 1, else 0
	*pCountTypeInfo = 1;
	return(S_OK);
}

HRESULT CCubeCubeRoot::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo)
{
	// code
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

HRESULT CCubeCubeRoot::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	// code
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CCubeCubeRoot::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	// variable declarations
	HRESULT hr;
	// code
	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);
	return(hr);
}

// Implementation Of Exported Functions From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	// variable declaraions
	CCubeCubeRootClassFactory *pCCubeCubeRootClassFactory = NULL;
	HRESULT hr;
	// code
	if (rclsid != CLSID_CubeCubeRoot)
		return(CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCCubeCubeRootClassFactory = new CCubeCubeRootClassFactory;
	if (pCCubeCubeRootClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCCubeCubeRootClassFactory->QueryInterface(riid, ppv);
	pCCubeCubeRootClassFactory->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// variable declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];
	// code
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr,szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

STDAPI DllRegisterServer()
{
	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("My Automation Server Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{A50091A9-0016-4DE5-9495-C12AB177BE6B}"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*)szClassDescription, sizeof(szClassDescription));

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegCreateKeyEx(hCLSIDKey, TEXT("InProcServer32"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hInProcSvrKey, NULL);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		GetModuleFileName(ghModule, szModulePath, MAX_PATH);

		lRet = RegSetValueEx(hInProcSvrKey, NULL, 0, REG_SZ, (const BYTE*)szModulePath, sizeof(TCHAR)*(lstrlen(szModulePath) + 1));

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);
	}
	__finally
	{
		if (NULL != hCLSIDKey)
			RegCloseKey(hCLSIDKey);
		if (NULL != hInProcSvrKey)
			RegCloseKey(hInProcSvrKey);

	}

	return S_OK;
}

STDAPI DllUnregisterServer()
{
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{A50091A9-0016-4DE5-9495-C12AB177BE6B}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{A50091A9-0016-4DE5-9495-C12AB177BE6B}"));

	return S_OK;
}