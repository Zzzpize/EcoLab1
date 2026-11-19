#ifndef __C_ECOLAB1DP_ENUM_CONNECTION_POINTS_H__
#define __C_ECOLAB1DP_ENUM_CONNECTION_POINTS_H__

#include "IEcoEnumConnectionPoints.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1DP_35D14A4AEnumConnectionPoints* CEcoLab1DP_35D14A4AEnumConnectionPointsPtr_t;

typedef struct CEcoLab1DP_35D14A4AEnumConnectionPoints {

    IEcoEnumConnectionPointsVTbl* m_pVTblIECP;

    uint32_t m_cRef;
    IEcoConnectionPoint** m_ppCP;
    uint32_t m_cCount;
    uint32_t m_cIndex;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab1DP_35D14A4AEnumConnectionPoints;

int16_t ECOCALLMETHOD createCEcoLab1DP_35D14A4AEnumConnectionPoints(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoConnectionPoint** ppCP, /* in */ uint32_t count, /* in */ uint32_t index, /* out */ IEcoEnumConnectionPoints** ppEnum);

#endif
