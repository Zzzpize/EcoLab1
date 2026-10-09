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
 *   This header describes the implementation of the CEcoLab1DP_35D14A4A component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 . All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECOLAB1DP_H__
#define __C_ECOLAB1DP_H__

#include "IEcoLab1DP.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1DP_35D14A4A* CEcoLab1DP_35D14A4APtr_t;

typedef struct CEcoLab1DP_35D14A4A {

    /* IEcoLab1DP interface function table */
    IEcoLab1DPVTbl* m_pVTblIEcoLab1DP;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLab1DP_35D14A4APtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLab1DP_35D14A4APtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLab1DP_35D14A4APtr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

} CEcoLab1DP_35D14A4A;

#endif /* __C_ECOLAB1DP_H__ */
