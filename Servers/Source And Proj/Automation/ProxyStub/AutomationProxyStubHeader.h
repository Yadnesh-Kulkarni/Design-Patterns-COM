

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0613 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for AutomationServerTypeLib.idl:
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

#ifndef __AutomationProxyStubHeader_h__
#define __AutomationProxyStubHeader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICubeCubeRoot_FWD_DEFINED__
#define __ICubeCubeRoot_FWD_DEFINED__
typedef interface ICubeCubeRoot ICubeCubeRoot;

#endif 	/* __ICubeCubeRoot_FWD_DEFINED__ */


#ifndef __CCubeCubeRoot_FWD_DEFINED__
#define __CCubeCubeRoot_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCubeCubeRoot CCubeCubeRoot;
#else
typedef struct CCubeCubeRoot CCubeCubeRoot;
#endif /* __cplusplus */

#endif 	/* __CCubeCubeRoot_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICubeCubeRoot_INTERFACE_DEFINED__
#define __ICubeCubeRoot_INTERFACE_DEFINED__

/* interface ICubeCubeRoot */
/* [oleautomation][dual][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICubeCubeRoot;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D8E55938-C58C-48F6-8BCA-4CA7380EB4C6")
    ICubeCubeRoot : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CubeOfInteger( 
            /* [in] */ int __MIDL__ICubeCubeRoot0000,
            /* [retval][out] */ float *__MIDL__ICubeCubeRoot0001) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CubeRootOfInteger( 
            /* [in] */ int __MIDL__ICubeCubeRoot0002,
            /* [retval][out] */ float *__MIDL__ICubeCubeRoot0003) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICubeCubeRootVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICubeCubeRoot * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICubeCubeRoot * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICubeCubeRoot * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICubeCubeRoot * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICubeCubeRoot * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICubeCubeRoot * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICubeCubeRoot * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *CubeOfInteger )( 
            ICubeCubeRoot * This,
            /* [in] */ int __MIDL__ICubeCubeRoot0000,
            /* [retval][out] */ float *__MIDL__ICubeCubeRoot0001);
        
        HRESULT ( STDMETHODCALLTYPE *CubeRootOfInteger )( 
            ICubeCubeRoot * This,
            /* [in] */ int __MIDL__ICubeCubeRoot0002,
            /* [retval][out] */ float *__MIDL__ICubeCubeRoot0003);
        
        END_INTERFACE
    } ICubeCubeRootVtbl;

    interface ICubeCubeRoot
    {
        CONST_VTBL struct ICubeCubeRootVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICubeCubeRoot_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICubeCubeRoot_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICubeCubeRoot_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICubeCubeRoot_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICubeCubeRoot_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICubeCubeRoot_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICubeCubeRoot_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICubeCubeRoot_CubeOfInteger(This,__MIDL__ICubeCubeRoot0000,__MIDL__ICubeCubeRoot0001)	\
    ( (This)->lpVtbl -> CubeOfInteger(This,__MIDL__ICubeCubeRoot0000,__MIDL__ICubeCubeRoot0001) ) 

#define ICubeCubeRoot_CubeRootOfInteger(This,__MIDL__ICubeCubeRoot0002,__MIDL__ICubeCubeRoot0003)	\
    ( (This)->lpVtbl -> CubeRootOfInteger(This,__MIDL__ICubeCubeRoot0002,__MIDL__ICubeCubeRoot0003) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICubeCubeRoot_INTERFACE_DEFINED__ */



#ifndef __AutomationServerWithoutRegFileTypeLib_LIBRARY_DEFINED__
#define __AutomationServerWithoutRegFileTypeLib_LIBRARY_DEFINED__

/* library AutomationServerWithoutRegFileTypeLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AutomationServerWithoutRegFileTypeLib;

EXTERN_C const CLSID CLSID_CCubeCubeRoot;

#ifdef __cplusplus

class DECLSPEC_UUID("A50091A9-0016-4DE5-9495-C12AB177BE6B")
CCubeCubeRoot;
#endif
#endif /* __AutomationServerWithoutRegFileTypeLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


