#ifndef __C_ECOLAB1_CONNECTION_POINT_H__
#define __C_ECOLAB1_CONNECTION_POINT_H__

#include "IEcoConnectionPoint.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoEnumConnections.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoList1.h"
#include "IdEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1_847FF6CCConnectionPoint* CEcoLab1_847FF6CCConnectionPointPtr_t;

typedef struct CEcoLab1_847FF6CCConnectionPoint {

    IEcoConnectionPointVTbl* m_pVTblICP;

    IEcoConnectionPointContainer* m_pICPC;
    UGUID m_iid;
    uint32_t m_cNextCookie;
    IEcoList1* m_pSinkList;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab1_847FF6CCConnectionPoint;

int16_t ECOCALLMETHOD createCEcoLab1_847FF6CCConnectionPoint(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoInterfaceBus1* pIBus, /* in */ IEcoConnectionPointContainer* pICPC, /* in */ const UGUID* riid, /* out */ CEcoLab1_847FF6CCConnectionPoint** ppCP);
void ECOCALLMETHOD deleteCEcoLab1_847FF6CCConnectionPoint(/* in */ CEcoLab1_847FF6CCConnectionPoint* pCMe);
uint32_t ECOCALLMETHOD CEcoLab1_847FF6CCConnectionPoint_Count(/* in */ CEcoLab1_847FF6CCConnectionPoint* pCMe);

#endif
