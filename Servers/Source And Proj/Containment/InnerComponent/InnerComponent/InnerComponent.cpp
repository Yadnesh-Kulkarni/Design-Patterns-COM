#include<windows.h>
#include"InnerComponent.h"
// class declarations
class CMultiplicationDivision:public IMultiplication,IDivision
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CMultiplicationDivision(void);
	// destructor method declarations
	~CMultiplicationDivision(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *);
	// IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *);
};

class CMultiplicationDivisionClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CMultiplicationDivisionClassFactory(void);
	// destructor method declarations
	~CMultiplicationDivisionClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents=0;
long glNumberOfServerLocks=0;

HMODULE ghModule;
// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{
	
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		ghModule = hDll;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
return(TRUE);
}
// Implementation Of CMultiplicationDivision's Constructor Method
CMultiplicationDivision::CMultiplicationDivision(void)
{

	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of CSumSubtract's Destructor Method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of CMultiplicationDivision's IUnknown's Methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid,void **ppv)
{

	if(riid==IID_IUnknown)
		*ppv=static_cast<IMultiplication *>(this);
	else if(riid==IID_IMultiplication)
		*ppv=static_cast<IMultiplication *>(this);
	else if(riid==IID_IDivision)
		*ppv=static_cast<IDivision *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CMultiplicationDivision::AddRef(void)
{
	
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivision::Release(void)
{
	
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of IMultiplication's Methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1,int num2,int *pMultiplication)
{
	
	*pMultiplication=num1*num2;
	return(S_OK);
}
// Implementation Of IDivision's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1,int num2,int *pDivision)
{
	
	*pDivision=num1/num2;
	return(S_OK);
}
// Implementation Of CMultiplicationDivisionClassFactory's Constructor Method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CMultiplicationDivisionClassFactory's Destructor Method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	
}
// Implementation Of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's Methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	
	if(riid==IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if(riid==IID_IClassFactory)
		*ppv=static_cast<IClassFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of CMultiplicationDivisionClassFactory's IClassFactory's Methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	
	CMultiplicationDivision *pCMultiplicationDivision=NULL;
	HRESULT hr;
	
	if(pUnkOuter!=NULL)
		return(CLASS_E_NOAGGREGATION);

	// create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision=new CMultiplicationDivision;
	if(pCMultiplicationDivision==NULL)
		return(E_OUTOFMEMORY);
	
	hr=pCMultiplicationDivision->QueryInterface(riid,ppv);
	pCMultiplicationDivision->Release();
	return(hr);
}
HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	// code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}
// Implementation Of Exported Functions From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv)
{
	// variable declaraions
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory=NULL;
	HRESULT hr;
	
	if(rclsid!=CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);
	
	pCMultiplicationDivisionClassFactory=new CMultiplicationDivisionClassFactory;
	if(pCMultiplicationDivisionClassFactory==NULL)
		return(E_OUTOFMEMORY);
	hr=pCMultiplicationDivisionClassFactory->QueryInterface(riid,ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	
	if((glNumberOfActiveComponents==0) && (glNumberOfServerLocks==0))
		return(S_OK);
	else
		return(S_FALSE);
}

STDAPI DllRegisterServer()
{
	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("My Containment Inner Component Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{D4D49BE6-F617-4DBE-8EF0-74FCFB6F50E4}"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

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
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{D4D49BE6-F617-4DBE-8EF0-74FCFB6F50E4}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{D4D49BE6-F617-4DBE-8EF0-74FCFB6F50E4}"));

	return S_OK;
}