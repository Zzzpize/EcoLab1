/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLab2_FF251504
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLab2_FF251504
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
#include "CEcoLab2.h"
#include "IdEcoLab1.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorD.h"
/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoLab2 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab2_FF251504_QueryInterface(/* in */ IEcoLab2Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
	
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if ( (IsEqualUGUID(riid, &IID_IEcoAdvancedMath) || IsEqualUGUID(riid, &IID_IEcoCalculatorX) || IsEqualUGUID(riid, &IID_IEcoCalculatorY)) && pCMe->m_pInnerUnknown != 0 ) {
        return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
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
 *   AddRef function for the IEcoLab2 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab2_FF251504_AddRef(/* in */ IEcoLab2Ptr_t me) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;

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
 *   Release function for the IEcoLab2 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab2_FF251504_Release(/* in */ IEcoLab2Ptr_t me) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;

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

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_Horner(/* in */ IEcoLab2Ptr_t me, /* in */ const int16_t* coeffs, /* in */ uint32_t n, /* in */ int16_t x, /* out */ int32_t* result) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;
    int32_t acc = 0;
    int32_t t = 0;
    uint32_t i = 0;

    if (me == 0 || coeffs == 0 || result == 0) {
        return ERR_ECO_POINTER;
    }
    if (n == 0) {
        return ERR_ECO_INVALIDARG;
    }
    if (pCMe->m_pIX == 0 || pCMe->m_pIY == 0) {
        return ERR_ECO_NOINTERFACE;
    }

    acc = coeffs[0];
    for (i = 1; i < n; i++) {
        if (acc < -32768 || acc > 32767) {
            return ERR_ECO_FAIL;
        }
        t = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, (int16_t)acc, x);
        if (t < -32768 || t > 32767) {
            return ERR_ECO_FAIL;
        }
        acc = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, (int16_t)t, coeffs[i]);
    }
    *result = acc;
    return ERR_ECO_SUCCESS;
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
static int16_t ECOCALLMETHOD initCEcoLab2_FF251504(/*in*/ CEcoLab2_FF251504Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;
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

    pCMe->m_pInnerUnknown = 0;
    if (pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)pCMe, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknown) != 0) {
        pCMe->m_pInnerUnknown = 0;
    }

    pCMe->m_pIX = 0;
    if (pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX) != 0) {
        pCMe->m_pIX = 0;
    }

    pCMe->m_pIY = 0;
    if (pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY) != 0) {
        pCMe->m_pIY = 0;
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
static int16_t ECOCALLMETHOD createCEcoLab2_FF251504(/* in */ CEcoLab2_FF251504Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoLab2_FF251504(/* in */ CEcoLab2_FF251504Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_pIX != 0 ) {
            pCMe->m_pIX->pVTbl->Release(pCMe->m_pIX);
        }
        if ( pCMe->m_pIY != 0 ) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
        if ( pCMe->m_pInnerUnknown != 0 ) {
            pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoLab2 Virtual Table */
IEcoLab2VTbl g_xE9A8093E311045CAA1DA8AC1BDA991A4VTbl_FF251504 = {
    CEcoLab2_FF251504_QueryInterface,
    CEcoLab2_FF251504_AddRef,
    CEcoLab2_FF251504_Release,
    CEcoLab2_FF251504_Horner
};



/* Object Instance */
CEcoLab2_FF251504 g_xCEcoLab2_FF251504 = {
    &g_xE9A8093E311045CAA1DA8AC1BDA991A4VTbl_FF251504,
   
    initCEcoLab2_FF251504,
    createCEcoLab2_FF251504,
    deleteCEcoLab2_FF251504,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0,
    0,
    0
};
