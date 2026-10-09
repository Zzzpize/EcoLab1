/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoLab1DP
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLab1DP
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

#ifndef __I_ECOLAB1DP_H__
#define __I_ECOLAB1DP_H__

#include "IEcoBase1.h"

/* IEcoLab1DP IID = {E6B182F1-257B-44C1-A815-97ADAC4B3836} */
#ifndef __IID_IEcoLab1DP
static const UGUID IID_IEcoLab1DP = {0x01, 0x10, {0xE6, 0xB1, 0x82, 0xF1, 0x25, 0x7B, 0x44, 0xC1, 0xA8, 0x15, 0x97, 0xAD, 0xAC, 0x4B, 0x38, 0x36}};
#endif /* __IID_IEcoLab1DP */

typedef struct IEcoLab1DP* IEcoLab1DPPtr_t;

typedef struct IEcoLab1DPVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab1DPPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab1DPPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab1DPPtr_t me);

    /* IEcoLab1DP */
    int16_t (ECOCALLMETHOD *MyFunction)(/* in */ IEcoLab1DPPtr_t me, /* in */ char_t* Name, /* out */ char_t** CopyName);

} IEcoLab1DPVTbl, *IEcoLab1DPVTblPtr_t;

interface IEcoLab1DP {
    struct IEcoLab1DPVTbl *pVTbl;
} IEcoLab1DP;


#endif /* __I_ECOLAB1DP_H__ */

