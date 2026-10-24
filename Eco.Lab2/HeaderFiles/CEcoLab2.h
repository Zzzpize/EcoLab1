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
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab2_FF251504* CEcoLab2_FF251504Ptr_t;

typedef struct CEcoLab2_FF251504 {

    /* IEcoLab2 interface function table */
    IEcoLab2VTbl* m_pVTblIEcoLab2;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLab2_FF251504Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLab2_FF251504Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLab2_FF251504Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    IEcoUnknown* m_pInnerUnknown;
    IEcoCalculatorX* m_pIX;
    IEcoCalculatorY* m_pIY;

} CEcoLab2_FF251504;

#endif /* __C_ECOLAB2_H__ */
