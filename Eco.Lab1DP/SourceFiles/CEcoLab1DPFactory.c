/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLab1DP_35D14A4AFactory
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the factory for the component
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

#include "CEcoLab1DP.h"
#include "CEcoLab1DPFactory.h"

extern CEcoLab1DP_35D14A4A g_xCEcoLab1DP_35D14A4A;

/*
 *
 * <summary>
 *   QueryInterface function
 * </summary>
 *
 * <description>
 *   The function returns a pointer to the interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return ERR_ECO_SUCCESS;
}

/*
 *
 * <summary>
 *   AddRef function
 * </summary>
 *
 * <description>
 *   The function increments the reference count for the interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <summary>
 *   Release function
 * </summary>
 *
 * <description>
 *   The function decrements the reference count for the interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component reference counter */
    --pCMe->m_cRef;

    /* If the counter is zeroed, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <summary>
 *   Init function
 * </summary>
 *
 * <description>
 *   The function initializes the component with parameters
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    /*CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;*/
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    /* Initializing the component with parameters */

    return result;
}

/*
 *
 * <summary>
 *   Alloc function
 * </summary>
 *
 * <description>
 *   The function creates a component
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    /*CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;*/
    IEcoUnknown* pIUnk = 0;
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1DP_35D14A4A* pCObj = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    if (me == 0 || pISystem == 0 ) {
        return result; /* ERR_ECO_POINTER */
    }

    /* Aggregation provided that IID is IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* aggregation not supported */
        return ERR_ECO_NOAGGREGATION;
    }

    /* Getting the application system interface */
    result = pISystem->pVTbl->QueryInterface(pISystem, &GID_IEcoSystem, (void **)&pISys);
    /* Check */
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    /* Getting the interface for working with the interface bus */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Check */
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    /* Getting the component ID for memory operations */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    /* Check */
    if (result != 0 || pIMem == 0) {
        /* Freeing in case of an error */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Allocating memory for instance data */
    pCObj = (CEcoLab1DP_35D14A4A*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1DP_35D14A4A));
    if (pCObj == 0) {
        /* Freeing in case of an error */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Forming instance data */
    pCObj = (CEcoLab1DP_35D14A4A*)pIMem->pVTbl->Copy(pIMem, pCObj, &g_xCEcoLab1DP_35D14A4A, sizeof(CEcoLab1DP_35D14A4A));

    /* Component creation */
    pCObj->Create(pCObj, pISystem, pIUnknownOuter);

    /* Component initialization */
    result = pCObj->Init(pCObj, pISystem);

    /* Getting a pointer to the interface */
    pIUnk = (IEcoUnknown*)pCObj;
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Decrementing the reference requested by the Component Factory */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}
/*
 *
 * <summary>
 *   get_Name function
 * </summary>
 *
 * <description>
 *   The function returns the name of the component
 * </description>
 *
 */
static char_t* ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Name;
}

/*
 *
 * <summary>
 *   get_Version function
 * </summary>
 *
 * <description>
 *   The function returns the version of the component
 * </description>
 *
 */
static char_t* ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Version;
}

/*
 *
 * <summary>
 *   get_Manufacturer function
 * </summary>
 *
 * <description>
 *   The function returns the name of the component manufacturer
 * </description>
 *
 */
static char_t* ECOCALLMETHOD CEcoLab1DP_35D14A4AFactory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab1DP_35D14A4AFactory* pCMe = (CEcoLab1DP_35D14A4AFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_xAFC67744F1C343AC891CA5DA35D14A4AFactoryVTbl = {
    CEcoLab1DP_35D14A4AFactory_QueryInterface,
    CEcoLab1DP_35D14A4AFactory_AddRef,
    CEcoLab1DP_35D14A4AFactory_Release,
    CEcoLab1DP_35D14A4AFactory_Alloc,
    CEcoLab1DP_35D14A4AFactory_Init,
    CEcoLab1DP_35D14A4AFactory_get_Name,
    CEcoLab1DP_35D14A4AFactory_get_Version,
    CEcoLab1DP_35D14A4AFactory_get_Manufacturer
};

/*
 *
 * <summary>
 *   Create function
 * </summary>
 *
 * <description>
 *   The function 
 * </description>
 *
 */
CEcoLab1DP_35D14A4AFactory g_xAFC67744F1C343AC891CA5DA35D14A4AFactory = {
    &g_xAFC67744F1C343AC891CA5DA35D14A4AFactoryVTbl,
    0,
    "EcoLab1DP\0",
    "1.0.0.0\0",
    "\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_xAFC67744F1C343AC891CA5DA35D14A4AFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_AFC67744F1C343AC891CA5DA35D14A4A = (IEcoComponentFactory*)&g_xAFC67744F1C343AC891CA5DA35D14A4AFactory;
#endif
