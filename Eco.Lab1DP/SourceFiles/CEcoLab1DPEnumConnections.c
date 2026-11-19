#include "CEcoLab1DPEnumConnections.h"

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_QueryInterface(/* in */ IEcoEnumConnectionsPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }
    if ( IsEqualUGUID(riid, &IID_IEcoEnumConnections) || IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return ERR_ECO_SUCCESS;
    }
    *ppv = 0;
    return ERR_ECO_NOINTERFACE;
}

static uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_AddRef(/* in */ IEcoEnumConnectionsPtr_t me) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)me;

    if (me == 0 ) {
        return -1;
    }
    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_Release(/* in */ IEcoEnumConnectionsPtr_t me) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)me;
    IEcoMemoryAllocator1* pIMem = 0;
    uint32_t i = 0;

    if (me == 0 ) {
        return -1;
    }
    --pCMe->m_cRef;
    if (pCMe->m_cRef != 0) {
        return pCMe->m_cRef;
    }
    pIMem = pCMe->m_pIMem;
    for (i = 0; i < pCMe->m_cCount; i++) {
        pCMe->m_pData[i].pUnk->pVTbl->Release(pCMe->m_pData[i].pUnk);
    }
    if (pCMe->m_pData != 0) {
        pIMem->pVTbl->Free(pIMem, pCMe->m_pData);
    }
    pIMem->pVTbl->Free(pIMem, pCMe);
    pIMem->pVTbl->Release(pIMem);
    return 0;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_Next(/* in */ IEcoEnumConnectionsPtr_t me, /* in */ uint32_t cConnections, /* out */ struct EcoConnectionData* rgcd, /* out */ uint32_t* pcFetched) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)me;
    uint32_t fetched = 0;

    if (me == 0 || rgcd == 0 || (pcFetched == 0 && cConnections != 1)) {
        return ERR_ECO_POINTER;
    }
    while (fetched < cConnections && pCMe->m_cIndex < pCMe->m_cCount) {
        rgcd[fetched] = pCMe->m_pData[pCMe->m_cIndex];
        rgcd[fetched].pUnk->pVTbl->AddRef(rgcd[fetched].pUnk);
        fetched++;
        pCMe->m_cIndex++;
    }
    if (pcFetched != 0) {
        *pcFetched = fetched;
    }
    return fetched == cConnections ? ERR_ECO_SUCCESS : ERR_ECO_FAIL;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_Skip(/* in */ IEcoEnumConnectionsPtr_t me, /* in */ uint32_t cConnections) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)me;

    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }
    if (cConnections > pCMe->m_cCount - pCMe->m_cIndex) {
        pCMe->m_cIndex = pCMe->m_cCount;
        return ERR_ECO_FAIL;
    }
    pCMe->m_cIndex += cConnections;
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_Reset(/* in */ IEcoEnumConnectionsPtr_t me) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)me;

    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }
    pCMe->m_cIndex = 0;
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4AEnumConnections_Clone(/* in */ IEcoEnumConnectionsPtr_t me, /* out */ IEcoEnumConnectionsPtr_t* ppEnum) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)me;
    int16_t result = 0;

    if (me == 0 || ppEnum == 0) {
        return ERR_ECO_POINTER;
    }
    result = createCEcoLab1DP_35D14A4AEnumConnections(pCMe->m_pIMem, 0, pCMe->m_pData, pCMe->m_cCount, ppEnum);
    if (result == 0) {
        ((CEcoLab1DP_35D14A4AEnumConnections*)*ppEnum)->m_cIndex = pCMe->m_cIndex;
    }
    return result;
}

IEcoEnumConnectionsVTbl g_x0000000200000000C000000000000046VTblEC_35D14A4A = {
    CEcoLab1DP_35D14A4AEnumConnections_QueryInterface,
    CEcoLab1DP_35D14A4AEnumConnections_AddRef,
    CEcoLab1DP_35D14A4AEnumConnections_Release,
    CEcoLab1DP_35D14A4AEnumConnections_Next,
    CEcoLab1DP_35D14A4AEnumConnections_Skip,
    CEcoLab1DP_35D14A4AEnumConnections_Reset,
    CEcoLab1DP_35D14A4AEnumConnections_Clone
};

int16_t ECOCALLMETHOD createCEcoLab1DP_35D14A4AEnumConnections(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoList1* pIList, /* in */ const EcoConnectionData* pData, /* in */ uint32_t count, /* out */ IEcoEnumConnections** ppEnum) {
    CEcoLab1DP_35D14A4AEnumConnections* pCMe = 0;
    EcoConnectionData* pCD = 0;
    uint32_t i = 0;

    if (pIMem == 0 || ppEnum == 0) {
        return ERR_ECO_POINTER;
    }
    *ppEnum = 0;
    if (pIList != 0) {
        count = pIList->pVTbl->Count(pIList);
    }

    pCMe = (CEcoLab1DP_35D14A4AEnumConnections*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1DP_35D14A4AEnumConnections));
    if (pCMe == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    pCMe->m_pData = 0;
    if (count != 0) {
        pCMe->m_pData = (EcoConnectionData*)pIMem->pVTbl->Alloc(pIMem, count * sizeof(EcoConnectionData));
        if (pCMe->m_pData == 0) {
            pIMem->pVTbl->Free(pIMem, pCMe);
            return ERR_ECO_OUTOFMEMORY;
        }
    }
    for (i = 0; i < count; i++) {
        if (pIList != 0) {
            pCD = (EcoConnectionData*)pIList->pVTbl->Item(pIList, i);
            pCMe->m_pData[i] = *pCD;
        }
        else {
            pCMe->m_pData[i] = pData[i];
        }
        pCMe->m_pData[i].pUnk->pVTbl->AddRef(pCMe->m_pData[i].pUnk);
    }

    pCMe->m_pVTblIEC = &g_x0000000200000000C000000000000046VTblEC_35D14A4A;
    pCMe->m_cRef = 1;
    pCMe->m_cCount = count;
    pCMe->m_cIndex = 0;
    pIMem->pVTbl->AddRef(pIMem);
    pCMe->m_pIMem = pIMem;

    *ppEnum = (IEcoEnumConnections*)pCMe;
    return ERR_ECO_SUCCESS;
}
