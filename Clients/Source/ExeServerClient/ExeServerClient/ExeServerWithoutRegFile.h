class ITrigo:public IUnknown
{
public:
	// ITrigo specific method declarations
	virtual HRESULT __stdcall SinOfAngle(float,float *)=0;// pure virtual
	virtual HRESULT __stdcall CosOfAngle(float,float *)=0;
};


// CLSID of SumSubtract Component {5B045BA3-7D90-419B-B730-2DC9E02213E7}
const CLSID CLSID_Trigo= { 0x5b045ba3, 0x7d90, 0x419b,{ 0xb7, 0x30, 0x2d, 0xc9, 0xe0, 0x22, 0x13, 0xe7 } };

// IID of ISum Interface {074A1DAA-0BAA-454E-9BDE-FB3B3AC123F8}
const IID IID_ITrigo= { 0x74a1daa, 0xbaa, 0x454e,{ 0x9b, 0xde, 0xfb, 0x3b, 0x3a, 0xc1, 0x23, 0xf8 } };
