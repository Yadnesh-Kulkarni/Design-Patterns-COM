#include<Windows.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HWND ghWnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance,IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIconSm = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = TEXT("COM Project Final Client");
	wndclass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL,TEXT("Class Could Not Be Loaded"),TEXT("ERROR"),MB_ICONERROR | MB_OK);
		return 0;
	}

	hwnd = CreateWindow(TEXT("COM Project Final Client"),TEXT("Maths Server"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	if (!hwnd)
	{
		MessageBox(NULL, TEXT("Window Could Not Be Loaded"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		return 0;
	}

	ghWnd = hwnd;

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void AddTwoNumbers(int,int,int);
	void SubtractTwoNumbers(int,int,int);
	void MultiplyTwoNumbers(int,int,int);
	void DivideTwoNumbers(int,int,int);
	void Square(int);
	void SquareRoot(int);
	void Cube(int);
	void CubeRoot(int);
	void RegisterDlls();
	void UnRegisterDlls();
	void FirstAndNextOddNumber(int);
	void GetSinOfAngle(float);
	void GetCosOfAngle(float);
	int n1 = 5;
	int n2 = 125;
	int n3 = 0;
	float angle = 45.0f;
	switch (iMsg)
	{
	case WM_CREATE :
		RegisterDlls();
		AddTwoNumbers(n1,n2,n3);
		SubtractTwoNumbers(n1,n2,n3);
		MultiplyTwoNumbers(n1,n2,n3);
		DivideTwoNumbers(n1,n2,n3);
		Square(n2);
		SquareRoot(n2);
		Cube(n1);
		CubeRoot(n2);
		FirstAndNextOddNumber(n1);
		GetSinOfAngle(angle);
		GetCosOfAngle(angle);
		break;
	case WM_DESTROY:
		UnRegisterDlls();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void RegisterDlls()
{
	static HMODULE hLib = NULL;
	typedef void(*pRegisterServers)(void);
	pRegisterServers pfn = NULL;
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\DllRegisterAndUnregister\\DllRegisterAndUnregister.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Register And Unregister Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pRegisterServers)GetProcAddress(hLib, "RegisterServers");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of RegisterServers"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}

	pfn();
	FreeLibrary(hLib);
}

void UnRegisterDlls()
{
	static HMODULE hLib = NULL;
	typedef void(*pRegisterServers)(void);
	pRegisterServers pfn = NULL;
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\DllRegisterAndUnregister\\DllRegisterAndUnregister.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Register And Unregister Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pRegisterServers)GetProcAddress(hLib, "UnRegisterServers");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of UnRegisterServers"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}

	pfn();
	FreeLibrary(hLib);
}

void AddTwoNumbers(int n1, int n2, int n3)
{
	static HMODULE hLib = NULL;
	typedef int (*pAddorSubtractPointer)(int, int);
	pAddorSubtractPointer pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\IClassFactory\\AdditionAndSubtraction.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Add and Subtract Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pAddorSubtractPointer)GetProcAddress(hLib, "GetSumOfTwoIntegers");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of SumOfTwoIntegers"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	
	n3 = pfn(n1, n2);

	wsprintf(str, TEXT("%d + %d = %d"), n1, n2, n3);
	MessageBox(NULL, str, TEXT("Addition"), MB_OK);
	FreeLibrary(hLib);
}

void SubtractTwoNumbers(int n1, int n2, int n3)
{
	static HMODULE hLib = NULL;
	typedef int(*pAddorSubtractPointer)(int, int);
	pAddorSubtractPointer pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\IClassFactory\\AdditionAndSubtraction.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Add and Subtract Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pAddorSubtractPointer)GetProcAddress(hLib, "GetSubstractionOfTwoIntegers");

	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of SumOfTwoIntegers"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	n3 = pfn(n1, n2);
	
	
	wsprintf(str, TEXT("%d - %d = %d"), n1, n2, n3);
	MessageBox(NULL, str, TEXT("Substraction"), MB_OK);
	FreeLibrary(hLib);
}

void MultiplyTwoNumbers(int n1, int n2, int n3)
{
		static HMODULE hLib = NULL;
		typedef int(*pMulDivide)(int, int);
		pMulDivide pfn = NULL;
		TCHAR str[255];
		hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Source\\Containment\\MultiplicationDivision.dll"));
		if (hLib == NULL)
		{
			MessageBox(ghWnd, TEXT("Multiply Divide Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
			DestroyWindow(ghWnd);
		}
		pfn = (pMulDivide)GetProcAddress(hLib, "GetMultiplicationOfTwoIntegers");
		if (pfn == NULL)
		{
			MessageBox(ghWnd, TEXT("Could Not Get Address of MultiplicationOfTwoIntegers"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
			FreeLibrary(hLib);
			DestroyWindow(ghWnd);
		}
		
		n3 = pfn(n1, n2);
		wsprintf(str, TEXT("%d * %d = %d"), n1, n2, n3);
		MessageBox(ghWnd, str, TEXT("Multiplication"), MB_OK);
		FreeLibrary(hLib);
}

void DivideTwoNumbers(int n1, int n2, int n3)
{
	static HMODULE hLib = NULL;
	typedef int(*pMulDivide)(int, int);
	pMulDivide pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Source\\Containment\\MultiplicationDivision.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Multiply Divide Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pMulDivide)GetProcAddress(hLib, "GetDivisionOfTwoIntegers");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetDivisionOfTwoIntegers"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}

	n3 = pfn(n1, n2);
	wsprintf(str, TEXT("%d / %d = %d"), n1, n2, n3);
	MessageBox(ghWnd, str, TEXT("Division"), MB_OK);
	FreeLibrary(hLib);
}

void Square(int n1)
{
	static HMODULE hLib = NULL;
	typedef float(*pSquareSquareRoot)(int);
	pSquareSquareRoot pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Aggregation\\SquareSquareRoot.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Square Square Root Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pSquareSquareRoot)GetProcAddress(hLib, "GetSquareOfInteger");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetSquareOfInteger"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	float fSquare;
	fSquare = pfn(n1);
	swprintf_s(str, TEXT("Square Of %d is %f"), n1, fSquare);
	MessageBox(ghWnd, str, TEXT("Square"), MB_OK);
	FreeLibrary(hLib);
}

void SquareRoot(int n1)
{
	static HMODULE hLib = NULL;
	typedef float(*pSquareSquareRoot)(int);
	pSquareSquareRoot pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Aggregation\\SquareSquareRoot.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Square Square Root Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pSquareSquareRoot)GetProcAddress(hLib, "GetSquareRootOfInteger");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetSquareRootOfInteger"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	float fSquareRoot;
	fSquareRoot = pfn(n1);
	swprintf_s(str, TEXT("Square Root Of %d is %f"), n1, fSquareRoot);
	MessageBox(ghWnd, str, TEXT("SquareRoot"), MB_OK);
	FreeLibrary(hLib);
}

void Cube(int n1)
{
	static HMODULE hLib = NULL;
	typedef float(*pCubeCubeRoot)(int);
	pCubeCubeRoot pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Source\\Automation\\CubeCubeRoot.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Cube Cube Root Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pCubeCubeRoot)GetProcAddress(hLib, "GetCubeOfInteger");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetCubeOfInteger"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	float fCube;
	fCube = pfn(n1);
	swprintf_s(str, TEXT("Cube Of %d is %f"), n1, fCube);
	MessageBox(ghWnd, str, TEXT("Cube"), MB_OK);
	FreeLibrary(hLib);
}

void CubeRoot(int n1)
{
	static HMODULE hLib = NULL;
	typedef float(*pCubeCubeRoot)(int);
	pCubeCubeRoot pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Source\\Automation\\CubeCubeRoot.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Cube Cube Root Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pCubeCubeRoot)GetProcAddress(hLib, "GetCubeRootOfInteger");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetCubeRootOfInteger"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	float fCubeRoot;
	fCubeRoot = pfn(n1);
	swprintf_s(str, TEXT("Cube Root Of %d is %f"), n1, fCubeRoot);
	MessageBox(ghWnd, str, TEXT("Cube Root"), MB_OK);
	FreeLibrary(hLib);
}

