#ifndef __C_ECOLAB2_ENUM_CONNECTIONS_H__
#define __C_ECOLAB2_ENUM_CONNECTIONS_H__

#include "IEcoEnumConnections.h"
#include "IEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab2_FF251504EnumConnections* CEcoLab2_FF251504EnumConnectionsPtr_t;

typedef struct CEcoLab2_FF251504EnumConnections {

    IEcoEnumConnectionsVTbl* m_pVTblIEC;

    uint32_t m_cRef;
    EcoConnectionData* m_pData;
    uint32_t m_cCount;
    uint32_t m_cIndex;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab2_FF251504EnumConnections;

int16_t ECOCALLMETHOD createCEcoLab2_FF251504EnumConnections(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoList1* pIList, /* in */ const EcoConnectionData* pData, /* in */ uint32_t count, /* out */ IEcoEnumConnections** ppEnum);

#endif
