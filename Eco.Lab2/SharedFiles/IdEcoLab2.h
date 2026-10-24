/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLab2
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoLab2
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

#ifndef __ID_ECOLAB2_H__
#define __ID_ECOLAB2_H__

#include "IEcoBase1.h"
#include "IEcoLab2.h"

/* EcoLab2 CID = {080C4706-D304-40CC-B958-857BFF251504} */
#ifndef __CID_EcoLab2
static const UGUID CID_EcoLab2 = {0x01, 0x10, {0x08, 0x0C, 0x47, 0x06, 0xD3, 0x04, 0x40, 0xCC, 0xB9, 0x58, 0x85, 0x7B, 0xFF, 0x25, 0x15, 0x04}};
#endif /* __CID_EcoLab2 */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_080C4706D30440CCB958857BFF251504;
#endif

#endif /* __ID_ECOLAB2_H__ */

