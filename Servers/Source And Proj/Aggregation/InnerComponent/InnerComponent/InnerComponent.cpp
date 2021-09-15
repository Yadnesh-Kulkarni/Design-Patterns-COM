#include<windows.h>
#include"InnerComponent.h"
#include<math.h>
// interface declaration ( for internal use only. i.e. not to be included in .h file )
interface INoAggregationIUnknown // new
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID,void **)=0;
	virtual ULONG __stdcall AddRef_NoAggregation(void)=0;
	virtual ULONG __stdcall Release_NoAggregation(void)=0;
};
// class declarations
class CSquareSquareRoot:public INoAggregationIUnknown,ISquare,ISquareRoot
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownOuter;
public:
	// constructor method declarations
	CSquareSquareRoot(IUnknown *);// new
	// destructor method declarations
	~CSquareSquareRoot(void);
	// Aggregation Supported IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// Aggregation NonSupported IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID,void **);// new
	ULONG __stdcall AddRef_NoAggregation(void);// new
	ULONG __stdcall Release_NoAggregation(void);// new
	// ISquare specific method declarations (inherited)
	HRESULT __stdcall SquareOfInteger(int,float *);
	// ISquareRoot specific method declarations (inherited)
	HRESULT __stdcall SquareRootOfInteger(int,float *);
};
class CSquareSquareRootClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSquareSquareRootClassFactory(void);
	// destructor method declarations
	~CSquareSquareRootClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};
// global variable declarations
long glNumberOfActiveComponents=0;// number of active components
long glNumberOfServerLocks=0;// number of locks on this dll

HMODULE ghModule;
// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{
	// code
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
// Implementation Of CSquareSquareRoot's Constructor Method
CSquareSquareRoot::CSquareSquareRoot(IUnknown *pIUnknownOuter)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
	if(pIUnknownOuter!=NULL)
		m_pIUnknownOuter=pIUnknownOuter;
	else
		m_pIUnknownOuter=reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));
}
// Implementation Of CSumSubtract's Destructor Method
CSquareSquareRoot::~CSquareSquareRoot(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of CSquareSquareRoot's Aggrgation Supporting IUnknown's Methods
HRESULT CSquareSquareRoot::QueryInterface(REFIID riid,void **ppv)
{
	// code
	return(m_pIUnknownOuter->QueryInterface(riid,ppv));
}
ULONG CSquareSquareRoot::AddRef(void)
{
	// code
	return(m_pIUnknownOuter->AddRef());
}
ULONG CSquareSquareRoot::Release(void)
{
	// code
	return(m_pIUnknownOuter->Release());
}
// Implementation Of CSquareSquareRoot's Aggregation NonSupporting IUnknown's Methods
HRESULT CSquareSquareRoot::QueryInterface_NoAggregation(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<INoAggregationIUnknown *>(this);
	else if(riid==IID_ISquare)
		*ppv=static_cast<ISquare *>(this);
	else if(riid==IID_ISquareRoot)
		*ppv=static_cast<ISquareRoot *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSquareSquareRoot::AddRef_NoAggregation(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSquareSquareRoot::Release_NoAggregation(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of ISquare's Methods
HRESULT CSquareSquareRoot::SquareOfInteger(int num1,float *pSquare)
{
	// code
	*pSquare=num1*num1;
	return(S_OK);
}
// Implementation Of ISquareRoot's Methods
HRESULT CSquareSquareRoot::SquareRootOfInteger(int num1,float *pSquareRoot)
{
	// code
	*pSquareRoot = sqrt(num1);
	return(S_OK);
}
// Implementation Of CSquareSquareRootClassFactory's Constructor Method
CSquareSquareRootClassFactory::CSquareSquareRootClassFactory(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CSquareSquareRootClassFactory's Destructor Method
CSquareSquareRootClassFactory::~CSquareSquareRootClassFactory(void)
{
	// code
}
// Implementation Of CSquareSquareRootClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSquareSquareRootClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	// code
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
ULONG CSquareSquareRootClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSquareSquareRootClassFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of CSquareSquareRootClassFactory's IClassFactory's Methods
HRESULT CSquareSquareRootClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	// variable declarations
	CSquareSquareRoot *pCSquareSquareRoot=NULL;
	HRESULT hr;
	// code
	if((pUnkOuter!=NULL) && (riid!=IID_IUnknown))
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CSquareSquareRoot class
	pCSquareSquareRoot=new CSquareSquareRoot(pUnkOuter);
	if(pCSquareSquareRoot==NULL)
		return(E_OUTOFMEMORY);
	// get the requested interface
	hr=pCSquareSquareRoot->QueryInterface_NoAggregation(riid,ppv);
	pCSquareSquareRoot->Release_NoAggregation();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CSquareSquareRootClassFactory::LockServer(BOOL fLock)
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
	CSquareSquareRootClassFactory *pCSquareSquareRootClassFactory=NULL;
	HRESULT hr;
	// code
	if(rclsid!= CLSID_SquareSquareRoot)
		return(CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCSquareSquareRootClassFactory=new CSquareSquareRootClassFactory;
	if(pCSquareSquareRootClassFactory==NULL)
		return(E_OUTOFMEMORY);
	hr=pCSquareSquareRootClassFactory->QueryInterface(riid,ppv);
	pCSquareSquareRootClassFactory->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
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
	TCHAR szClassDescription[] = TEXT("My Aggregation Inner Component Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{FF944330-A554-4560-93CE-543D186D7CF1}"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

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
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{FF944330-A554-4560-93CE-543D186D7CF1}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{FF944330-A554-4560-93CE-543D186D7CF1}"));

	return S_OK;
}
