#ifndef __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__
#define __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__

#include "IEcoEnumConnectionPoints.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1_847FF6CCEnumConnectionPoints* CEcoLab1_847FF6CCEnumConnectionPointsPtr_t;

typedef struct CEcoLab1_847FF6CCEnumConnectionPoints {

    IEcoEnumConnectionPointsVTbl* m_pVTblIECP;

    uint32_t m_cRef;
    IEcoConnectionPoint** m_ppCP;
    uint32_t m_cCount;
    uint32_t m_cIndex;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab1_847FF6CCEnumConnectionPoints;

int16_t ECOCALLMETHOD createCEcoLab1_847FF6CCEnumConnectionPoints(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoConnectionPoint** ppCP, /* in */ uint32_t count, /* in */ uint32_t index, /* out */ IEcoEnumConnectionPoints** ppEnum);

#endif
