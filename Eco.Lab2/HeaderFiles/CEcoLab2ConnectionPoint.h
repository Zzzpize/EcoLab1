#ifndef __C_ECOLAB2_CONNECTION_POINT_H__
#define __C_ECOLAB2_CONNECTION_POINT_H__

#include "IEcoConnectionPoint.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoEnumConnections.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoList1.h"
#include "IdEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab2_FF251504ConnectionPoint* CEcoLab2_FF251504ConnectionPointPtr_t;

typedef struct CEcoLab2_FF251504ConnectionPoint {

    IEcoConnectionPointVTbl* m_pVTblICP;

    IEcoConnectionPointContainer* m_pICPC;
    UGUID m_iid;
    uint32_t m_cNextCookie;
    IEcoList1* m_pSinkList;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab2_FF251504ConnectionPoint;

int16_t ECOCALLMETHOD createCEcoLab2_FF251504ConnectionPoint(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoInterfaceBus1* pIBus, /* in */ IEcoConnectionPointContainer* pICPC, /* in */ const UGUID* riid, /* out */ CEcoLab2_FF251504ConnectionPoint** ppCP);
void ECOCALLMETHOD deleteCEcoLab2_FF251504ConnectionPoint(/* in */ CEcoLab2_FF251504ConnectionPoint* pCMe);
uint32_t ECOCALLMETHOD CEcoLab2_FF251504ConnectionPoint_Count(/* in */ CEcoLab2_FF251504ConnectionPoint* pCMe);

#endif
