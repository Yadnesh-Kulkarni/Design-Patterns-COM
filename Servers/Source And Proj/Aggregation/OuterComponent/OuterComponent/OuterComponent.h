class ISum:public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;// pure virtual
};
class ISubtract:public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;// pure virtual
};

// CLSID of SumSubtract Component {EDF756B7-9EC5-4B0B-9182-0066B3C2DB1D}
const CLSID CLSID_SumSubtract= { 0xedf756b7, 0x9ec5, 0x4b0b,{ 0x91, 0x82, 0x0, 0x66, 0xb3, 0xc2, 0xdb, 0x1d } };

// IID of ISum Interface {6BF3E064-BABD-4028-AB24-7FB53B21F9CF}
const IID IID_ISum= 
{ 0x6bf3e064, 0xbabd, 0x4028,{ 0xab, 0x24, 0x7f, 0xb5, 0x3b, 0x21, 0xf9, 0xcf } };

// IID of ISubtract Interface {F439C164-D126-47E9-8E17-F8BA2E502D89}
const IID IID_ISubtract= { 0xf439c164, 0xd126, 0x47e9,{ 0x8e, 0x17, 0xf8, 0xba, 0x2e, 0x50, 0x2d, 0x89 } };
