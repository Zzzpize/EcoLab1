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
#include "CEcoLab2EnumConnectionPoints.h"
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
    else if ( IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer) && pCMe->m_pISinkCP != 0 ) {
        *ppv = &pCMe->m_pVTblICPC;
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

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_ICPC_QueryInterface(/* in */ IEcoConnectionPointContainerPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)((char_t*)me - sizeof(voidptr_t));

    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }
    return pCMe->m_pVTblIEcoLab2->QueryInterface((IEcoLab2*)pCMe, riid, ppv);
}

static uint32_t ECOCALLMETHOD CEcoLab2_FF251504_ICPC_AddRef(/* in */ IEcoConnectionPointContainerPtr_t me) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)((char_t*)me - sizeof(voidptr_t));

    if (me == 0 ) {
        return -1;
    }
    return pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
}

static uint32_t ECOCALLMETHOD CEcoLab2_FF251504_ICPC_Release(/* in */ IEcoConnectionPointContainerPtr_t me) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)((char_t*)me - sizeof(voidptr_t));

    if (me == 0 ) {
        return -1;
    }
    return pCMe->m_pVTblIEcoLab2->Release((IEcoLab2*)pCMe);
}

static IEcoConnectionPoint* CEcoLab2_FF251504_InnerConnectionPoint(/* in */ CEcoLab2_FF251504* pCMe) {
    IEcoConnectionPointContainer* pIInnerCPC = 0;
    IEcoConnectionPoint* pICP = 0;

    if (pCMe->m_pInnerUnknown == 0) {
        return 0;
    }
    if (pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, &IID_IEcoConnectionPointContainer, (voidptr_t*)&pIInnerCPC) != 0 || pIInnerCPC == 0) {
        return 0;
    }
    if (pIInnerCPC->pVTbl->FindConnectionPoint(pIInnerCPC, &IID_IEcoLab1Events, &pICP) != 0) {
        pICP = 0;
    }
    pIInnerCPC->pVTbl->Release(pIInnerCPC);
    return pICP;
}

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_ICPC_EnumConnectionPoints(/* in */ IEcoConnectionPointContainerPtr_t me, /* out */ IEcoEnumConnectionPointsPtr_t* ppEnum) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)((char_t*)me - sizeof(voidptr_t));
    IEcoConnectionPoint* points[2];
    uint32_t count = 0;
    int16_t result = 0;

    if (me == 0 || ppEnum == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pISinkCP != 0) {
        points[count++] = (IEcoConnectionPoint*)pCMe->m_pISinkCP;
    }
    points[count] = CEcoLab2_FF251504_InnerConnectionPoint(pCMe);
    if (points[count] != 0) {
        count++;
    }
    result = createCEcoLab2_FF251504EnumConnectionPoints(pCMe->m_pIMem, points, count, 0, ppEnum);
    if (count != 0 && points[count - 1] != (IEcoConnectionPoint*)pCMe->m_pISinkCP) {
        points[count - 1]->pVTbl->Release(points[count - 1]);
    }
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_ICPC_FindConnectionPoint(/* in */ IEcoConnectionPointContainerPtr_t me, /* in */ const UGUID* riid, /* out */ IEcoConnectionPointPtr_t* ppCP) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)((char_t*)me - sizeof(voidptr_t));
    IEcoConnectionPoint* pICP = 0;

    if (me == 0 || riid == 0 || ppCP == 0) {
        return ERR_ECO_POINTER;
    }
    *ppCP = 0;
    if (IsEqualUGUID(riid, &IID_IEcoLab2Events) && pCMe->m_pISinkCP != 0) {
        pICP = (IEcoConnectionPoint*)pCMe->m_pISinkCP;
        pICP->pVTbl->AddRef(pICP);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoLab1Events)) {
        pICP = CEcoLab2_FF251504_InnerConnectionPoint(pCMe);
    }
    if (pICP == 0) {
        return ERR_ECO_NOINTERFACE;
    }
    *ppCP = pICP;
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_IEcoLab2Events_Fire_OnHornerStarted(/* in */ struct CEcoLab2_FF251504* me, /* in */ const int16_t* coeffs, /* in */ uint32_t n, /* in */ int16_t x) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab2Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }
    if (CEcoLab2_FF251504ConnectionPoint_Count(pCMe->m_pISinkCP) != 0) {
        result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
        if ( (result == 0) && (pEnum != 0) ) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab2Events, (voidptr_t*)&pIEvents);
                if ( (result == 0) && (pIEvents != 0) ) {
                    result = pIEvents->pVTbl->OnHornerStarted(pIEvents, coeffs, n, x);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_IEcoLab2Events_Fire_OnHornerStep(/* in */ struct CEcoLab2_FF251504* me, /* in */ uint32_t index, /* in */ int32_t product, /* in */ int16_t coeff, /* in */ int32_t acc) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab2Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }
    if (CEcoLab2_FF251504ConnectionPoint_Count(pCMe->m_pISinkCP) != 0) {
        result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
        if ( (result == 0) && (pEnum != 0) ) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab2Events, (voidptr_t*)&pIEvents);
                if ( (result == 0) && (pIEvents != 0) ) {
                    result = pIEvents->pVTbl->OnHornerStep(pIEvents, index, product, coeff, acc);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_IEcoLab2Events_Fire_OnHornerFinished(/* in */ struct CEcoLab2_FF251504* me, /* in */ int32_t value, /* in */ int16_t status) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab2Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }
    if (CEcoLab2_FF251504ConnectionPoint_Count(pCMe->m_pISinkCP) != 0) {
        result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
        if ( (result == 0) && (pEnum != 0) ) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab2Events, (voidptr_t*)&pIEvents);
                if ( (result == 0) && (pIEvents != 0) ) {
                    result = pIEvents->pVTbl->OnHornerFinished(pIEvents, value, status);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab2_FF251504_Horner(/* in */ IEcoLab2Ptr_t me, /* in */ const int16_t* coeffs, /* in */ uint32_t n, /* in */ int16_t x, /* out */ int32_t* result) {
    CEcoLab2_FF251504* pCMe = (CEcoLab2_FF251504*)me;
    int32_t acc = 0;
    int32_t t = 0;
    uint32_t i = 0;
    int16_t status = ERR_ECO_SUCCESS;

    if (me == 0 || coeffs == 0 || result == 0) {
        return ERR_ECO_POINTER;
    }
    if (n == 0) {
        return ERR_ECO_INVALIDARG;
    }
    if (pCMe->m_pIX == 0 || pCMe->m_pIY == 0) {
        return ERR_ECO_NOINTERFACE;
    }

    pCMe->Fire_OnHornerStarted(pCMe, coeffs, n, x);
    acc = coeffs[0];
    for (i = 1; i < n; i++) {
        if (acc < -32768 || acc > 32767) {
            status = ERR_ECO_FAIL;
            break;
        }
        t = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, (int16_t)acc, x);
        if (t < -32768 || t > 32767) {
            status = ERR_ECO_FAIL;
            break;
        }
        acc = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, (int16_t)t, coeffs[i]);
        pCMe->Fire_OnHornerStep(pCMe, i, t, coeffs[i], acc);
    }
    if (status == ERR_ECO_SUCCESS) {
        *result = acc;
    }
    pCMe->Fire_OnHornerFinished(pCMe, acc, status);
    return status;
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

    pCMe->m_pISinkCP = 0;
    if (pCMe->m_pIMem != 0) {
        if (createCEcoLab2_FF251504ConnectionPoint(pCMe->m_pIMem, pIBus, (IEcoConnectionPointContainer*)&pCMe->m_pVTblICPC, &IID_IEcoLab2Events, &pCMe->m_pISinkCP) != 0) {
            pCMe->m_pISinkCP = 0;
        }
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
        if ( pCMe->m_pISinkCP != 0 ) {
            deleteCEcoLab2_FF251504ConnectionPoint(pCMe->m_pISinkCP);
            pCMe->m_pISinkCP = 0;
        }
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

IEcoConnectionPointContainerVTbl g_x0000000500000000C000000000000046VTblCPC_FF251504 = {
    CEcoLab2_FF251504_ICPC_QueryInterface,
    CEcoLab2_FF251504_ICPC_AddRef,
    CEcoLab2_FF251504_ICPC_Release,
    CEcoLab2_FF251504_ICPC_EnumConnectionPoints,
    CEcoLab2_FF251504_ICPC_FindConnectionPoint
};

/* Object Instance */
CEcoLab2_FF251504 g_xCEcoLab2_FF251504 = {
    &g_xE9A8093E311045CAA1DA8AC1BDA991A4VTbl_FF251504,
    &g_x0000000500000000C000000000000046VTblCPC_FF251504,
    initCEcoLab2_FF251504,
    createCEcoLab2_FF251504,
    deleteCEcoLab2_FF251504,
    CEcoLab2_FF251504_IEcoLab2Events_Fire_OnHornerStarted,
    CEcoLab2_FF251504_IEcoLab2Events_Fire_OnHornerStep,
    CEcoLab2_FF251504_IEcoLab2Events_Fire_OnHornerFinished,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0,
    0,
    0,
    0
};
