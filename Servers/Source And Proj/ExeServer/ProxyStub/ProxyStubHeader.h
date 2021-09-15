

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ProxyStubHeader_h__
#define __ProxyStubHeader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITrigoFunction_FWD_DEFINED__
#define __ITrigoFunction_FWD_DEFINED__
typedef interface ITrigoFunction ITrigoFunction;

#endif 	/* __ITrigoFunction_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITrigoFunction_INTERFACE_DEFINED__
#define __ITrigoFunction_INTERFACE_DEFINED__

/* interface ITrigoFunction */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITrigoFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("074A1DAA-0BAA-454E-9BDE-FB3B3AC123F8")
    ITrigoFunction : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SinOfAngle( 
            /* [in] */ float __MIDL__ITrigoFunction0000,
            /* [out][in] */ float *__MIDL__ITrigoFunction0001) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CosOfAngle( 
            /* [in] */ float __MIDL__ITrigoFunction0002,
            /* [out][in] */ float *__MIDL__ITrigoFunction0003) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITrigoFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrigoFunction * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrigoFunction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrigoFunction * This);
        
        HRESULT ( STDMETHODCALLTYPE *SinOfAngle )( 
            ITrigoFunction * This,
            /* [in] */ float __MIDL__ITrigoFunction0000,
            /* [out][in] */ float *__MIDL__ITrigoFunction0001);
        
        HRESULT ( STDMETHODCALLTYPE *CosOfAngle )( 
            ITrigoFunction * This,
            /* [in] */ float __MIDL__ITrigoFunction0002,
            /* [out][in] */ float *__MIDL__ITrigoFunction0003);
        
        END_INTERFACE
    } ITrigoFunctionVtbl;

    interface ITrigoFunction
    {
        CONST_VTBL struct ITrigoFunctionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrigoFunction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrigoFunction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrigoFunction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrigoFunction_SinOfAngle(This,__MIDL__ITrigoFunction0000,__MIDL__ITrigoFunction0001)	\
    ( (This)->lpVtbl -> SinOfAngle(This,__MIDL__ITrigoFunction0000,__MIDL__ITrigoFunction0001) ) 

#define ITrigoFunction_CosOfAngle(This,__MIDL__ITrigoFunction0002,__MIDL__ITrigoFunction0003)	\
    ( (This)->lpVtbl -> CosOfAngle(This,__MIDL__ITrigoFunction0002,__MIDL__ITrigoFunction0003) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrigoFunction_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


