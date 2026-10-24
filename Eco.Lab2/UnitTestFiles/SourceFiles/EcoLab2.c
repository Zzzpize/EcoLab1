/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   EcoLab2
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
#include "IdEcoLab2.h"
#include "IdEcoLab1.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"

static int g_passed = 0;
static int g_failed = 0;

static double_t* g_t = 0;
static double_t* g_y = 0;

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

static int16_t ECOCALLMETHOD Oscillator(voidptr_t ctx, double_t t, const double_t* y, double_t* dydt, uint32_t n) {
    dydt[0] = y[1];
    dydt[1] = -y[0];
    return 0;
}

static int32_t HornerDirect(const int16_t* coeffs, uint32_t n, int16_t x) {
    int32_t acc = 0;
    uint32_t i = 0;

    for (i = 0; i < n; i++) {
        acc = acc * x + coeffs[i];
    }
    return acc;
}

static void TestHorner(IEcoLab2* pIEcoLab2) {
    int16_t p1[4];
    int16_t p2[3];
    int16_t big[3];
    int32_t value = 0;
    int16_t x = 0;
    int16_t r = 0;
    int ok = 1;

    printf("\n1. IEcoLab2::Horner: умножение через включенный D, сложение через включенный A\n");
    p1[0] = 2;
    p1[1] = -3;
    p1[2] = 0;
    p1[3] = 5;
    printf("p(x) = 2x^3 - 3x^2 + 5\n");
    printf("%6s %12s %12s\n", "x", "Horner", "напрямую");
    for (x = -3; x <= 4; x++) {
        r = pIEcoLab2->pVTbl->Horner(pIEcoLab2, p1, 4, x, &value);
        printf("%6d %12d %12d\n", (int)x, (int)value, (int)HornerDirect(p1, 4, x));
        ok = ok && r == 0 && value == HornerDirect(p1, 4, x);
    }
    Check("значения многочлена совпадают с прямым вычислением", ok);

    p2[0] = 1;
    p2[1] = 0;
    p2[2] = -1;
    r = pIEcoLab2->pVTbl->Horner(pIEcoLab2, p2, 3, 1, &value);
    Check("корень x^2 - 1 в точке 1 дает 0", r == 0 && value == 0);

    big[0] = 100;
    big[1] = 0;
    big[2] = 0;
    Check("переполнение int16 в промежуточном результате -> ERR_ECO_FAIL", pIEcoLab2->pVTbl->Horner(pIEcoLab2, big, 3, 100, &value) == ERR_ECO_FAIL);
    Check("n = 0 -> ERR_ECO_INVALIDARG", pIEcoLab2->pVTbl->Horner(pIEcoLab2, p1, 0, 1, &value) == ERR_ECO_INVALIDARG);
    Check("coeffs = NULL -> ERR_ECO_POINTER", pIEcoLab2->pVTbl->Horner(pIEcoLab2, 0, 3, 1, &value) == ERR_ECO_POINTER);
}

static void TestAggregatedLab1(IEcoLab2* pIEcoLab2) {
    IEcoAdvancedMath* pIMath = 0;
    IEcoCalculatorX* pIX = 0;
    IEcoCalculatorY* pIY = 0;
    EcoOdeStats st;
    double_t y0[2];
    int16_t r = 0;

    printf("\n2. Eco.Lab1 агрегирован в Eco.Lab2: его интерфейсы отдаются клиенту напрямую\n");
    r = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoAdvancedMath, (void**) &pIMath);
    Check("QueryInterface(IID_IEcoAdvancedMath) у Eco.Lab2", r == 0 && pIMath != 0);
    if (pIMath == 0) {
        return;
    }
    y0[0] = 1.0;
    y0[1] = 0.0;
    r = pIMath->pVTbl->Solve(pIMath, Oscillator, 0, 2, 0.0, 10.0, y0, 0, 1001, g_t, g_y, &st);
    printf("Solve (Рунге-Кутта 4) через Eco.Lab2: x(10) = %.12f, cos(10) = %.12f\n", g_y[2000], cos(10.0));
    Check("метод Рунге-Кутты работает через агрегированный Eco.Lab1", r == 0 && fabs(g_y[2000] - cos(10.0)) < 1e-9);

    r = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void**) &pIX);
    Check("QueryInterface(IID_IEcoCalculatorX): X компонента B через два уровня агрегирования", r == 0 && pIX != 0);
    r = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorY, (void**) &pIY);
    Check("QueryInterface(IID_IEcoCalculatorY): Y из Eco.Lab1 (включен E)", r == 0 && pIY != 0);
    if (pIX != 0 && pIY != 0) {
        printf("  Addition(3, 5) = %d, Subtraction(3, 5) = %d, Multiplication(6, 7) = %d, Division(20, 3) = %d\n",
               (int)pIX->pVTbl->Addition(pIX, 3, 5), (int)pIX->pVTbl->Subtraction(pIX, 3, 5),
               (int)pIY->pVTbl->Multiplication(pIY, 6, 7), (int)pIY->pVTbl->Division(pIY, 20, 3));
        Check("арифметика через Eco.Lab2", pIX->pVTbl->Addition(pIX, 3, 5) == 8 && pIX->pVTbl->Subtraction(pIX, 3, 5) == -2
              && pIY->pVTbl->Multiplication(pIY, 6, 7) == 42 && pIY->pVTbl->Division(pIY, 20, 3) == 6);
    }
    if (pIY != 0) {
        pIY->pVTbl->Release(pIY);
    }
    if (pIX != 0) {
        pIX->pVTbl->Release(pIX);
    }
    pIMath->pVTbl->Release(pIMath);
}

