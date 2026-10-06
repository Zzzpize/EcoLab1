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
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1_847FF6CC* CEcoLab1_847FF6CCPtr_t;

typedef struct CEcoLab1_847FF6CC {

    /* IEcoAdvancedMath interface function table */
    IEcoAdvancedMathVTbl* m_pVTblIEcoAdvancedMath;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLab1_847FF6CCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLab1_847FF6CCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLab1_847FF6CCPtr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

} CEcoLab1_847FF6CC;

#endif /* __C_ECOLAB1_H__ */
