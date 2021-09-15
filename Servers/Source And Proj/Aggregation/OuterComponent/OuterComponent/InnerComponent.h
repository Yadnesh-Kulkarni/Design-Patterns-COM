class ISquare:public IUnknown
{
public:
	// ISquare specific method declarations
	virtual HRESULT __stdcall SquareOfInteger(int,float *)=0;// pure virtual
};
class ISquareRoot:public IUnknown
{
public:
	// ISquare specific method declarations
	virtual HRESULT __stdcall SquareRootOfInteger(int,float *)=0;// pure virtual
};

// CLSID of SquareSquareRoot Component {FF944330-A554-4560-93CE-543D186D7CF1}
const CLSID CLSID_SquareSquareRoot= 
{ 0xff944330, 0xa554, 0x4560,{ 0x93, 0xce, 0x54, 0x3d, 0x18, 0x6d, 0x7c, 0xf1 } };


// IID of ISquare Interface {C5179403-6C23-479D-BFF9-49F7ECAC10BD}
const IID IID_ISquare= 
{ 0xc5179403, 0x6c23, 0x479d,{ 0xbf, 0xf9, 0x49, 0xf7, 0xec, 0xac, 0x10, 0xbd } };


// IID of ISquareRoot Interface {B0EE4A98-6CC8-4336-9AFE-BD48DE767B3E}
const IID IID_ISquareRoot= 
{ 0xb0ee4a98, 0x6cc8, 0x4336,{ 0x9a, 0xfe, 0xbd, 0x48, 0xde, 0x76, 0x7b, 0x3e } };
