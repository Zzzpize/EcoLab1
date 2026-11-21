#include <stdio.h>
#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"

static void CEcoLab1Sink_PrintVector(/* in */ const double_t* y, /* in */ uint32_t n) {
    uint32_t i = 0;

    printf("(");
    for (i = 0; i < n && i < 3; i++) {
        printf(i == 0 ? "%.6f" : ", %.6f", y[i]);
    }
    if (n > 3) {
        printf(", ...");
    }
    printf(")");
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_QueryInterface(/* in */ IEcoLab1EventsPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }
    if ( IsEqualUGUID(riid, &IID_IEcoLab1Events) || IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return ERR_ECO_SUCCESS;
    }
    *ppv = 0;
    return ERR_ECO_NOINTERFACE;
}

static uint32_t ECOCALLMETHOD CEcoLab1Sink_AddRef(/* in */ IEcoLab1EventsPtr_t me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }
    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1Sink_Release(/* in */ IEcoLab1EventsPtr_t me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }
    --pCMe->m_cRef;
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1Sink(me);
        return 0;
    }
    return pCMe->m_cRef;
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_OnSolveStarted(/* in */ IEcoLab1EventsPtr_t me, /* in */ const char_t* method, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ double_t h, /* in */ const double_t* y0) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 || y0 == 0) {
        return ERR_ECO_POINTER;
    }
    pCMe->m_Method = method;
    pCMe->m_cStarted++;
    pCMe->m_cRunSteps = 0;
    pCMe->m_cRunRejected = 0;
    pCMe->m_hMin = 0;
    pCMe->m_hMax = 0;
    pCMe->m_PrevY = y0[0];
    pCMe->m_bEvent = 0;
    if (pCMe->m_bPrint && pCMe->m_Kind == ECOLAB1_SINK_TRACE) {
        printf("[%s] %s: старт, n = %u, отрезок [%g, %g], начальный шаг %g, y0 = ", pCMe->m_Name, method, (unsigned)n, t0, t1, h);
        CEcoLab1Sink_PrintVector(y0, n);
        printf("\n");
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_OnStep(/* in */ IEcoLab1EventsPtr_t me, /* in */ uint32_t index, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* in */ uint32_t n, /* out */ bool_t* isStop) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    double_t ah = h < 0 ? -h : h;
    double_t tPrev = 0;

    if (me == 0 || y == 0 || isStop == 0) {
        return ERR_ECO_POINTER;
    }
    *isStop = 0;
    pCMe->m_cSteps++;
    pCMe->m_cRunSteps++;
    if (pCMe->m_cRunSteps == 1 || ah < pCMe->m_hMin) {
        pCMe->m_hMin = ah;
    }
    if (ah > pCMe->m_hMax) {
        pCMe->m_hMax = ah;
    }

    if (pCMe->m_Kind == ECOLAB1_SINK_TRACE && pCMe->m_bPrint) {
        if (pCMe->m_cEvery <= 1 || index % pCMe->m_cEvery == 0) {
            printf("[%s] %s шаг %u: t = %.6f, h = %.6f, y = ", pCMe->m_Name, pCMe->m_Method, (unsigned)index, t, h);
            CEcoLab1Sink_PrintVector(y, n);
            printf("\n");
        }
    }

    if (pCMe->m_Kind == ECOLAB1_SINK_DETECTOR && !pCMe->m_bEvent) {
        if ((pCMe->m_PrevY > 0 && y[0] <= 0) || (pCMe->m_PrevY < 0 && y[0] >= 0)) {
            tPrev = t - h;
            pCMe->m_tEvent = tPrev + h * pCMe->m_PrevY / (pCMe->m_PrevY - y[0]);
            pCMe->m_bEvent = 1;
            if (pCMe->m_bPrint) {
                printf("[%s] %s шаг %u: y1 сменил знак, t* = %.6f%s\n", pCMe->m_Name, pCMe->m_Method, (unsigned)index, pCMe->m_tEvent, pCMe->m_bStopOnEvent ? ", прошу остановить решение" : "");
            }
            if (pCMe->m_bStopOnEvent) {
                *isStop = 1;
            }
        }
        pCMe->m_PrevY = y[0];
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_OnStepRejected(/* in */ IEcoLab1EventsPtr_t me, /* in */ uint32_t index, /* in */ double_t t, /* in */ double_t h, /* in */ double_t err) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }
    pCMe->m_cRejected++;
    pCMe->m_cRunRejected++;
    if (pCMe->m_Kind == ECOLAB1_SINK_TRACE && pCMe->m_bPrint) {
        printf("[%s] %s шаг %u отклонен: t = %.6f, h = %.6f, ошибка %.3g\n", pCMe->m_Name, pCMe->m_Method, (unsigned)index, t, h, err);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_OnSolveFinished(/* in */ IEcoLab1EventsPtr_t me, /* in */ uint32_t steps, /* in */ uint32_t evaluations, /* in */ int16_t status) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }
    pCMe->m_cFinished++;
    pCMe->m_LastStatus = status;
    if (!pCMe->m_bPrint) {
        return ERR_ECO_SUCCESS;
    }
    if (pCMe->m_Kind == ECOLAB1_SINK_TRACE) {
        printf("[%s] %s: финиш, шагов %u, вызовов правой части %u, код %d\n", pCMe->m_Name, pCMe->m_Method, (unsigned)steps, (unsigned)evaluations, (int)status);
    }
    else if (pCMe->m_Kind == ECOLAB1_SINK_STATS) {
        printf("[%s] %s: принято шагов %u, отклонено %u, шаг от %.6f до %.6f, вызовов правой части %u\n", pCMe->m_Name, pCMe->m_Method, (unsigned)pCMe->m_cRunSteps, (unsigned)pCMe->m_cRunRejected, pCMe->m_hMin, pCMe->m_hMax, (unsigned)evaluations);
    }
    else if (pCMe->m_Kind == ECOLAB1_SINK_DETECTOR && !pCMe->m_bEvent) {
        printf("[%s] %s: смены знака y1 не было\n", pCMe->m_Name, pCMe->m_Method);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_Advise(/* in */ struct CEcoLab1Sink* me, /* in */ IEcoUnknown* pISource) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    IEcoUnknown* pIUnk = 0;
    uint32_t slot = 0;
    int16_t result = 0;

    if (me == 0 || pISource == 0) {
        return ERR_ECO_POINTER;
    }
    for (slot = 0; slot < ECOLAB1_SINK_MAX_SOURCES && me->m_cCookie[slot] != 0; slot++) {
    }
    if (slot == ECOLAB1_SINK_MAX_SOURCES) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = pISource->pVTbl->QueryInterface(pISource, &IID_IEcoUnknown, (voidptr_t*)&pIUnk);
    if (result != 0 || pIUnk == 0) {
        return ERR_ECO_NOINTERFACE;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &IID_IEcoConnectionPointContainer, (voidptr_t*)&pCPC);
    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {
            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*)me, &me->m_cCookie[slot]);
            if (result == 0) {
                me->m_pISource[slot] = pIUnk;
            }
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }
    pIUnk->pVTbl->Release(pIUnk);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1Sink_Unadvise(/* in */ struct CEcoLab1Sink* me, /* in */ IEcoUnknown* pISource) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    IEcoUnknown* pIUnk = 0;
    uint32_t slot = 0;
    int16_t result = 0;

    if (me == 0 || pISource == 0) {
        return ERR_ECO_POINTER;
    }
    result = pISource->pVTbl->QueryInterface(pISource, &IID_IEcoUnknown, (voidptr_t*)&pIUnk);
    if (result != 0 || pIUnk == 0) {
        return ERR_ECO_NOINTERFACE;
    }
    for (slot = 0; slot < ECOLAB1_SINK_MAX_SOURCES; slot++) {
        if (me->m_cCookie[slot] != 0 && me->m_pISource[slot] == pIUnk) {
            break;
        }
    }
    if (slot == ECOLAB1_SINK_MAX_SOURCES) {
        pIUnk->pVTbl->Release(pIUnk);
        return ERR_ECO_VALUE_NOT_FOUND;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &IID_IEcoConnectionPointContainer, (voidptr_t*)&pCPC);
    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {
            result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie[slot]);
            if (result == 0) {
                me->m_cCookie[slot] = 0;
                me->m_pISource[slot] = 0;
            }
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }
    pIUnk->pVTbl->Release(pIUnk);
    return result;
}

