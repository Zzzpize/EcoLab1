/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   EcoLab1
 * </summary>
 *
 * <description>
 *   This source file is the entry point
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 . All rights reserved.
 * </author>
 *
 */

#include <stdio.h>
#include <math.h>

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

#define BUF_POINTS 1001

typedef struct DecayParams {
    double_t k;
} DecayParams;

static int g_passed = 0;
static int g_failed = 0;
static uint32_t g_calls = 0;

static double_t* g_t = 0;
static double_t* g_y = 0;
static float_t* g_tf = 0;
static float_t* g_yf = 0;
static ldouble_t* g_tl = 0;
static ldouble_t* g_yl = 0;

static void Check(const char* name, int ok) {
    if (ok) {
        g_passed++;
        printf("[OK] %s\n", name);
    }
    else {
        g_failed++;
        printf("[FAIL] %s\n", name);
    }
}

static int16_t ECOCALLMETHOD Decay(voidptr_t ctx, double_t t, const double_t* y, double_t* dydt, uint32_t n) {
    DecayParams* p = (DecayParams*)ctx;
    dydt[0] = -p->k * y[0];
    g_calls++;
    return 0;
}

static int16_t ECOCALLMETHOD Oscillator(voidptr_t ctx, double_t t, const double_t* y, double_t* dydt, uint32_t n) {
    dydt[0] = y[1];
    dydt[1] = -y[0];
    g_calls++;
    return 0;
}

static int16_t ECOCALLMETHOD OscillatorF(voidptr_t ctx, float_t t, const float_t* y, float_t* dydt, uint32_t n) {
    dydt[0] = y[1];
    dydt[1] = -y[0];
    return 0;
}

static int16_t ECOCALLMETHOD OscillatorL(voidptr_t ctx, ldouble_t t, const ldouble_t* y, ldouble_t* dydt, uint32_t n) {
    dydt[0] = y[1];
    dydt[1] = -y[0];
    return 0;
}

static int16_t ECOCALLMETHOD Linear(voidptr_t ctx, double_t t, const double_t* y, double_t* dydt, uint32_t n) {
    dydt[0] = -2.0 * y[0] + y[1];
    dydt[1] = y[0] - 2.0 * y[1];
    return 0;
}

static int16_t ECOCALLMETHOD Broken(voidptr_t ctx, double_t t, const double_t* y, double_t* dydt, uint32_t n) {
    return 42;
}

static void TestDecayOrder(IEcoAdvancedMath* m) {
    DecayParams p;
    EcoOdeStats st;
    double_t y0[1];
    double_t exact = exp(-2.0);
    double_t err = 0;
    double_t prevErr = 0;
    double_t ratio = 0;
    uint32_t steps = 0;
    int16_t r = 0;

    printf("\n1. y' = -2y, y(0) = 1 на [0, 1], точное решение exp(-2t)\n");
    printf("  %6s %12s %20s %20s %12s %8s\n", "N", "h", "RK4 y(1)", "exp(-2)", "|err|", "ratio");
    p.k = 2.0;
    y0[0] = 1.0;
    for (steps = 10; steps <= 640; steps *= 2) {
        r = m->pVTbl->Solve(m, Decay, &p, 1, 0.0, 1.0, y0, 0, steps + 1, g_t, g_y, &st);
        if (r != 0) {
            break;
        }
        err = fabs(g_y[steps] - exact);
        ratio = prevErr > 0 ? prevErr / err : 0;
        printf("  %6u %12.6f %20.15f %20.15f %12.3e %8.2f\n", (unsigned)steps, 1.0 / steps, g_y[steps], exact, err, ratio);
        prevErr = err;
    }
    Check("решение сходится к exp(-2) с точностью 1e-10", r == 0 && err < 1e-10);
    Check("порядок метода 4: при h/2 ошибка падает в ~16 раз", ratio > 15.0 && ratio < 17.0);
}

