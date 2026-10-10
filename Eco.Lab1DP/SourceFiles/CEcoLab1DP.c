/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLab1DP_35D14A4A
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLab1DP_35D14A4A
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
static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_QueryInterface(/* in */ IEcoAdvancedMathPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;

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
static uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_AddRef(/* in */ IEcoAdvancedMathPtr_t me) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;

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
static uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Release(/* in */ IEcoAdvancedMathPtr_t me) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;

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

static double_t CEcoLab1DP_35D14A4A_Root5(/* in */ double_t x) {
    double_t scale = 1;
    double_t r = 1.5;
    double_t r4 = 0;
    int16_t i = 0;

    if (x <= 0) {
        return 0;
    }
    while (x >= 32) {
        x = x / 32;
        scale = scale * 2;
    }
    while (x < 1) {
        x = x * 32;
        scale = scale / 2;
    }
    for (i = 0; i < 8; i++) {
        r4 = r * r * r * r;
        r = (4 * r + x / r4) / 5;
    }
    return r * scale;
}

static int16_t CEcoLab1DP_35D14A4A_DpCore(/* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* in */ double_t* work, /* out */ double_t* yNew, /* out */ double_t* errv) {
    double_t* k1 = work;
    double_t* k2 = work + n;
    double_t* k3 = work + 2 * n;
    double_t* k4 = work + 3 * n;
    double_t* k5 = work + 4 * n;
    double_t* k6 = work + 5 * n;
    double_t* k7 = work + 6 * n;
    double_t* tmp = work + 7 * n;
    int16_t result = 0;
    uint32_t i = 0;

    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] / 5);
    }
    result = f(ctx, t + h / 5, tmp, k2, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 3 / 40 + k2[i] * 9 / 40);
    }
    result = f(ctx, t + h * 3 / 10, tmp, k3, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 44 / 45 - k2[i] * 56 / 15 + k3[i] * 32 / 9);
    }
    result = f(ctx, t + h * 4 / 5, tmp, k4, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 19372 / 6561 - k2[i] * 25360 / 2187 + k3[i] * 64448 / 6561 - k4[i] * 212 / 729);
    }
    result = f(ctx, t + h * 8 / 9, tmp, k5, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 9017 / 3168 - k2[i] * 355 / 33 + k3[i] * 46732 / 5247 + k4[i] * 49 / 176 - k5[i] * 5103 / 18656);
    }
    result = f(ctx, t + h, tmp, k6, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        yNew[i] = y[i] + h * (k1[i] * 35 / 384 + k3[i] * 500 / 1113 + k4[i] * 125 / 192 - k5[i] * 2187 / 6784 + k6[i] * 11 / 84);
    }
    result = f(ctx, t + h, yNew, k7, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        errv[i] = h * (k1[i] * 71 / 57600 - k3[i] * 71 / 16695 + k4[i] * 71 / 1920 - k5[i] * 17253 / 339200 + k6[i] * 22 / 525 - k7[i] / 40);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Step(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* out */ double_t* yOut) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
    double_t* work = 0;
    uint32_t i = 0;
    int16_t result = 0;

    if (me == 0 || f == 0 || y == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (10 * sizeof(double_t))) {
        return ERR_ECO_INVALIDARG;
    }

    work = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(10 * n * sizeof(double_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = f(ctx, t, y, work, n);
    if (result == 0) {
        result = CEcoLab1DP_35D14A4A_DpCore(f, ctx, n, t, h, y, work, work + 8 * n, work + 9 * n);
    }
    if (result == 0) {
        for (i = 0; i < n; i++) {
            yOut[i] = work[8 * n + i];
        }
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Solve(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ const double_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ double_t* tOut, /* out */ double_t* yOut, /* out */ EcoOdeStats* stats) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
    double_t* work = 0;
    double_t* yNew = 0;
    double_t* errv = 0;
    double_t* y = 0;
    double_t span = t1 - t0;
    double_t rtol = (double_t)0.001;
    double_t atol = (double_t)0.000001;
    double_t h = 0;
    double_t t = t0;
    double_t rest = 0;
    double_t err = 0;
    double_t e = 0;
    double_t sc = 0;
    double_t a = 0;
    double_t factor = 0;
    uint32_t maxSteps = 0;
    uint32_t steps = 0;
    uint32_t rejected = 0;
    uint32_t evals = 0;
    uint32_t i = 0;
    int16_t last = 0;
    int16_t wasRejected = 0;
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
    if (n == 0 || n > 0x7FFFFFFF / (10 * sizeof(double_t)) || capacity < 2 || span == 0) {
        return ERR_ECO_INVALIDARG;
    }

    if (opt != 0 && opt->RelTol > 0) {
        rtol = (double_t)opt->RelTol;
    }
    if (opt != 0 && opt->AbsTol > 0) {
        atol = (double_t)opt->AbsTol;
    }
    if (opt != 0 && opt->Step != 0) {
        h = (double_t)opt->Step;
    }
    else {
        h = span / 100;
    }
    if (h < 0) {
        h = -h;
    }
    if (span < 0) {
        h = -h;
    }
    maxSteps = capacity - 1;
    if (opt != 0 && opt->MaxSteps != 0 && opt->MaxSteps < maxSteps) {
        maxSteps = opt->MaxSteps;
    }

    work = (double_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(10 * n * sizeof(double_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    yNew = work + 8 * n;
    errv = work + 9 * n;

    tOut[0] = t0;
    for (i = 0; i < n; i++) {
        yOut[i] = y0[i];
    }
    result = f(ctx, t0, y0, work, n);
    evals++;

    while (result == 0) {
        if (steps >= maxSteps) {
            result = ERR_ECO_INDEX_OUT_OF_BOUNDS;
            break;
        }
        t = tOut[steps];
        y = yOut + steps * n;
        rest = t1 - t;
        last = 0;
        if ((h > 0 && h >= rest) || (h < 0 && h <= rest)) {
            h = rest;
            last = 1;
        }
        if (t + h == t) {
            result = ERR_ECO_FAIL;
            break;
        }

        result = CEcoLab1DP_35D14A4A_DpCore(f, ctx, n, t, h, y, work, yNew, errv);
        evals += 6;
        if (result != 0) {
            break;
        }

        err = 0;
        for (i = 0; i < n; i++) {
            e = errv[i] < 0 ? -errv[i] : errv[i];
            sc = y[i] < 0 ? -y[i] : y[i];
            a = yNew[i] < 0 ? -yNew[i] : yNew[i];
            if (a > sc) {
                sc = a;
            }
            sc = atol + rtol * sc;
            if (e != e) {
                err = e;
                break;
            }
            if (e / sc > err) {
                err = e / sc;
            }
        }

        if (err <= 1) {
            tOut[steps + 1] = last ? t1 : t + h;
            for (i = 0; i < n; i++) {
                yOut[(steps + 1) * n + i] = yNew[i];
                work[i] = work[6 * n + i];
            }
            steps++;
            if (last) {
                break;
            }
            if (err == 0) {
                factor = 5;
            }
            else {
                factor = (double_t)0.9 * CEcoLab1DP_35D14A4A_Root5(1 / err);
                if (factor > 5) {
                    factor = 5;
                }
            }
            if (wasRejected && factor > 1) {
                factor = 1;
            }
            if (factor < (double_t)0.2) {
                factor = (double_t)0.2;
            }
            wasRejected = 0;
        }
        else {
            rejected++;
            factor = (double_t)0.2;
            if (err == err && err < 1e10) {
                factor = (double_t)0.9 * CEcoLab1DP_35D14A4A_Root5(1 / err);
                if (factor < (double_t)0.2) {
                    factor = (double_t)0.2;
                }
            }
            wasRejected = 1;
        }
        h = h * factor;
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    if (stats != 0) {
        stats->Steps = steps;
        stats->Points = steps + 1;
        stats->Rejected = rejected;
        stats->Evaluations = evals;
    }
    return result;
}

static float_t CEcoLab1DP_35D14A4A_Root5f(/* in */ float_t x) {
    float_t scale = 1;
    float_t r = 1.5;
    float_t r4 = 0;
    int16_t i = 0;

    if (x <= 0) {
        return 0;
    }
    while (x >= 32) {
        x = x / 32;
        scale = scale * 2;
    }
    while (x < 1) {
        x = x * 32;
        scale = scale / 2;
    }
    for (i = 0; i < 8; i++) {
        r4 = r * r * r * r;
        r = (4 * r + x / r4) / 5;
    }
    return r * scale;
}

static int16_t CEcoLab1DP_35D14A4A_DpCoref(/* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t, /* in */ float_t h, /* in */ const float_t* y, /* in */ float_t* work, /* out */ float_t* yNew, /* out */ float_t* errv) {
    float_t* k1 = work;
    float_t* k2 = work + n;
    float_t* k3 = work + 2 * n;
    float_t* k4 = work + 3 * n;
    float_t* k5 = work + 4 * n;
    float_t* k6 = work + 5 * n;
    float_t* k7 = work + 6 * n;
    float_t* tmp = work + 7 * n;
    int16_t result = 0;
    uint32_t i = 0;

    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] / 5);
    }
    result = f(ctx, t + h / 5, tmp, k2, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 3 / 40 + k2[i] * 9 / 40);
    }
    result = f(ctx, t + h * 3 / 10, tmp, k3, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 44 / 45 - k2[i] * 56 / 15 + k3[i] * 32 / 9);
    }
    result = f(ctx, t + h * 4 / 5, tmp, k4, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 19372 / 6561 - k2[i] * 25360 / 2187 + k3[i] * 64448 / 6561 - k4[i] * 212 / 729);
    }
    result = f(ctx, t + h * 8 / 9, tmp, k5, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 9017 / 3168 - k2[i] * 355 / 33 + k3[i] * 46732 / 5247 + k4[i] * 49 / 176 - k5[i] * 5103 / 18656);
    }
    result = f(ctx, t + h, tmp, k6, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        yNew[i] = y[i] + h * (k1[i] * 35 / 384 + k3[i] * 500 / 1113 + k4[i] * 125 / 192 - k5[i] * 2187 / 6784 + k6[i] * 11 / 84);
    }
    result = f(ctx, t + h, yNew, k7, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        errv[i] = h * (k1[i] * 71 / 57600 - k3[i] * 71 / 16695 + k4[i] * 71 / 1920 - k5[i] * 17253 / 339200 + k6[i] * 22 / 525 - k7[i] / 40);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Stepf(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t, /* in */ float_t h, /* in */ const float_t* y, /* out */ float_t* yOut) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
    float_t* work = 0;
    uint32_t i = 0;
    int16_t result = 0;

    if (me == 0 || f == 0 || y == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (10 * sizeof(float_t))) {
        return ERR_ECO_INVALIDARG;
    }

    work = (float_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(10 * n * sizeof(float_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = f(ctx, t, y, work, n);
    if (result == 0) {
        result = CEcoLab1DP_35D14A4A_DpCoref(f, ctx, n, t, h, y, work, work + 8 * n, work + 9 * n);
    }
    if (result == 0) {
        for (i = 0; i < n; i++) {
            yOut[i] = work[8 * n + i];
        }
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Solvef(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t0, /* in */ float_t t1, /* in */ const float_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ float_t* tOut, /* out */ float_t* yOut, /* out */ EcoOdeStats* stats) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
    float_t* work = 0;
    float_t* yNew = 0;
    float_t* errv = 0;
    float_t* y = 0;
    float_t span = t1 - t0;
    float_t rtol = (float_t)0.001;
    float_t atol = (float_t)0.000001;
    float_t h = 0;
    float_t t = t0;
    float_t rest = 0;
    float_t err = 0;
    float_t e = 0;
    float_t sc = 0;
    float_t a = 0;
    float_t factor = 0;
    uint32_t maxSteps = 0;
    uint32_t steps = 0;
    uint32_t rejected = 0;
    uint32_t evals = 0;
    uint32_t i = 0;
    int16_t last = 0;
    int16_t wasRejected = 0;
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
    if (n == 0 || n > 0x7FFFFFFF / (10 * sizeof(float_t)) || capacity < 2 || span == 0) {
        return ERR_ECO_INVALIDARG;
    }

    if (opt != 0 && opt->RelTol > 0) {
        rtol = (float_t)opt->RelTol;
    }
    if (opt != 0 && opt->AbsTol > 0) {
        atol = (float_t)opt->AbsTol;
    }
    if (opt != 0 && opt->Step != 0) {
        h = (float_t)opt->Step;
    }
    else {
        h = span / 100;
    }
    if (h < 0) {
        h = -h;
    }
    if (span < 0) {
        h = -h;
    }
    maxSteps = capacity - 1;
    if (opt != 0 && opt->MaxSteps != 0 && opt->MaxSteps < maxSteps) {
        maxSteps = opt->MaxSteps;
    }

    work = (float_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(10 * n * sizeof(float_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    yNew = work + 8 * n;
    errv = work + 9 * n;

    tOut[0] = t0;
    for (i = 0; i < n; i++) {
        yOut[i] = y0[i];
    }
    result = f(ctx, t0, y0, work, n);
    evals++;

    while (result == 0) {
        if (steps >= maxSteps) {
            result = ERR_ECO_INDEX_OUT_OF_BOUNDS;
            break;
        }
        t = tOut[steps];
        y = yOut + steps * n;
        rest = t1 - t;
        last = 0;
        if ((h > 0 && h >= rest) || (h < 0 && h <= rest)) {
            h = rest;
            last = 1;
        }
        if (t + h == t) {
            result = ERR_ECO_FAIL;
            break;
        }

        result = CEcoLab1DP_35D14A4A_DpCoref(f, ctx, n, t, h, y, work, yNew, errv);
        evals += 6;
        if (result != 0) {
            break;
        }

        err = 0;
        for (i = 0; i < n; i++) {
            e = errv[i] < 0 ? -errv[i] : errv[i];
            sc = y[i] < 0 ? -y[i] : y[i];
            a = yNew[i] < 0 ? -yNew[i] : yNew[i];
            if (a > sc) {
                sc = a;
            }
            sc = atol + rtol * sc;
            if (e != e) {
                err = e;
                break;
            }
            if (e / sc > err) {
                err = e / sc;
            }
        }

        if (err <= 1) {
            tOut[steps + 1] = last ? t1 : t + h;
            for (i = 0; i < n; i++) {
                yOut[(steps + 1) * n + i] = yNew[i];
                work[i] = work[6 * n + i];
            }
            steps++;
            if (last) {
                break;
            }
            if (err == 0) {
                factor = 5;
            }
            else {
                factor = (float_t)0.9 * CEcoLab1DP_35D14A4A_Root5f(1 / err);
                if (factor > 5) {
                    factor = 5;
                }
            }
            if (wasRejected && factor > 1) {
                factor = 1;
            }
            if (factor < (float_t)0.2) {
                factor = (float_t)0.2;
            }
            wasRejected = 0;
        }
        else {
            rejected++;
            factor = (float_t)0.2;
            if (err == err && err < 1e10) {
                factor = (float_t)0.9 * CEcoLab1DP_35D14A4A_Root5f(1 / err);
                if (factor < (float_t)0.2) {
                    factor = (float_t)0.2;
                }
            }
            wasRejected = 1;
        }
        h = h * factor;
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    if (stats != 0) {
        stats->Steps = steps;
        stats->Points = steps + 1;
        stats->Rejected = rejected;
        stats->Evaluations = evals;
    }
    return result;
}

static ldouble_t CEcoLab1DP_35D14A4A_Root5l(/* in */ ldouble_t x) {
    ldouble_t scale = 1;
    ldouble_t r = 1.5;
    ldouble_t r4 = 0;
    int16_t i = 0;

    if (x <= 0) {
        return 0;
    }
    while (x >= 32) {
        x = x / 32;
        scale = scale * 2;
    }
    while (x < 1) {
        x = x * 32;
        scale = scale / 2;
    }
    for (i = 0; i < 8; i++) {
        r4 = r * r * r * r;
        r = (4 * r + x / r4) / 5;
    }
    return r * scale;
}

static int16_t CEcoLab1DP_35D14A4A_DpCorel(/* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t, /* in */ ldouble_t h, /* in */ const ldouble_t* y, /* in */ ldouble_t* work, /* out */ ldouble_t* yNew, /* out */ ldouble_t* errv) {
    ldouble_t* k1 = work;
    ldouble_t* k2 = work + n;
    ldouble_t* k3 = work + 2 * n;
    ldouble_t* k4 = work + 3 * n;
    ldouble_t* k5 = work + 4 * n;
    ldouble_t* k6 = work + 5 * n;
    ldouble_t* k7 = work + 6 * n;
    ldouble_t* tmp = work + 7 * n;
    int16_t result = 0;
    uint32_t i = 0;

    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] / 5);
    }
    result = f(ctx, t + h / 5, tmp, k2, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 3 / 40 + k2[i] * 9 / 40);
    }
    result = f(ctx, t + h * 3 / 10, tmp, k3, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 44 / 45 - k2[i] * 56 / 15 + k3[i] * 32 / 9);
    }
    result = f(ctx, t + h * 4 / 5, tmp, k4, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 19372 / 6561 - k2[i] * 25360 / 2187 + k3[i] * 64448 / 6561 - k4[i] * 212 / 729);
    }
    result = f(ctx, t + h * 8 / 9, tmp, k5, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        tmp[i] = y[i] + h * (k1[i] * 9017 / 3168 - k2[i] * 355 / 33 + k3[i] * 46732 / 5247 + k4[i] * 49 / 176 - k5[i] * 5103 / 18656);
    }
    result = f(ctx, t + h, tmp, k6, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        yNew[i] = y[i] + h * (k1[i] * 35 / 384 + k3[i] * 500 / 1113 + k4[i] * 125 / 192 - k5[i] * 2187 / 6784 + k6[i] * 11 / 84);
    }
    result = f(ctx, t + h, yNew, k7, n);
    if (result != 0) {
        return result;
    }
    for (i = 0; i < n; i++) {
        errv[i] = h * (k1[i] * 71 / 57600 - k3[i] * 71 / 16695 + k4[i] * 71 / 1920 - k5[i] * 17253 / 339200 + k6[i] * 22 / 525 - k7[i] / 40);
    }
    return ERR_ECO_SUCCESS;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Stepl(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t, /* in */ ldouble_t h, /* in */ const ldouble_t* y, /* out */ ldouble_t* yOut) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
    ldouble_t* work = 0;
    uint32_t i = 0;
    int16_t result = 0;

    if (me == 0 || f == 0 || y == 0 || yOut == 0) {
        return ERR_ECO_POINTER;
    }
    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }
    if (n == 0 || n > 0x7FFFFFFF / (10 * sizeof(ldouble_t))) {
        return ERR_ECO_INVALIDARG;
    }

    work = (ldouble_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(10 * n * sizeof(ldouble_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    result = f(ctx, t, y, work, n);
    if (result == 0) {
        result = CEcoLab1DP_35D14A4A_DpCorel(f, ctx, n, t, h, y, work, work + 8 * n, work + 9 * n);
    }
    if (result == 0) {
        for (i = 0; i < n; i++) {
            yOut[i] = work[8 * n + i];
        }
    }
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1DP_35D14A4A_Solvel(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t0, /* in */ ldouble_t t1, /* in */ const ldouble_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ ldouble_t* tOut, /* out */ ldouble_t* yOut, /* out */ EcoOdeStats* stats) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
    ldouble_t* work = 0;
    ldouble_t* yNew = 0;
    ldouble_t* errv = 0;
    ldouble_t* y = 0;
    ldouble_t span = t1 - t0;
    ldouble_t rtol = (ldouble_t)0.001;
    ldouble_t atol = (ldouble_t)0.000001;
    ldouble_t h = 0;
    ldouble_t t = t0;
    ldouble_t rest = 0;
    ldouble_t err = 0;
    ldouble_t e = 0;
    ldouble_t sc = 0;
    ldouble_t a = 0;
    ldouble_t factor = 0;
    uint32_t maxSteps = 0;
    uint32_t steps = 0;
    uint32_t rejected = 0;
    uint32_t evals = 0;
    uint32_t i = 0;
    int16_t last = 0;
    int16_t wasRejected = 0;
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
    if (n == 0 || n > 0x7FFFFFFF / (10 * sizeof(ldouble_t)) || capacity < 2 || span == 0) {
        return ERR_ECO_INVALIDARG;
    }

    if (opt != 0 && opt->RelTol > 0) {
        rtol = (ldouble_t)opt->RelTol;
    }
    if (opt != 0 && opt->AbsTol > 0) {
        atol = (ldouble_t)opt->AbsTol;
    }
    if (opt != 0 && opt->Step != 0) {
        h = (ldouble_t)opt->Step;
    }
    else {
        h = span / 100;
    }
    if (h < 0) {
        h = -h;
    }
    if (span < 0) {
        h = -h;
    }
    maxSteps = capacity - 1;
    if (opt != 0 && opt->MaxSteps != 0 && opt->MaxSteps < maxSteps) {
        maxSteps = opt->MaxSteps;
    }

    work = (ldouble_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (uint32_t)(10 * n * sizeof(ldouble_t)));
    if (work == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }
    yNew = work + 8 * n;
    errv = work + 9 * n;

    tOut[0] = t0;
    for (i = 0; i < n; i++) {
        yOut[i] = y0[i];
    }
    result = f(ctx, t0, y0, work, n);
    evals++;

    while (result == 0) {
        if (steps >= maxSteps) {
            result = ERR_ECO_INDEX_OUT_OF_BOUNDS;
            break;
        }
        t = tOut[steps];
        y = yOut + steps * n;
        rest = t1 - t;
        last = 0;
        if ((h > 0 && h >= rest) || (h < 0 && h <= rest)) {
            h = rest;
            last = 1;
        }
        if (t + h == t) {
            result = ERR_ECO_FAIL;
            break;
        }

        result = CEcoLab1DP_35D14A4A_DpCorel(f, ctx, n, t, h, y, work, yNew, errv);
        evals += 6;
        if (result != 0) {
            break;
        }

        err = 0;
        for (i = 0; i < n; i++) {
            e = errv[i] < 0 ? -errv[i] : errv[i];
            sc = y[i] < 0 ? -y[i] : y[i];
            a = yNew[i] < 0 ? -yNew[i] : yNew[i];
            if (a > sc) {
                sc = a;
            }
            sc = atol + rtol * sc;
            if (e != e) {
                err = e;
                break;
            }
            if (e / sc > err) {
                err = e / sc;
            }
        }

        if (err <= 1) {
            tOut[steps + 1] = last ? t1 : t + h;
            for (i = 0; i < n; i++) {
                yOut[(steps + 1) * n + i] = yNew[i];
                work[i] = work[6 * n + i];
            }
            steps++;
            if (last) {
                break;
            }
            if (err == 0) {
                factor = 5;
            }
            else {
                factor = (ldouble_t)0.9 * CEcoLab1DP_35D14A4A_Root5l(1 / err);
                if (factor > 5) {
                    factor = 5;
                }
            }
            if (wasRejected && factor > 1) {
                factor = 1;
            }
            if (factor < (ldouble_t)0.2) {
                factor = (ldouble_t)0.2;
            }
            wasRejected = 0;
        }
        else {
            rejected++;
            factor = (ldouble_t)0.2;
            if (err == err && err < 1e10) {
                factor = (ldouble_t)0.9 * CEcoLab1DP_35D14A4A_Root5l(1 / err);
                if (factor < (ldouble_t)0.2) {
                    factor = (ldouble_t)0.2;
                }
            }
            wasRejected = 1;
        }
        h = h * factor;
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, work);
    if (stats != 0) {
        stats->Steps = steps;
        stats->Points = steps + 1;
        stats->Rejected = rejected;
        stats->Evaluations = evals;
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
static int16_t ECOCALLMETHOD initCEcoLab1DP_35D14A4A(/*in*/ CEcoLab1DP_35D14A4APtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLab1DP_35D14A4A* pCMe = (CEcoLab1DP_35D14A4A*)me;
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
static int16_t ECOCALLMETHOD createCEcoLab1DP_35D14A4A(/* in */ CEcoLab1DP_35D14A4APtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoLab1DP_35D14A4A(/* in */ CEcoLab1DP_35D14A4APtr_t pCMe) {
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
IEcoAdvancedMathVTbl g_x4EF92ACD86564B68821E2E480C0651D9VTbl_35D14A4A = {
    CEcoLab1DP_35D14A4A_QueryInterface,
    CEcoLab1DP_35D14A4A_AddRef,
    CEcoLab1DP_35D14A4A_Release,
    CEcoLab1DP_35D14A4A_Step,
    CEcoLab1DP_35D14A4A_Stepf,
    CEcoLab1DP_35D14A4A_Stepl,
    CEcoLab1DP_35D14A4A_Solve,
    CEcoLab1DP_35D14A4A_Solvef,
    CEcoLab1DP_35D14A4A_Solvel
};



/* Object Instance */
CEcoLab1DP_35D14A4A g_xCEcoLab1DP_35D14A4A = {
    &g_x4EF92ACD86564B68821E2E480C0651D9VTbl_35D14A4A,
   
    initCEcoLab1DP_35D14A4A,
    createCEcoLab1DP_35D14A4A,
    deleteCEcoLab1DP_35D14A4A,
    1, /* m_cRef */
    0, /* m_pIMem */
    0  /* m_pISys */
};
