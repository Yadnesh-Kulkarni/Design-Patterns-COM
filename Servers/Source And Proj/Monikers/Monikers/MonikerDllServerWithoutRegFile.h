class IOddNumber:public IUnknown
{
public:
	// IOddNumber specific method declarations
	virtual HRESULT __stdcall GetNextOddNumber(int *)=0;// pure virtual
};
class IOddNumberFactory:public IUnknown
{
public:
	// IOddNumberFactory specific method declarations
	virtual HRESULT __stdcall SetFirstOddNumber(int,IOddNumber **)=0;// pure virtual
};

// CLSID of OddNumber Component {3E0E4846-933C-4820-B9A5-5FC25EDB7106}
const CLSID CLSID_OddNumber= 
{ 0x3e0e4846, 0x933c, 0x4820,{ 0xb9, 0xa5, 0x5f, 0xc2, 0x5e, 0xdb, 0x71, 0x6 } };

// IID of IOddNumber Interface {3EA09C5A-5522-4BF9-A133-64F4B723889B}
const IID IID_IOddNumber= 
{ 0x3ea09c5a, 0x5522, 0x4bf9,{ 0xa1, 0x33, 0x64, 0xf4, 0xb7, 0x23, 0x88, 0x9b } };

// IID of IOddNumberFactory Interface {90D7A9EE-4116-4CE9-A2EF-B204EA838F18}
const IID IID_IOddNumberFactory= { 0x90d7a9ee, 0x4116, 0x4ce9,{ 0xa2, 0xef, 0xb2, 0x4, 0xea, 0x83, 0x8f, 0x18 } };