static void TestOscillator(IEcoAdvancedMath* m) {
    EcoOdeStats st;
    double_t y0[2];
    double_t maxErr = 0;
    double_t maxEnergy = 0;
    double_t err = 0;
    double_t energy = 0;
    uint32_t i = 0;
    int16_t r = 0;

    printf("\n2. Гармонический осциллятор x'' = -x, x(0) = 1, x'(0) = 0 на [0, 10], 1000 шагов\n");
    printf("  %6s %20s %20s %12s\n", "t", "RK4 x(t)", "cos(t)", "|err|");
    y0[0] = 1.0;
    y0[1] = 0.0;
    r = m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 10.0, y0, 0, BUF_POINTS, g_t, g_y, &st);
    for (i = 0; r == 0 && i < st.Points; i++) {
        err = fabs(g_y[2 * i] - cos(g_t[i]));
        if (err > maxErr) {
            maxErr = err;
        }
        err = fabs(g_y[2 * i + 1] + sin(g_t[i]));
        if (err > maxErr) {
            maxErr = err;
        }
        energy = fabs(g_y[2 * i] * g_y[2 * i] + g_y[2 * i + 1] * g_y[2 * i + 1] - 1.0);
        if (energy > maxEnergy) {
            maxEnergy = energy;
        }
        if (i % 100 == 0) {
            printf("  %6.2f %20.15f %20.15f %12.3e\n", g_t[i], g_y[2 * i], cos(g_t[i]), fabs(g_y[2 * i] - cos(g_t[i])));
        }
    }
    printf("макс. ошибка по x и x': %.3e, отклонение энергии: %.3e\n", maxErr, maxEnergy);
    Check("1001 точка, последняя ровно в t = 10", r == 0 && st.Points == BUF_POINTS && g_t[BUF_POINTS - 1] == 10.0);
    Check("x(t) и x'(t) совпадают с cos(t) и -sin(t) до 1e-9", r == 0 && maxErr < 1e-9);
    Check("энергия x^2 + x'^2 сохраняется до 1e-9", r == 0 && maxEnergy < 1e-9);
}

static void TestLinearSystem(IEcoAdvancedMath* m) {
    EcoOdeStats st;
    double_t y0[2];
    double_t e1 = exp(-2.0);
    double_t e3 = exp(-6.0);
    double_t ex1 = 0.5 * e1 + 0.5 * e3;
    double_t ex2 = 0.5 * e1 - 0.5 * e3;
    double_t err = 0;
    int16_t r = 0;

    printf("\n3. Система y1' = -2y1 + y2, y2' = y1 - 2y2, y(0) = (1, 0) на [0, 2], 200 шагов\n");
    y0[0] = 1.0;
    y0[1] = 0.0;
    r = m->pVTbl->Solve(m, Linear, 0, 2, 0.0, 2.0, y0, 0, 201, g_t, g_y, &st);
    err = fabs(g_y[400] - ex1);
    if (fabs(g_y[401] - ex2) > err) {
        err = fabs(g_y[401] - ex2);
    }
    printf("  y1(2) = %.15f, точно %.15f\n", g_y[400], ex1);
    printf("  y2(2) = %.15f, точно %.15f\n", g_y[401], ex2);
    Check("решение системы совпадает с аналитическим до 1e-9", r == 0 && err < 1e-9);
}

static void TestPrecision(IEcoAdvancedMath* m) {
    EcoOdeStats st;
    double_t y0[2];
    float_t y0f[2];
    ldouble_t y0l[2];
    double_t exact = cos(10.0);
    double_t errD = 0;
    double_t errF = 0;
    double_t errL = 0;
    double_t diffLD = 0;
    int16_t rD = 0;
    int16_t rF = 0;
    int16_t rL = 0;

    printf("\n4. Осциллятор на [0, 10], 1000 шагов: float / double / long double\n");
    y0[0] = 1.0;
    y0[1] = 0.0;
    y0f[0] = 1.0f;
    y0f[1] = 0.0f;
    y0l[0] = 1.0L;
    y0l[1] = 0.0L;
    rD = m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 10.0, y0, 0, BUF_POINTS, g_t, g_y, &st);
    rF = m->pVTbl->Solvef(m, OscillatorF, 0, 2, 0.0f, 10.0f, y0f, 0, BUF_POINTS, g_tf, g_yf, &st);
    rL = m->pVTbl->Solvel(m, OscillatorL, 0, 2, 0.0L, 10.0L, y0l, 0, BUF_POINTS, g_tl, g_yl, &st);
    errD = fabs(g_y[2000] - exact);
    errF = fabs((double_t)g_yf[2000] - exact);
    errL = fabs((double_t)g_yl[2000] - exact);
    diffLD = fabs((double_t)(g_yl[2000] - (ldouble_t)g_y[2000]));
    printf("  %12s %24s %12s\n", "type", "x(10)", "|err|");
    printf("  %12s %24.9f %12.3e\n", "float", (double_t)g_yf[2000], errF);
    printf("  %12s %24.15f %12.3e\n", "double", g_y[2000], errD);
    printf("  %12s %24.18Lf %12.3e\n", "long double", g_yl[2000], errL);
    printf("  %12s %24.15f\n", "cos(10)", exact);
    Check("все три версии отработали без ошибок", rD == 0 && rF == 0 && rL == 0);
    Check("float: ошибка меньше 1e-5", errF < 1e-5);
    Check("double: ошибка меньше 1e-9", errD < 1e-9);
    Check("long double совпадает с double до 1e-13", diffLD < 1e-13);
}

