class ICubeCubeRoot :public IDispatch
{
public:
	virtual HRESULT __stdcall CubeOfInteger(int, float *) = 0;// pure virtual
	virtual HRESULT __stdcall CubeRootOfInteger(int, float *) = 0;// pure virtual
};

// CLSID of CubeCubeRoot Component : {A50091A9-0016-4DE5-9495-C12AB177BE6B}
const CLSID CLSID_CubeCubeRoot =
{ 0xa50091a9, 0x16, 0x4de5,{ 0x94, 0x95, 0xc1, 0x2a, 0xb1, 0x77, 0xbe, 0x6b } };

// IID of ICubeCubeRoot Interface : {D8E55938-C58C-48F6-8BCA-4CA7380EB4C6}
const IID IID_ICubeCubeRoot = { 0xd8e55938, 0xc58c, 0x48f6,{ 0x8b, 0xca, 0x4c, 0xa7, 0x38, 0xe, 0xb4, 0xc6 } };
