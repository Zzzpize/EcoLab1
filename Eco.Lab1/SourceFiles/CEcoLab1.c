/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLab1_847FF6CC
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLab1_847FF6CC
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 . All rights reserved.
 * </author>
 *
 */


#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoAdvancedMath interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_QueryInterface(/* in */ IEcoAdvancedMathPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoAdvancedMath) ) {
        *ppv = &pCMe->m_pVTblIEcoAdvancedMath;
        pCMe->m_pVTblIEcoAdvancedMath->AddRef((IEcoAdvancedMath*)pCMe);
    }
	
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoAdvancedMath;
        pCMe->m_pVTblIEcoAdvancedMath->AddRef((IEcoAdvancedMath*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESS;
}

/*
 *
 * <summary>
 *   AddRef Function
 * </summary>
 *
 * <description>
 *   AddRef function for the IEcoAdvancedMath interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_847FF6CC_AddRef(/* in */ IEcoAdvancedMathPtr_t me) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <summary>
 *   Release Function
 * </summary>
 *
 * <description>
 *   Release function for the IEcoAdvancedMath interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_847FF6CC_Release(/* in */ IEcoAdvancedMathPtr_t me) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component's reference count */
    --pCMe->m_cRef;
    /* If the count is zero, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);
		
        return 0;
    }
    return pCMe->m_cRef;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Step(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* out */ double_t* yOut) {
    return ERR_ECO_NOTIMPL;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Stepf(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t, /* in */ float_t h, /* in */ const float_t* y, /* out */ float_t* yOut) {
    return ERR_ECO_NOTIMPL;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Stepl(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t, /* in */ ldouble_t h, /* in */ const ldouble_t* y, /* out */ ldouble_t* yOut) {
    return ERR_ECO_NOTIMPL;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Solve(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ const double_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ double_t* tOut, /* out */ double_t* yOut, /* out */ EcoOdeStats* stats) {
    return ERR_ECO_NOTIMPL;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Solvef(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t0, /* in */ float_t t1, /* in */ const float_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ float_t* tOut, /* out */ float_t* yOut, /* out */ EcoOdeStats* stats) {
    return ERR_ECO_NOTIMPL;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Solvel(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t0, /* in */ ldouble_t t1, /* in */ const ldouble_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ ldouble_t* tOut, /* out */ ldouble_t* yOut, /* out */ EcoOdeStats* stats) {
    return ERR_ECO_NOTIMPL;
}

/*
 *
 * <summary>
 *   Init Function
 * </summary>
 *
 * <description>
 *   Instance initialization function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD initCEcoLab1_847FF6CC(/*in*/ CEcoLab1_847FF6CCPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    IEcoInterfaceBus1* pIBus = 0;

    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0 ) {
        return result;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Getting the component ID for working with memory */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    /* Check */
    if (result != 0 || pCMe->m_pIMem == 0) {
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }



    /* Freeing */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/*
 *
 * <summary>
 *   Create Function
 * </summary>
 *
 * <description>
 *   Instance creation function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD createCEcoLab1_847FF6CC(/* in */ CEcoLab1_847FF6CCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;

    /* Pointer Validation */
    if (pCMe == 0) {
        return result; /* ERR_ECO_POINTER */
    }



    return ERR_ECO_SUCCESS;
}

/*
 *
 * <summary>
 *   Delete Function
 * </summary>
 *
 * <description>
 *   Instance freeing function
 * </description>
 *
 */
static void ECOCALLMETHOD deleteCEcoLab1_847FF6CC(/* in */ CEcoLab1_847FF6CCPtr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoAdvancedMath Virtual Table */
IEcoAdvancedMathVTbl g_x4EF92ACD86564B68821E2E480C0651D9VTbl_847FF6CC = {
    CEcoLab1_847FF6CC_QueryInterface,
    CEcoLab1_847FF6CC_AddRef,
    CEcoLab1_847FF6CC_Release,
    CEcoLab1_847FF6CC_Step,
    CEcoLab1_847FF6CC_Stepf,
    CEcoLab1_847FF6CC_Stepl,
    CEcoLab1_847FF6CC_Solve,
    CEcoLab1_847FF6CC_Solvef,
    CEcoLab1_847FF6CC_Solvel
};



/* Object Instance */
CEcoLab1_847FF6CC g_xCEcoLab1_847FF6CC = {
    &g_x4EF92ACD86564B68821E2E480C0651D9VTbl_847FF6CC,
   
    initCEcoLab1_847FF6CC,
    createCEcoLab1_847FF6CC,
    deleteCEcoLab1_847FF6CC,
    1, /* m_cRef */
    0, /* m_pIMem */
    0  /* m_pISys */
};
