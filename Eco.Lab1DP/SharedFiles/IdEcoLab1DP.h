/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLab1DP
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoLab1DP
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

#ifndef __ID_ECOLAB1DP_H__
#define __ID_ECOLAB1DP_H__

#include "IEcoBase1.h"
#include "IEcoAdvancedMath.h"

/* EcoLab1DP CID = {AFC67744-F1C3-43AC-891C-A5DA35D14A4A} */
#ifndef __CID_EcoLab1DP
static const UGUID CID_EcoLab1DP = {0x01, 0x10, {0xAF, 0xC6, 0x77, 0x44, 0xF1, 0xC3, 0x43, 0xAC, 0x89, 0x1C, 0xA5, 0xDA, 0x35, 0xD1, 0x4A, 0x4A}};
#endif /* __CID_EcoLab1DP */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_AFC67744F1C343AC891CA5DA35D14A4A;
#endif

#endif /* __ID_ECOLAB1DP_H__ */