static void TestQueryInterfaceRules(IEcoLab2* pIEcoLab2) {
    IEcoAdvancedMath* pIMath = 0;
    IEcoCalculatorX* pIX = 0;
    IEcoCalculatorY* pIY = 0;
    IEcoLab2* pIL2 = 0;
    IEcoUnknown* pU[4];
    void* pBad = 0;
    int16_t r = 0;
    int i = 0;
    int same = 1;

    printf("\n3. Правила QueryInterface для четырех интерфейсов Eco.Lab2\n");
    pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoAdvancedMath, (void**) &pIMath);
    pIMath->pVTbl->QueryInterface(pIMath, &IID_IEcoCalculatorX, (void**) &pIX);
    pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void**) &pIY);

    pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoUnknown, (void**) &pU[0]);
    pIMath->pVTbl->QueryInterface(pIMath, &IID_IEcoUnknown, (void**) &pU[1]);
    pIX->pVTbl->QueryInterface(pIX, &IID_IEcoUnknown, (void**) &pU[2]);
    pIY->pVTbl->QueryInterface(pIY, &IID_IEcoUnknown, (void**) &pU[3]);
    printf("IEcoUnknown через IEcoLab2 %p, Math %p, X %p, Y %p\n", (void*)pU[0], (void*)pU[1], (void*)pU[2], (void*)pU[3]);
    for (i = 1; i < 4; i++) {
        same = same && pU[i] == pU[0];
    }
    Check("1. один и тот же IEcoUnknown у всех интерфейсов, включая интерфейс B", same);

    r = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab2, (void**) &pIL2);
    Check("из X компонента B получается IEcoLab2 внешнего компонента", r == 0 && pIL2 == pIEcoLab2);
    pIL2->pVTbl->Release(pIL2);

    r = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoAdvancedMath, (void**) &pIMath);
    Check("4. можно вернуться туда, откуда начали (Math -> X -> Y -> Math)", r == 0);
    pIMath->pVTbl->Release(pIMath);

    pBad = (void*)pIEcoLab2;
    r = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoInterfaceBus1, &pBad);
    Check("неподдерживаемый интерфейс: ERR_ECO_NOINTERFACE", r == ERR_ECO_NOINTERFACE && pBad == 0);

    for (i = 0; i < 4; i++) {
        pU[i]->pVTbl->Release(pU[i]);
    }
    pIY->pVTbl->Release(pIY);
    pIX->pVTbl->Release(pIX);
    pIMath->pVTbl->Release(pIMath);
}

static void TestReferenceCounting(IEcoLab2* pIEcoLab2) {
    IEcoCalculatorX* pIX = 0;
    IEcoAdvancedMath* pIMath = 0;
    uint32_t base = 0;
    uint32_t cx = 0;
    uint32_t cm = 0;
    uint32_t back = 0;

    printf("\n4. Подсчет ссылок: интерфейсы агрегированных компонентов увеличивают счетчик Eco.Lab2\n");
    base = pIEcoLab2->pVTbl->AddRef(pIEcoLab2);
    pIEcoLab2->pVTbl->Release(pIEcoLab2);
    pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void**) &pIX);
    cx = pIX->pVTbl->AddRef(pIX);
    pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoAdvancedMath, (void**) &pIMath);
    cm = pIMath->pVTbl->AddRef(pIMath);
    printf("AddRef: IEcoLab2 %u, X (компонент B) %u, IEcoAdvancedMath (Eco.Lab1) %u\n", (unsigned)base, (unsigned)cx, (unsigned)cm);
    Check("один общий счетчик на Eco.Lab2, Eco.Lab1 и B", cx == base + 1 && cm == cx + 2);
    pIMath->pVTbl->Release(pIMath);
    pIMath->pVTbl->Release(pIMath);
    pIX->pVTbl->Release(pIX);
    back = pIX->pVTbl->Release(pIX);
    Check("после Release счетчик вернулся к исходному", back == base - 1);
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
    IEcoLab2* pIEcoLab2 = 0;

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
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_080C4706D30440CCB958857BFF251504);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_039232DCC9354369925013DC847FF6CC);
    if (result != 0 ) {
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorA, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0 ) {
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorB, (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    if (result != 0 ) {
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorD, (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    if (result != 0 ) {
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorE, (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0 ) {
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
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**) &pIEcoLab2);
    if (result != 0 || pIEcoLab2 == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    g_t = (double_t*)pIMem->pVTbl->Alloc(pIMem, 1001 * sizeof(double_t));
    g_y = (double_t*)pIMem->pVTbl->Alloc(pIMem, 2002 * sizeof(double_t));
    if (g_t == 0 || g_y == 0) {
        result = ERR_ECO_OUTOFMEMORY;
        goto Release;
    }

    printf("Unit-тест компонента EcoLab2: агрегирование Eco.Lab1 и включение калькуляторов A и D\n");
    TestHorner(pIEcoLab2);
    TestAggregatedLab1(pIEcoLab2);
    TestQueryInterfaceRules(pIEcoLab2);
    TestReferenceCounting(pIEcoLab2);
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
    if (pIEcoLab2 != 0) {
        printf("Release последней ссылки на Eco.Lab2: %u\n", (unsigned)pIEcoLab2->pVTbl->Release(pIEcoLab2));
    }


    /* Free the system interface */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
