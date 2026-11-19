#ifndef __C_ECOLAB1DP_CONNECTION_POINT_H__
#define __C_ECOLAB1DP_CONNECTION_POINT_H__

#include "IEcoConnectionPoint.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoEnumConnections.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoList1.h"
#include "IdEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1DP_35D14A4AConnectionPoint* CEcoLab1DP_35D14A4AConnectionPointPtr_t;

typedef struct CEcoLab1DP_35D14A4AConnectionPoint {

    IEcoConnectionPointVTbl* m_pVTblICP;

    IEcoConnectionPointContainer* m_pICPC;
    UGUID m_iid;
    uint32_t m_cNextCookie;
    IEcoList1* m_pSinkList;
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab1DP_35D14A4AConnectionPoint;

int16_t ECOCALLMETHOD createCEcoLab1DP_35D14A4AConnectionPoint(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoInterfaceBus1* pIBus, /* in */ IEcoConnectionPointContainer* pICPC, /* in */ const UGUID* riid, /* out */ CEcoLab1DP_35D14A4AConnectionPoint** ppCP);
void ECOCALLMETHOD deleteCEcoLab1DP_35D14A4AConnectionPoint(/* in */ CEcoLab1DP_35D14A4AConnectionPoint* pCMe);
uint32_t ECOCALLMETHOD CEcoLab1DP_35D14A4AConnectionPoint_Count(/* in */ CEcoLab1DP_35D14A4AConnectionPoint* pCMe);

#endif