static void TestStep(IEcoAdvancedMath* m) {
    double_t y[2];
    double_t yOut[2];
    int16_t r1 = 0;
    int16_t r2 = 0;

    printf("\n5. Один шаг Step, осциллятор, h = 0.1\n");
    y[0] = 1.0;
    y[1] = 0.0;
    r1 = m->pVTbl->Step(m, Oscillator, 0, 2, 0.0, 0.1, y, yOut);
    r2 = m->pVTbl->Step(m, Oscillator, 0, 2, 0.0, 0.1, y, y);
    printf("  x(0.1) = %.15f, cos(0.1) = %.15f, |err| = %.3e\n", yOut[0], cos(0.1), fabs(yOut[0] - cos(0.1)));
    Check("локальная ошибка шага меньше 1e-7", r1 == 0 && fabs(yOut[0] - cos(0.1)) < 1e-7 && fabs(yOut[1] + sin(0.1)) < 1e-7);
    Check("шаг на месте (y и yOut один массив) дает тот же результат", r2 == 0 && y[0] == yOut[0] && y[1] == yOut[1]);
}

static void TestOptionsAndBackward(IEcoAdvancedMath* m) {
    DecayParams p;
    EcoOdeOptions opt;
    EcoOdeStats st;
    double_t y0[2];
    uint32_t calls = 0;
    uint32_t i = 0;
    int16_t r = 0;

    printf("\n6. Параметры шага, интегрирование назад, статистика\n");
    y0[0] = 1.0;
    y0[1] = 0.0;
    opt.Step = 0.3;
    opt.RelTol = 0;
    opt.AbsTol = 0;
    opt.MaxSteps = 0;
    r = m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 1.0, y0, &opt, BUF_POINTS, g_t, g_y, &st);
    printf("  шаг 0.3 на [0, 1]: t =");
    for (i = 0; r == 0 && i < st.Points; i++) {
        printf(" %.2f", g_t[i]);
    }
    printf("\n");
    Check("при шаге 0.3 последний шаг укорачивается до t = 1", r == 0 && st.Points == 5 && g_t[4] == 1.0 && fabs(g_t[3] - 0.9) < 1e-15);

    p.k = 1.0;
    y0[0] = exp(-1.0);
    r = m->pVTbl->Solve(m, Decay, &p, 1, 1.0, 0.0, y0, 0, 101, g_t, g_y, &st);
    printf("  назад от t = 1 до t = 0: y(0) = %.15f\n", g_y[100]);
    Check("интегрирование назад по времени возвращает y(0) = 1", r == 0 && g_t[100] == 0.0 && fabs(g_y[100] - 1.0) < 1e-9);

    g_calls = 0;
    r = m->pVTbl->Solve(m, Decay, &p, 1, 0.0, 1.0, y0, 0, 51, g_t, g_y, &st);
    calls = g_calls;
    printf("  50 шагов: Points = %u, Steps = %u, Evaluations = %u, реальных вызовов = %u\n", (unsigned)st.Points, (unsigned)st.Steps, (unsigned)st.Evaluations, (unsigned)calls);
    Check("статистика: 4 вызова правой части на шаг", r == 0 && st.Steps == 50 && st.Points == 51 && st.Evaluations == 200 && calls == 200);
}

static void TestErrors(IEcoAdvancedMath* m) {
    EcoOdeOptions opt;
    EcoOdeStats st;
    double_t y0[2];

    printf("\n7. Обработка ошибок\n");
    y0[0] = 1.0;
    y0[1] = 0.0;
    opt.Step = 0.1;
    opt.RelTol = 0;
    opt.AbsTol = 0;
    opt.MaxSteps = 0;
    Check("f = NULL -> ERR_ECO_POINTER", m->pVTbl->Solve(m, 0, 0, 2, 0.0, 1.0, y0, 0, 11, g_t, g_y, &st) == ERR_ECO_POINTER);
    Check("y0 = NULL -> ERR_ECO_POINTER", m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 1.0, 0, 0, 11, g_t, g_y, &st) == ERR_ECO_POINTER);
    Check("yOut = NULL в Step -> ERR_ECO_POINTER", m->pVTbl->Step(m, Oscillator, 0, 2, 0.0, 0.1, y0, 0) == ERR_ECO_POINTER);
    Check("n = 0 -> ERR_ECO_INVALIDARG", m->pVTbl->Solve(m, Oscillator, 0, 0, 0.0, 1.0, y0, 0, 11, g_t, g_y, &st) == ERR_ECO_INVALIDARG);
    Check("capacity = 1 -> ERR_ECO_INVALIDARG", m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 1.0, y0, 0, 1, g_t, g_y, &st) == ERR_ECO_INVALIDARG);
    Check("t0 = t1 -> ERR_ECO_INVALIDARG", m->pVTbl->Solve(m, Oscillator, 0, 2, 1.0, 1.0, y0, 0, 11, g_t, g_y, &st) == ERR_ECO_INVALIDARG);
    Check("не хватает места под результат -> ERR_ECO_INDEX_OUT_OF_BOUNDS", m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 1.0, y0, &opt, 6, g_t, g_y, &st) == ERR_ECO_INDEX_OUT_OF_BOUNDS && st.Points == 6);
    opt.MaxSteps = 5;
    Check("превышен MaxSteps -> ERR_ECO_INDEX_OUT_OF_BOUNDS", m->pVTbl->Solve(m, Oscillator, 0, 2, 0.0, 1.0, y0, &opt, BUF_POINTS, g_t, g_y, &st) == ERR_ECO_INDEX_OUT_OF_BOUNDS && st.Steps == 5);
    Check("код ошибки из правой части возвращается клиенту", m->pVTbl->Solve(m, Broken, 0, 1, 0.0, 1.0, y0, 0, 11, g_t, g_y, &st) == 42);
}

