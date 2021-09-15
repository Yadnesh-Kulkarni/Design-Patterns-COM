class ISum :public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;// pure virtual
};

class ISubtract :public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;// pure virtual
};

class ISquare :public IUnknown
{
public:
	// ISquare specific method declarations
	virtual HRESULT __stdcall SquareOfInteger(int, float *) = 0;// pure virtual
};

class ISquareRoot :public IUnknown
{
public:
	// ISquare specific method declarations
	virtual HRESULT __stdcall SquareRootOfInteger(int, float *) = 0;// pure virtual
};

// CLSID of SumSubtract Component {EDF756B7-9EC5-4B0B-9182-0066B3C2DB1D}
const CLSID CLSID_SumSubtract = { 0xedf756b7, 0x9ec5, 0x4b0b,{ 0x91, 0x82, 0x0, 0x66, 0xb3, 0xc2, 0xdb, 0x1d } };

// IID of ISum Interface {6BF3E064-BABD-4028-AB24-7FB53B21F9CF}
const IID IID_ISum =
{ 0x6bf3e064, 0xbabd, 0x4028,{ 0xab, 0x24, 0x7f, 0xb5, 0x3b, 0x21, 0xf9, 0xcf } };

// IID of ISubtract Interface {F439C164-D126-47E9-8E17-F8BA2E502D89}
const IID IID_ISubtract = { 0xf439c164, 0xd126, 0x47e9,{ 0x8e, 0x17, 0xf8, 0xba, 0x2e, 0x50, 0x2d, 0x89 } };

// IID of ISquare Interface {C5179403-6C23-479D-BFF9-49F7ECAC10BD}
const IID IID_ISquare =
{ 0xc5179403, 0x6c23, 0x479d,{ 0xbf, 0xf9, 0x49, 0xf7, 0xec, 0xac, 0x10, 0xbd } };


// IID of ISquareRoot Interface {B0EE4A98-6CC8-4336-9AFE-BD48DE767B3E}
const IID IID_ISquareRoot =
{ 0xb0ee4a98, 0x6cc8, 0x4336,{ 0x9a, 0xfe, 0xbd, 0x48, 0xde, 0x76, 0x7b, 0x3e } };
