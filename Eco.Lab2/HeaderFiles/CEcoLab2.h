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
 *   This header describes the implementation of the CEcoLab2_FF251504 component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 . All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECOLAB2_H__
#define __C_ECOLAB2_H__

#include "IEcoLab2.h"
#include "IEcoLab2Events.h"
#include "IEcoLab1Events.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab2ConnectionPoint.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab2_FF251504* CEcoLab2_FF251504Ptr_t;

typedef struct CEcoLab2_FF251504 {

    /* IEcoLab2 interface function table */
    IEcoLab2VTbl* m_pVTblIEcoLab2;
    IEcoConnectionPointContainerVTbl* m_pVTblICPC;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLab2_FF251504Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLab2_FF251504Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLab2_FF251504Ptr_t pCMe);
    int16_t (ECOCALLMETHOD *Fire_OnHornerStarted)(/* in */ struct CEcoLab2_FF251504* me, /* in */ const int16_t* coeffs, /* in */ uint32_t n, /* in */ int16_t x);
    int16_t (ECOCALLMETHOD *Fire_OnHornerStep)(/* in */ struct CEcoLab2_FF251504* me, /* in */ uint32_t index, /* in */ int32_t product, /* in */ int16_t coeff, /* in */ int32_t acc);
    int16_t (ECOCALLMETHOD *Fire_OnHornerFinished)(/* in */ struct CEcoLab2_FF251504* me, /* in */ int32_t result, /* in */ int16_t status);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    IEcoUnknown* m_pInnerUnknown;
    IEcoCalculatorX* m_pIX;
    IEcoCalculatorY* m_pIY;
    CEcoLab2_FF251504ConnectionPoint* m_pISinkCP;

} CEcoLab2_FF251504;

#endif /* __C_ECOLAB2_H__ */
