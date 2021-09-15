#pragma once
class ISum :public IUnknown
{
public :
	//ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *) = 0;
};

class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};


//CLSID CLSID_SumSubtract(String Form) = {45D97394-042C-4C2D-9582-18C32B7C82A3}
const CLSID CLSID_SumSubtract =
{ 0x45d97394, 0x42c, 0x4c2d,{ 0x95, 0x82, 0x18, 0xc3, 0x2b, 0x7c, 0x82, 0xa3 } };

//IID_ISum(String Form) = {C322DFBD-E799-432E-AE5C-22BF38A8AD0E}
const IID IID_ISum =
{ 0xc322dfbd, 0xe799, 0x432e,{ 0xae, 0x5c, 0x22, 0xbf, 0x38, 0xa8, 0xad, 0xe } };

//IID_ISubtract {180D0774-226D-45D5-AB5D-7484E45CBCD6}
const IID IID_ISubtract =
{ 0x180d0774, 0x226d, 0x45d5,{ 0xab, 0x5d, 0x74, 0x84, 0xe4, 0x5c, 0xbc, 0xd6 } };



