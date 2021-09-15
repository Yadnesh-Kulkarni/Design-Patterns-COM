class ISum:public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;
};
class ISubtract:public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;
};


// CLSID of SumSubtract Component {0FBC6494-FCD7-4BC1-A892-FCF45BC8D65B}
const CLSID CLSID_SumSubtract= 
{ 0xfbc6494, 0xfcd7, 0x4bc1,{ 0xa8, 0x92, 0xfc, 0xf4, 0x5b, 0xc8, 0xd6, 0x5b } };

// IID of ISum Interface {9C0AE1A6-9309-4E7E-83F2-447487412DB3}
const IID IID_ISum=
{ 0x9c0ae1a6, 0x9309, 0x4e7e,{ 0x83, 0xf2, 0x44, 0x74, 0x87, 0x41, 0x2d, 0xb3 } };

// IID of ISubtract Interface : {44C6EE2C-32C6-4788-86AB-752C8A1CAE21}
const IID IID_ISubtract= 
{ 0x44c6ee2c, 0x32c6, 0x4788,{ 0x86, 0xab, 0x75, 0x2c, 0x8a, 0x1c, 0xae, 0x21 } };
