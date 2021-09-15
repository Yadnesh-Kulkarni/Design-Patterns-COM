class IMultiplication:public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;
};
class IDivision:public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *)=0;
};



// CLSID of MultiplicationDivision : {D4D49BE6-F617-4DBE-8EF0-74FCFB6F50E4}
const CLSID CLSID_MultiplicationDivision= 
{ 0xd4d49be6, 0xf617, 0x4dbe,{ 0x8e, 0xf0, 0x74, 0xfc, 0xfb, 0x6f, 0x50, 0xe4 } };

// IID of IMultiplication Interface : {B9C26601-2BBF-413A-8588-CABD414EA601}
const IID IID_IMultiplication= 
{ 0xb9c26601, 0x2bbf, 0x413a,{ 0x85, 0x88, 0xca, 0xbd, 0x41, 0x4e, 0xa6, 0x1 } };

// IID of IDivision Interface : {CEA929EA-7EF6-4B9C-AB8D-7F455FC97E69}
const IID IID_IDivision = 
{ 0xcea929ea, 0x7ef6, 0x4b9c,{ 0xab, 0x8d, 0x7f, 0x45, 0x5f, 0xc9, 0x7e, 0x69 } };
