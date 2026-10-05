/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLab1
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoLab1
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

#ifndef __ID_ECOLAB1_H__
#define __ID_ECOLAB1_H__

#include "IEcoBase1.h"
#include "IEcoLab1.h"

/* EcoLab1 CID = {039232DC-C935-4369-9250-13DC847FF6CC} */
#ifndef __CID_EcoLab1
static const UGUID CID_EcoLab1 = {0x01, 0x10, {0x03, 0x92, 0x32, 0xDC, 0xC9, 0x35, 0x43, 0x69, 0x92, 0x50, 0x13, 0xDC, 0x84, 0x7F, 0xF6, 0xCC}};
#endif /* __CID_EcoLab1 */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_039232DCC9354369925013DC847FF6CC;
#endif

#endif /* __ID_ECOLAB1_H__ */

