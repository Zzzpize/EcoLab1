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

static int16_t CEcoLab1_847FF6CC_Rk4Core(/* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* out */ double_t* yOut, /* in */ double_t* work) {
    double_t* k1 = work;
    double_t* k2 = work + n;
    double_t* k3 = work + 2 * n;
    double_t* k4 = work + 3 * n;
    double_t* tmp = work + 4 * n;
    double_t half = h / (double_t)2;
    int16_t result = 0;
    uint32_t i = 0;

    result = f(ctx, t, y, k1, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + half * k1[i];
    }
    result = f(ctx, t + half, tmp, k2, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + half * k2[i];
    }
    result = f(ctx, t + half, tmp, k3, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * k3[i];
    }
    result = f(ctx, t + h, tmp, k4, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        yOut[i] = y[i] + h / (double_t)6 * (k1[i] + (double_t)2 * k2[i] + (double_t)2 * k3[i] + k4[i]);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Step(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* out */ double_t* yOut) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    double_t* work = 0;
    int16_t result = 0;

    if (me == 0 || f == 0 || y == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (5 * sizeof(double_t))) {
        return ERR_ECO_INVALIDARG;
    }

    work = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(5 * n * sizeof(double_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = CEcoLab1_847FF6CC_Rk4Core(f, ctx, n, t, h, y, yOut, work);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Solve(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ const double_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ double_t* tOut, /* out */ double_t* yOut, /* out */ EcoOdeStats* stats) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    double_t* work = 0;
    double_t span = t1 - t0;
    double_t h = 0;
    double_t t = t0;
    double_t rest = 0;
    uint32_t maxSteps = 0;
    uint32_t steps = 0;
    uint32_t i = 0;
    int16_t done = 0;
    int16_t result = ERR_ECO_SUCCESS;

    if (stats != 0) {
        stats->Points = 0;
        stats->Steps = 0;
        stats->Rejected = 0;
        stats->Evaluations = 0;
    }
    if (me == 0 || f == 0 || y0 == 0 || tOut == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (5 * sizeof(double_t)) || capacity < 2 || span == 0) {
        return ERR_ECO_INVALIDARG;
    }

    if (opt != 0 && opt->Step != 0) {
        h = (double_t)opt->Step;
        if (h < 0) {
            h = -h;
        }
    }
    else {
        h = span / (double_t)(capacity - 1);
        if (h < 0) {
            h = -h;
        }
    }
    if (span < 0) {
        h = -h;
    }
    if (t0 + h == t0) {
        return ERR_ECO_INVALIDARG;
    }
    maxSteps = capacity - 1;
    if (opt != 0 && opt->MaxSteps != 0 && opt->MaxSteps < maxSteps) {
        maxSteps = opt->MaxSteps;
    }

    work = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(5 * n * sizeof(double_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    tOut[0] = t0;
    for (i = 0; i < n; i++) {
        yOut[i] = y0[i];
    }

    while (!done) {
        if (steps >= maxSteps) {
            result = ERR_ECO_INDEX_OUT_OF_BOUNDS;
            break;
        }
        t = t0 + (double_t)steps * h;
        rest = t1 - t;
        if ((h > 0 && rest <= h * (double_t)1.0001) || (h < 0 && rest >= h * (double_t)1.0001)) {
            result = CEcoLab1_847FF6CC_Rk4Core(f, ctx, n, t, rest, yOut + steps * n, yOut + (steps + 1) * n, work);
            tOut[steps + 1] = t1;
            done = 1;
        }
        else {
            result = CEcoLab1_847FF6CC_Rk4Core(f, ctx, n, t, h, yOut + steps * n, yOut + (steps + 1) * n, work);
            tOut[steps + 1] = t0 + (double_t)(steps + 1) * h;
        }
        if (result != 0) {
            break;
        }
        steps++;
        if (stats != 0) {
            stats->Evaluations += 4;
        }
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    if (stats != 0) {
        stats->Steps = steps;
        stats->Points = steps + 1;
    }
    return result;
}

static int16_t CEcoLab1_847FF6CC_Rk4Coref(/* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t, /* in */ float_t h, /* in */ const float_t* y, /* out */ float_t* yOut, /* in */ float_t* work) {
    float_t* k1 = work;
    float_t* k2 = work + n;
    float_t* k3 = work + 2 * n;
    float_t* k4 = work + 3 * n;
    float_t* tmp = work + 4 * n;
    float_t half = h / (float_t)2;
    int16_t result = 0;
    uint32_t i = 0;

    result = f(ctx, t, y, k1, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + half * k1[i];
    }
    result = f(ctx, t + half, tmp, k2, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + half * k2[i];
    }
    result = f(ctx, t + half, tmp, k3, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * k3[i];
    }
    result = f(ctx, t + h, tmp, k4, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        yOut[i] = y[i] + h / (float_t)6 * (k1[i] + (float_t)2 * k2[i] + (float_t)2 * k3[i] + k4[i]);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Stepf(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t, /* in */ float_t h, /* in */ const float_t* y, /* out */ float_t* yOut) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    float_t* work = 0;
    int16_t result = 0;

    if (me == 0 || f == 0 || y == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (5 * sizeof(float_t))) {
        return ERR_ECO_INVALIDARG;
    }

    work = (float_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(5 * n * sizeof(float_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = CEcoLab1_847FF6CC_Rk4Coref(f, ctx, n, t, h, y, yOut, work);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Solvef(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t0, /* in */ float_t t1, /* in */ const float_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ float_t* tOut, /* out */ float_t* yOut, /* out */ EcoOdeStats* stats) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    float_t* work = 0;
    float_t span = t1 - t0;
    float_t h = 0;
    float_t t = t0;
    float_t rest = 0;
    uint32_t maxSteps = 0;
    uint32_t steps = 0;
    uint32_t i = 0;
    int16_t done = 0;
    int16_t result = ERR_ECO_SUCCESS;

    if (stats != 0) {
        stats->Points = 0;
        stats->Steps = 0;
        stats->Rejected = 0;
        stats->Evaluations = 0;
    }
    if (me == 0 || f == 0 || y0 == 0 || tOut == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (5 * sizeof(float_t)) || capacity < 2 || span == 0) {
        return ERR_ECO_INVALIDARG;
    }

    if (opt != 0 && opt->Step != 0) {
        h = (float_t)opt->Step;
        if (h < 0) {
            h = -h;
        }
    }
    else {
        h = span / (float_t)(capacity - 1);
        if (h < 0) {
            h = -h;
        }
    }
    if (span < 0) {
        h = -h;
    }
    if (t0 + h == t0) {
        return ERR_ECO_INVALIDARG;
    }
    maxSteps = capacity - 1;
    if (opt != 0 && opt->MaxSteps != 0 && opt->MaxSteps < maxSteps) {
        maxSteps = opt->MaxSteps;
    }

    work = (float_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(5 * n * sizeof(float_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    tOut[0] = t0;
    for (i = 0; i < n; i++) {
        yOut[i] = y0[i];
    }

    while (!done) {
        if (steps >= maxSteps) {
            result = ERR_ECO_INDEX_OUT_OF_BOUNDS;
            break;
        }
        t = t0 + (float_t)steps * h;
        rest = t1 - t;
        if ((h > 0 && rest <= h * (float_t)1.0001) || (h < 0 && rest >= h * (float_t)1.0001)) {
            result = CEcoLab1_847FF6CC_Rk4Coref(f, ctx, n, t, rest, yOut + steps * n, yOut + (steps + 1) * n, work);
            tOut[steps + 1] = t1;
            done = 1;
        }
        else {
            result = CEcoLab1_847FF6CC_Rk4Coref(f, ctx, n, t, h, yOut + steps * n, yOut + (steps + 1) * n, work);
            tOut[steps + 1] = t0 + (float_t)(steps + 1) * h;
        }
        if (result != 0) {
            break;
        }
        steps++;
        if (stats != 0) {
            stats->Evaluations += 4;
        }
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    if (stats != 0) {
        stats->Steps = steps;
        stats->Points = steps + 1;
    }
    return result;
}

static int16_t CEcoLab1_847FF6CC_Rk4Corel(/* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t, /* in */ ldouble_t h, /* in */ const ldouble_t* y, /* out */ ldouble_t* yOut, /* in */ ldouble_t* work) {
    ldouble_t* k1 = work;
    ldouble_t* k2 = work + n;
    ldouble_t* k3 = work + 2 * n;
    ldouble_t* k4 = work + 3 * n;
    ldouble_t* tmp = work + 4 * n;
    ldouble_t half = h / (ldouble_t)2;
    int16_t result = 0;
    uint32_t i = 0;

    result = f(ctx, t, y, k1, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + half * k1[i];
    }
    result = f(ctx, t + half, tmp, k2, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + half * k2[i];
    }
    result = f(ctx, t + half, tmp, k3, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * k3[i];
    }
    result = f(ctx, t + h, tmp, k4, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        yOut[i] = y[i] + h / (ldouble_t)6 * (k1[i] + (ldouble_t)2 * k2[i] + (ldouble_t)2 * k3[i] + k4[i]);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Stepl(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t, /* in */ ldouble_t h, /* in */ const ldouble_t* y, /* out */ ldouble_t* yOut) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    ldouble_t* work = 0;
    int16_t result = 0;

    if (me == 0 || f == 0 || y == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (5 * sizeof(ldouble_t))) {
        return ERR_ECO_INVALIDARG;
    }

    work = (ldouble_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(5 * n * sizeof(ldouble_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = CEcoLab1_847FF6CC_Rk4Corel(f, ctx, n, t, h, y, yOut, work);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_847FF6CC_Solvel(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t0, /* in */ ldouble_t t1, /* in */ const ldouble_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ ldouble_t* tOut, /* out */ ldouble_t* yOut, /* out */ EcoOdeStats* stats) {
    CEcoLab1_847FF6CC* pCMe = (CEcoLab1_847FF6CC*)me;
    ldouble_t* work = 0;
    ldouble_t span = t1 - t0;
    ldouble_t h = 0;
    ldouble_t t = t0;
    ldouble_t rest = 0;
    uint32_t maxSteps = 0;
    uint32_t steps = 0;
    uint32_t i = 0;
    int16_t done = 0;
    int16_t result = ERR_ECO_SUCCESS;

    if (stats != 0) {
        stats->Points = 0;
        stats->Steps = 0;
        stats->Rejected = 0;
        stats->Evaluations = 0;
    }
    if (me == 0 || f == 0 || y0 == 0 || tOut == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (5 * sizeof(ldouble_t)) || capacity < 2 || span == 0) {
        return ERR_ECO_INVALIDARG;
    }

    if (opt != 0 && opt->Step != 0) {
        h = (ldouble_t)opt->Step;
        if (h < 0) {
            h = -h;
        }
    }
    else {
        h = span / (ldouble_t)(capacity - 1);
        if (h < 0) {
            h = -h;
        }
    }
    if (span < 0) {
        h = -h;
    }
    if (t0 + h == t0) {
        return ERR_ECO_INVALIDARG;
    }
    maxSteps = capacity - 1;
    if (opt != 0 && opt->MaxSteps != 0 && opt->MaxSteps < maxSteps) {
        maxSteps = opt->MaxSteps;
    }

    work = (ldouble_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(5 * n * sizeof(ldouble_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    tOut[0] = t0;
    for (i = 0; i < n; i++) {
        yOut[i] = y0[i];
    }

    while (!done) {
        if (steps >= maxSteps) {
            result = ERR_ECO_INDEX_OUT_OF_BOUNDS;
            break;
        }
        t = t0 + (ldouble_t)steps * h;
        rest = t1 - t;
        if ((h > 0 && rest <= h * (ldouble_t)1.0001) || (h < 0 && rest >= h * (ldouble_t)1.0001)) {
            result = CEcoLab1_847FF6CC_Rk4Corel(f, ctx, n, t, rest, yOut + steps * n, yOut + (steps + 1) * n, work);
            tOut[steps + 1] = t1;
            done = 1;
        }
        else {
            result = CEcoLab1_847FF6CC_Rk4Corel(f, ctx, n, t, h, yOut + steps * n, yOut + (steps + 1) * n, work);
            tOut[steps + 1] = t0 + (ldouble_t)(steps + 1) * h;
        }
        if (result != 0) {
            break;
        }
        steps++;
        if (stats != 0) {
            stats->Evaluations += 4;
        }
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    if (stats != 0) {
        stats->Steps = steps;
        stats->Points = steps + 1;
    }
    return result;
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
