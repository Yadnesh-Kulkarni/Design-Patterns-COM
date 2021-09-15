#include<windows.h>
#include"InnerComponent.h"
#include"OuterComponent.h"
// class declarations
class CSumSubtract:public ISum,ISubtract
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownInner;
	ISquare *m_pISquare;
	ISquareRoot *m_pISquareRoot;
public:
	// constructor method declarations
	CSumSubtract(void);
	// destructor method declarations
	~CSumSubtract(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
	// custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};
class CSumSubtractClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtractClassFactory(void);
	// destructor method declarations
	~CSumSubtractClassFactory(void);
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
// Implementation Of CSumSubtract's Constructor Method
CSumSubtract::CSumSubtract(void)
{
	// code
	// initialization of private data members
	m_pIUnknownInner=NULL;
	m_pISquare=NULL;
	m_pISquareRoot=NULL;
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of CSumSubtract's Destructor Method
CSumSubtract::~CSumSubtract(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
	if(m_pISquare)
	{
		m_pISquare->Release();
		m_pISquare=NULL;
	}
	if(m_pISquareRoot)
	{
		m_pISquareRoot->Release();
		m_pISquareRoot=NULL;
	}
	if(m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner=NULL;
	}
}
// Implementation Of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISum)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISubtract)
		*ppv=static_cast<ISubtract *>(this);
	else if(riid==IID_ISquare)
		return(m_pIUnknownInner->QueryInterface(riid,ppv));
	else if(riid==IID_ISquareRoot)
		return(m_pIUnknownInner->QueryInterface(riid,ppv));
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtract::Release(void)
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
// Implementation Of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1,int num2,int *pSum)
{
	// code
	*pSum=num1+num2;
	return(S_OK);
}
// Implementation Of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1,int num2,int *pSubtract)
{
	// code
	*pSubtract=num1-num2;
	return(S_OK);
}
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	// variable declarations
	HRESULT hr;
	// code
	hr=CoCreateInstance(CLSID_SquareSquareRoot,
		                reinterpret_cast<IUnknown *>(this),
						CLSCTX_INPROC_SERVER,
		                IID_IUnknown,
						(void **)&m_pIUnknownInner);
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("IUnknown Interface Can Not Be Obtained From Inner Component."),TEXT("Error"),MB_OK);
		return(E_FAIL);
	}
	hr=m_pIUnknownInner->QueryInterface(IID_ISquare,(void **)&m_pISquare);
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("ISquare Interface Can Not Be Obtained From Inner Component."),TEXT("Error"),MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner=NULL;
		return(E_FAIL);
	}
	hr=m_pIUnknownInner->QueryInterface(IID_ISquareRoot,(void **)&m_pISquareRoot);
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("ISquareRoot Interface Can Not Be Obtained From Inner Component."),TEXT("Error"),MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner=NULL;
		return(E_FAIL);
	}
	return(S_OK);
}
// Implementation Of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// code
}
// Implementation Of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid,void **ppv)
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
ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractClassFactory::Release(void)
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
// Implementation Of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	// variable declarations
	CSumSubtract *pCSumSubtract=NULL;
	HRESULT hr;
	// code
	if(pUnkOuter!=NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CSumSubtract class
	pCSumSubtract=new CSumSubtract;
	if(pCSumSubtract==NULL)
		return(E_OUTOFMEMORY);
	// initialize the inner component
	hr=pCSumSubtract->InitializeInnerComponent();
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("Failed To Initialize Inner Component"),TEXT("Error"),MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}
    // get the requested interface
	hr=pCSumSubtract->QueryInterface(riid,ppv);
	pCSumSubtract->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory *pCSumSubtractClassFactory=NULL;
	HRESULT hr;
	// code
	if(rclsid!=CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCSumSubtractClassFactory=new CSumSubtractClassFactory;
	if(pCSumSubtractClassFactory==NULL)
		return(E_OUTOFMEMORY);
	hr=pCSumSubtractClassFactory->QueryInterface(riid,ppv);
	pCSumSubtractClassFactory->Release();// anticipate possible failure of QueryInterface()
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
	TCHAR szClassDescription[] = TEXT("My Aggregation Outer Component Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{EDF756B7-9EC5-4B0B-9182-0066B3C2DB1D}"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

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
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{EDF756B7-9EC5-4B0B-9182-0066B3C2DB1D}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{EDF756B7-9EC5-4B0B-9182-0066B3C2DB1D}"));

	return S_OK;
}