#include<windows.h>
#include"ExeServerWithoutRegFile.h"
#include<math.h>
// global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
// class declarations
class CTrigo:public ITrigo
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CTrigo(void);
	// destructor method declarations
	~CTrigo(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// ITrigo specific method declarations (inherited)
	HRESULT __stdcall SinOfAngle(float,float *);
	HRESULT __stdcall CosOfAngle(float,float *);
};
class CTrigoClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CTrigoClassFactory(void);
	// destructor method declarations
	~CTrigoClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents=0;
long glNumberOfServerLocks=0;
IClassFactory *gpIClassFactory=NULL;
HMODULE ghModule = NULL;
DWORD dwRegister;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
    HRESULT StartMyClassFactories(void);
    void StopMyClassFactories(void);
	HRESULT RegisterComponent();
	HRESULT UnRegisterComponent();
	MSG msg;
	HRESULT hr;

	TCHAR szTokens[]=TEXT("-/");
	TCHAR *pszTokens;
	TCHAR lpszCmdLine[255];
	wchar_t *next_token = NULL;

	hr=CoInitialize(NULL);
	if(FAILED(hr))
		return(0);
	ghModule = hInstance;
    MultiByteToWideChar(CP_ACP,0,lpCmdLine,255,lpszCmdLine,255);
	pszTokens = wcstok_s(lpszCmdLine, szTokens, &next_token);
	while(pszTokens!=NULL)
	{
		if(_wcsicmp(pszTokens,TEXT("Embedding"))==0)// i.e. COM is calling me
		{
			break;
		}
		if (_wcsicmp(pszTokens, TEXT("register")) == 0)//i.e. Register Component
		{
			RegisterComponent();
			exit(0);
			break;
		}
		if (_wcsicmp(pszTokens, TEXT("unregister")) == 0)//i.e. Register Component
		{
			UnRegisterComponent();
			exit(0);
			break;
		}
		else
		{
			MessageBox(NULL,TEXT("Bad Command Line Arguments.\nExitting The Application."),TEXT("Error"),MB_OK);
			exit(0);
		}
		pszTokens = wcstok_s(NULL, szTokens, &next_token);
	}

    hr=StartMyClassFactories();
	if(FAILED(hr))
	{
	 exit(0);
	}
    
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    StopMyClassFactories();
	CoUninitialize();
	return((int)msg.wParam);

}

// Implementation Of CTrigo's Constructor Method
CTrigo::CTrigo(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of CTrigo's Destructor Method
CTrigo::~CTrigo(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of CTrigo's IUnknown's Methods
HRESULT CTrigo::QueryInterface(REFIID riid,void **ppv)
{
	// code
	if(riid==IID_IUnknown)
		*ppv=static_cast<ITrigo *>(this);
	else if(riid==IID_ITrigo)
		*ppv=static_cast<ITrigo *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CTrigo::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CTrigo::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
			PostQuitMessage(0);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of ITrigo's Methods
HRESULT CTrigo::SinOfAngle(float angle,float *result)
{
	// code
	*result = sinf(angle);
	return(S_OK);
}
// Implementation Of ISubtract's Methods
HRESULT CTrigo::CosOfAngle(float angle,float *result)
{
	*result = cosf(angle);
	return(S_OK);
}
// Implementation Of CTrigoClassFactory's Constructor Method
CTrigoClassFactory::CTrigoClassFactory(void)
{
	// code
	m_cRef=1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CTrigoClassFactory's Destructor Method
CTrigoClassFactory::~CTrigoClassFactory(void)
{
	// code
}
// Implementation Of CTrigoClassFactory's IClassFactory's IUnknown's Methods
HRESULT CTrigoClassFactory::QueryInterface(REFIID riid,void **ppv)
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
ULONG CTrigoClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CTrigoClassFactory::Release(void)
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
// Implementation Of CTrigoClassFactory's IClassFactory's Methods
HRESULT CTrigoClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	// variable declarations
	CTrigo *pCTrigo=NULL;
	HRESULT hr;
	// code
	if(pUnkOuter!=NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CTrigo class
	pCTrigo=new CTrigo;
	if(pCTrigo==NULL)
		return(E_OUTOFMEMORY);
	// get the requested interface
	hr=pCTrigo->QueryInterface(riid,ppv);
	pCTrigo->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CTrigoClassFactory::LockServer(BOOL fLock)
{
	// code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		PostQuitMessage(0);
	return(S_OK);
}
HRESULT StartMyClassFactories(void)
{
	// variable declaraions
	HRESULT hr;
	// code
	gpIClassFactory=new CTrigoClassFactory;
	if(gpIClassFactory==NULL)
		return(E_OUTOFMEMORY);
	gpIClassFactory->AddRef();
	// register the class factory
	hr=CoRegisterClassObject(CLSID_Trigo,
		                     static_cast<IUnknown *>(gpIClassFactory),
							 CLSCTX_LOCAL_SERVER,
							 REGCLS_MULTIPLEUSE,
							 &dwRegister);
	if(FAILED(hr))
	{
		gpIClassFactory->Release();
		return(E_FAIL);
	}
	return(S_OK);
}
void StopMyClassFactories(void)
{
	// variable declaraions
	// code
	// un-register the class factory
	if(dwRegister!=0)
		CoRevokeClassObject(dwRegister);
	if(gpIClassFactory!=NULL)
		gpIClassFactory->Release();
}

HRESULT RegisterComponent()
{
	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("My Simple Exe Server Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{5B045BA3-7D90-419B-B730-2DC9E02213E7}"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*)szClassDescription, sizeof(szClassDescription));

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegCreateKeyEx(hCLSIDKey, TEXT("LocalServer32"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hInProcSvrKey, NULL);

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

HRESULT UnRegisterComponent()
{
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{5B045BA3-7D90-419B-B730-2DC9E02213E7}\\LocalServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{5B045BA3-7D90-419B-B730-2DC9E02213E7}"));

	return S_OK;
}