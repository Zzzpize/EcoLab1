/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoLab2
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLab2
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2026 . All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECOLAB2_H__
#define __I_ECOLAB2_H__

#include "IEcoBase1.h"

/* IEcoLab2 IID = {E9A8093E-3110-45CA-A1DA-8AC1BDA991A4} */
#ifndef __IID_IEcoLab2
static const UGUID IID_IEcoLab2 = {0x01, 0x10, {0xE9, 0xA8, 0x09, 0x3E, 0x31, 0x10, 0x45, 0xCA, 0xA1, 0xDA, 0x8A, 0xC1, 0xBD, 0xA9, 0x91, 0xA4}};
#endif /* __IID_IEcoLab2 */

typedef struct IEcoLab2* IEcoLab2Ptr_t;

typedef struct IEcoLab2VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab2Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab2Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab2Ptr_t me);

    /* IEcoLab2 */
    int16_t (ECOCALLMETHOD *Horner)(/* in */ IEcoLab2Ptr_t me, /* in */ const int16_t* coeffs, /* in */ uint32_t n, /* in */ int16_t x, /* out */ int32_t* result);

} IEcoLab2VTbl, *IEcoLab2VTblPtr_t;

interface IEcoLab2 {
    struct IEcoLab2VTbl *pVTbl;
} IEcoLab2;


#endif /* __I_ECOLAB2_H__ */

