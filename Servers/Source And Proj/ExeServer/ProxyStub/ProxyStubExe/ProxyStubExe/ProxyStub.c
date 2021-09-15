

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.00.0613 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for C:\Users\Yadnesh\Documents\Final_COM_Project\Servers\Source And Proj\ExeServer\ProxyStub\ProxyStub.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0613 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "ProxyStubHeader.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   89                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _ProxyStub_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ProxyStub_MIDL_TYPE_FORMAT_STRING;

typedef struct _ProxyStub_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ProxyStub_MIDL_PROC_FORMAT_STRING;

typedef struct _ProxyStub_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ProxyStub_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ProxyStub_MIDL_TYPE_FORMAT_STRING ProxyStub__MIDL_TypeFormatString;
extern const ProxyStub_MIDL_PROC_FORMAT_STRING ProxyStub__MIDL_ProcFormatString;
extern const ProxyStub_MIDL_EXPR_FORMAT_STRING ProxyStub__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITrigoFunction_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITrigoFunction_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const ProxyStub_MIDL_PROC_FORMAT_STRING ProxyStub__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SinOfAngle */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 10 */	NdrFcShort( 0x24 ),	/* 36 */
/* 12 */	NdrFcShort( 0x24 ),	/* 36 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x4 ),	/* 4 */

	/* Parameter __MIDL__ITrigoFunction0000 */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter __MIDL__ITrigoFunction0001 */

/* 32 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 38 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CosOfAngle */

/* 44 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 46 */	NdrFcLong( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 54 */	NdrFcShort( 0x24 ),	/* 36 */
/* 56 */	NdrFcShort( 0x24 ),	/* 36 */
/* 58 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 60 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x4 ),	/* 4 */

	/* Parameter __MIDL__ITrigoFunction0002 */

/* 70 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 72 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 74 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter __MIDL__ITrigoFunction0003 */

/* 76 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 78 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 80 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 82 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 84 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 86 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const ProxyStub_MIDL_TYPE_FORMAT_STRING ProxyStub__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ITrigoFunction, ver. 0.0,
   GUID={0x074A1DAA,0x0BAA,0x454E,{0x9B,0xDE,0xFB,0x3B,0x3A,0xC1,0x23,0xF8}} */

#pragma code_seg(".orpc")
static const unsigned short ITrigoFunction_FormatStringOffsetTable[] =
    {
    0,
    44
    };

static const MIDL_STUBLESS_PROXY_INFO ITrigoFunction_ProxyInfo =
    {
    &Object_StubDesc,
    ProxyStub__MIDL_ProcFormatString.Format,
    &ITrigoFunction_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITrigoFunction_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ProxyStub__MIDL_ProcFormatString.Format,
    &ITrigoFunction_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ITrigoFunctionProxyVtbl = 
{
    &ITrigoFunction_ProxyInfo,
    &IID_ITrigoFunction,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITrigoFunction::SinOfAngle */ ,
    (void *) (INT_PTR) -1 /* ITrigoFunction::CosOfAngle */
};

const CInterfaceStubVtbl _ITrigoFunctionStubVtbl =
{
    &IID_ITrigoFunction,
    &ITrigoFunction_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    ProxyStub__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x8000265, /* MIDL Version 8.0.613 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _ProxyStub_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ITrigoFunctionProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _ProxyStub_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ITrigoFunctionStubVtbl,
    0
};

PCInterfaceName const _ProxyStub_InterfaceNamesList[] = 
{
    "ITrigoFunction",
    0
};


#define _ProxyStub_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ProxyStub, pIID, n)

int __stdcall _ProxyStub_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ProxyStub_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ProxyStub_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ProxyStub_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ProxyStub_StubVtblList,
    (const PCInterfaceName * ) & _ProxyStub_InterfaceNamesList,
    0, /* no delegation */
    & _ProxyStub_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