/*
 *
 * <summary>
 *   EcoMain Function
 * </summary>
 *
 * <description>
 *   EcoMain function - entry point
 * </description>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Pointer to the system interface */
    IEcoSystem1* pISys = 0;
    /* Pointer to the interface for working with the system interface bus */
    IEcoInterfaceBus1* pIBus = 0;
    /* Pointer to the memory management interface */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Pointer to the tested interface */
    IEcoAdvancedMath* pIMath = 0;

    /* System interface check and creation */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Free the system interface in case of an error */
            goto Release;
        }
    }

    /* Getting the interface for working with the interface bus */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Free in case of an error */
        goto Release;
    }
#ifdef ECO_LIB
    /* Registration of a static component for working with the list */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_039232DCC9354369925013DC847FF6CC);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
#endif
    /* Getting the memory management interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Check */
    if (result != 0 || pIMem == 0) {
        /* Free the system interface in case of an error */
        goto Release;
    }

    /* Getting the tested interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoAdvancedMath, (void**) &pIMath);
    if (result != 0 || pIMath == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    g_t = (double_t*)pIMem->pVTbl->Alloc(pIMem, BUF_POINTS * sizeof(double_t));
    g_y = (double_t*)pIMem->pVTbl->Alloc(pIMem, 2 * BUF_POINTS * sizeof(double_t));
    g_tf = (float_t*)pIMem->pVTbl->Alloc(pIMem, BUF_POINTS * sizeof(float_t));
    g_yf = (float_t*)pIMem->pVTbl->Alloc(pIMem, 2 * BUF_POINTS * sizeof(float_t));
    g_tl = (ldouble_t*)pIMem->pVTbl->Alloc(pIMem, BUF_POINTS * sizeof(ldouble_t));
    g_yl = (ldouble_t*)pIMem->pVTbl->Alloc(pIMem, 2 * BUF_POINTS * sizeof(ldouble_t));
    if (g_t == 0 || g_y == 0 || g_tf == 0 || g_yf == 0 || g_tl == 0 || g_yl == 0) {
        result = ERR_ECO_OUTOFMEMORY;
        goto Release;
    }

    printf("Unit-тест компонента EcoLab1: метод Рунге-Кутты 4-го порядка\n");
    TestDecayOrder(pIMath);
    TestOscillator(pIMath);
    TestLinearSystem(pIMath);
    TestPrecision(pIMath);
    TestStep(pIMath);
    TestOptionsAndBackward(pIMath);
    TestErrors(pIMath);
    printf("\nИтого: пройдено %d, провалено %d\n", g_passed, g_failed);
    result = g_failed == 0 ? 0 : -1;

Release:

    if (pIMem != 0) {
        if (g_t != 0) {
            pIMem->pVTbl->Free(pIMem, g_t);
        }
        if (g_y != 0) {
            pIMem->pVTbl->Free(pIMem, g_y);
        }
        if (g_tf != 0) {
            pIMem->pVTbl->Free(pIMem, g_tf);
        }
        if (g_yf != 0) {
            pIMem->pVTbl->Free(pIMem, g_yf);
        }
        if (g_tl != 0) {
            pIMem->pVTbl->Free(pIMem, g_tl);
        }
        if (g_yl != 0) {
            pIMem->pVTbl->Free(pIMem, g_yl);
        }
    }


    /* Free the interface for working with the interface bus */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Free the memory management interface */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Free the tested interface */
    if (pIMath != 0) {
        pIMath->pVTbl->Release(pIMath);
    }


    /* Free the system interface */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