void FirstAndNextOddNumber(int iNum1)
{
	static HMODULE hLib = NULL;
	typedef int(*pOddNumber)(int);
	pOddNumber pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\Moniker\\OddNumber.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("OddNumberLibrary Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pOddNumber)GetProcAddress(hLib, "SetFirstAndGetNextOddNumber");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of SetFirstAndGetNextOddNumber"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	int iNext;
	iNext = pfn(iNum1);
	swprintf_s(str, TEXT("Next Odd Number of %d is %d"), iNum1,iNext);
	MessageBox(ghWnd, str, TEXT("Cube Root"), MB_OK);
	FreeLibrary(hLib);
}

void GetSinOfAngle(float angle)
{
	static HMODULE hLib = NULL;
	typedef float(*pTrigo)(float);
	pTrigo pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\ExeServer\\TrigoFunction.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Trigo Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pTrigo)GetProcAddress(hLib, "GetSinOfAngle");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetSinOfAngle"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	float result;
	result = pfn(angle);
	swprintf_s(str, TEXT("Sin of %f is %f"), angle, result);
	MessageBox(ghWnd, str, TEXT("Sin of Angle"), MB_OK);
	FreeLibrary(hLib);
}

void GetCosOfAngle(float angle)
{
	static HMODULE hLib = NULL;
	typedef float(*pTrigo)(float);
	pTrigo pfn = NULL;
	TCHAR str[255];
	hLib = LoadLibrary(TEXT("..\\..\\MiddleWare\\ExeServer\\TrigoFunction.dll"));
	if (hLib == NULL)
	{
		MessageBox(ghWnd, TEXT("Trigo Library Could Not Be Loaded.."), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		DestroyWindow(ghWnd);
	}
	pfn = (pTrigo)GetProcAddress(hLib, "GetCosOfAngle");
	if (pfn == NULL)
	{
		MessageBox(ghWnd, TEXT("Could Not Get Address of GetCosOfAngle"), TEXT("ERROR!!!"), MB_ICONERROR | MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(ghWnd);
	}
	float result;
	result = pfn(angle);
	swprintf_s(str, TEXT("Cos of %f is %f"), angle, result);
	MessageBox(ghWnd, str, TEXT("Cos of Angle"), MB_OK);
	FreeLibrary(hLib);
}
