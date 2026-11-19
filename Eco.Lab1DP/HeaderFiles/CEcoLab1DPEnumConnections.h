#ifndef __C_ECOLAB1DP_ENUM_CONNECTIONS_H__
#define __C_ECOLAB1DP_ENUM_CONNECTIONS_H__

#include "IEcoEnumConnections.h"
#include "IEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1DP_35D14A4AEnumConnections* CEcoLab1DP_35D14A4AEnumConnectionsPtr_t;

typedef struct CEcoLab1DP_35D14A4AEnumConnections {

    IEcoEnumConnectionsVTbl* m_pVTblIEC;

    uint32_t m_cRef;
    EcoConnectionData* m_pData;
    uint32_t m_cCount;
    uint32_t m_cIndex;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab1DP_35D14A4AEnumConnections;

int16_t ECOCALLMETHOD createCEcoLab1DP_35D14A4AEnumConnections(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoList1* pIList, /* in */ const EcoConnectionData* pData, /* in */ uint32_t count, /* out */ IEcoEnumConnections** ppEnum);

#endif
