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
 *   This header describes the implementation of the CEcoLab1_847FF6CC component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 . All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECOLAB1_H__
#define __C_ECOLAB1_H__

#include "IEcoAdvancedMath.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IEcoLab1Events.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab1ConnectionPoint.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1_847FF6CC* CEcoLab1_847FF6CCPtr_t;

typedef struct CEcoLab1_847FF6CC {

    /* IEcoAdvancedMath interface function table */
    IEcoAdvancedMathVTbl* m_pVTblIEcoAdvancedMath;
    IEcoCalculatorYVTbl* m_pVTblIY;
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;
    IEcoConnectionPointContainerVTbl* m_pVTblICPC;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLab1_847FF6CCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLab1_847FF6CCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLab1_847FF6CCPtr_t pCMe);
    int16_t (ECOCALLMETHOD *Fire_OnSolveStarted)(/* in */ struct CEcoLab1_847FF6CC* me, /* in */ const char_t* method, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ double_t h, /* in */ const double_t* y0);
    int16_t (ECOCALLMETHOD *Fire_OnStep)(/* in */ struct CEcoLab1_847FF6CC* me, /* in */ uint32_t index, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* in */ uint32_t n, /* out */ bool_t* isStop);
    int16_t (ECOCALLMETHOD *Fire_OnSolveFinished)(/* in */ struct CEcoLab1_847FF6CC* me, /* in */ uint32_t steps, /* in */ uint32_t evaluations, /* in */ int16_t status);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    IEcoUnknown* m_pIUnkOuter;
    IEcoUnknown* m_pInnerUnknown;
    IEcoCalculatorY* m_pIY;
    CEcoLab1_847FF6CCConnectionPoint* m_pISinkCP;

} CEcoLab1_847FF6CC;

#endif /* __C_ECOLAB1_H__ */
