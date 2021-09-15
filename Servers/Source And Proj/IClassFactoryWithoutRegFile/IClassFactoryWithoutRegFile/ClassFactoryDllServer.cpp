#include<windows.h>
#include"ClassFactoryDll.h"

//Class Declaration
class CSumSubtract :public ISum, ISubtract
{
private :
	long m_cRef;
public :
	//Constructor
	CSumSubtract(void);
	//Destructor
	~CSumSubtract(void);

	//IUnknown Specific Method Declarations
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISUM Methods
	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);

	//ISubtract Methods
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
};

class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//Constructor
	CSumSubtractClassFactory(void);

	//Destructor
	~CSumSubtractClassFactory(void);

	//IUnknown Methods
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClass Factory Specific Method Declaration
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};

//GLOBAL VARIABLES REQUIRED
long glNumberOfActiveComponents = 0; 
long glNumberOfServerLocks = 0;

HMODULE ghModule = NULL;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
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

//Implementation of CSumSubtract
CSumSubtract::CSumSubtract(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//Iunknown

HRESULT CSumSubtract::QueryInterface(REFIID refiid, void **ppv)
{
	if (refiid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (refiid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (refiid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}

	return (m_cRef);
}

//ISum Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *psum)
{
	*psum = num1 + num2;
	return (S_OK);
}

//ISubtract Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *psub)
{
	*psub = num1 - num2;
	return (S_OK);
}

//CSumSubtractIClassFactory
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID refiid, void **ppv)
{
	if (refiid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (refiid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return(m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID refiid, void **ppv)
{
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtract->QueryInterface(refiid,ppv);

	pCSumSubtract->Release();
	
	return(hr);

}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return (S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return (S_OK);
	}
	else
		return (S_FALSE);
}

STDAPI DllRegisterServer()
{
	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("My Simple Class Factory Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT,TEXT("CLSID\\{45D97394-042C-4C2D-9582-18C32B7C82A3}"),0,NULL,REG_OPTION_NON_VOLATILE,KEY_SET_VALUE | KEY_CREATE_SUB_KEY,NULL,&hCLSIDKey,NULL);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegSetValueEx(hCLSIDKey,NULL,0,REG_SZ,(const BYTE*)szClassDescription,sizeof(szClassDescription));

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegCreateKeyEx(hCLSIDKey,TEXT("InProcServer32"),0,NULL,REG_OPTION_NON_VOLATILE,KEY_SET_VALUE,NULL,&hInProcSvrKey,NULL);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		GetModuleFileName(ghModule,szModulePath,MAX_PATH);

		lRet = RegSetValueEx(hInProcSvrKey,NULL,0,REG_SZ,(const BYTE*)szModulePath,sizeof(TCHAR)*(lstrlen(szModulePath)+1));

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
	MessageBox(NULL,TEXT("TEST"),TEXT("TEST"),MB_OK);
	return S_OK;
}

STDAPI DllUnregisterServer()
{
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{45D97394-042C-4C2D-9582-18C32B7C82A3}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{45D97394-042C-4C2D-9582-18C32B7C82A3}"));

	return S_OK;
}