IEcoLab1EventsVTbl g_x29EEA0957A26418C9926550CEE125309VTblEvents = {
    CEcoLab1Sink_QueryInterface,
    CEcoLab1Sink_AddRef,
    CEcoLab1Sink_Release,
    CEcoLab1Sink_OnSolveStarted,
    CEcoLab1Sink_OnStep,
    CEcoLab1Sink_OnStepRejected,
    CEcoLab1Sink_OnSolveFinished
};

int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ const char_t* name, /* in */ uint32_t kind, /* out */ IEcoLab1Events** ppIEcoLab1Events) {
    CEcoLab1Sink* pCMe = 0;
    uint32_t i = 0;

    if (pIMem == 0 || ppIEcoLab1Events == 0) {
        return ERR_ECO_POINTER;
    }
    *ppIEcoLab1Events = 0;

    pCMe = (CEcoLab1Sink*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink));
    if (pCMe == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    pIMem->pVTbl->Fill(pIMem, pCMe, 0, sizeof(CEcoLab1Sink));

    pCMe->m_pVTblIEcoLab1Events = &g_x29EEA0957A26418C9926550CEE125309VTblEvents;
    pCMe->Advise = CEcoLab1Sink_Advise;
    pCMe->Unadvise = CEcoLab1Sink_Unadvise;
    pCMe->m_cRef = 1;
    for (i = 0; i < ECOLAB1_SINK_MAX_SOURCES; i++) {
        pCMe->m_cCookie[i] = 0;
        pCMe->m_pISource[i] = 0;
    }
    pIMem->pVTbl->AddRef(pIMem);
    pCMe->m_pIMem = pIMem;
    pCMe->m_Name = name;
    pCMe->m_Kind = kind;
    pCMe->m_bPrint = 1;
    pCMe->m_cEvery = 1;
    pCMe->m_bStopOnEvent = 1;
    pCMe->m_Method = "";
    pCMe->m_LastStatus = -1;

    *ppIEcoLab1Events = (IEcoLab1Events*)pCMe;
    return ERR_ECO_SUCCESS;
}

void ECOCALLMETHOD deleteCEcoLab1Sink(/* in */ IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0) {
        pIMem = pCMe->m_pIMem;
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
