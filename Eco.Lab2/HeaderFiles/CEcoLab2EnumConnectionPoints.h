#ifndef __C_ECOLAB2_ENUM_CONNECTION_POINTS_H__
#define __C_ECOLAB2_ENUM_CONNECTION_POINTS_H__

#include "IEcoEnumConnectionPoints.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab2_FF251504EnumConnectionPoints* CEcoLab2_FF251504EnumConnectionPointsPtr_t;

typedef struct CEcoLab2_FF251504EnumConnectionPoints {

    IEcoEnumConnectionPointsVTbl* m_pVTblIECP;

    uint32_t m_cRef;
    IEcoConnectionPoint** m_ppCP;
    uint32_t m_cCount;
    uint32_t m_cIndex;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab2_FF251504EnumConnectionPoints;

int16_t ECOCALLMETHOD createCEcoLab2_FF251504EnumConnectionPoints(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoConnectionPoint** ppCP, /* in */ uint32_t count, /* in */ uint32_t index, /* out */ IEcoEnumConnectionPoints** ppEnum);

#endif
