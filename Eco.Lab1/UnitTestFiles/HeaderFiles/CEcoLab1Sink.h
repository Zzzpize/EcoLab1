#ifndef __C_ECOLAB1_SINK_H__
#define __C_ECOLAB1_SINK_H__

#include "IEcoLab1Events.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

#define ECOLAB1_SINK_TRACE 1
#define ECOLAB1_SINK_STATS 2
#define ECOLAB1_SINK_DETECTOR 3

#define ECOLAB1_SINK_MAX_SOURCES 4

typedef struct CEcoLab1Sink {

    IEcoLab1EventsVTbl* m_pVTblIEcoLab1Events;

    int16_t (ECOCALLMETHOD *Advise)(/* in */ struct CEcoLab1Sink* me, /* in */ IEcoUnknown* pISource);
    int16_t (ECOCALLMETHOD *Unadvise)(/* in */ struct CEcoLab1Sink* me, /* in */ IEcoUnknown* pISource);

    uint32_t m_cRef;
    uint32_t m_cCookie[ECOLAB1_SINK_MAX_SOURCES];
    IEcoUnknown* m_pISource[ECOLAB1_SINK_MAX_SOURCES];

    IEcoMemoryAllocator1* m_pIMem;

    const char_t* m_Name;
    uint32_t m_Kind;
    bool_t m_bPrint;
    uint32_t m_cEvery;
    bool_t m_bStopOnEvent;

    const char_t* m_Method;
    uint32_t m_cStarted;
    uint32_t m_cSteps;
    uint32_t m_cRejected;
    uint32_t m_cFinished;
    uint32_t m_cRunSteps;
    uint32_t m_cRunRejected;
    double_t m_hMin;
    double_t m_hMax;
    int16_t m_LastStatus;

    double_t m_PrevY;
    double_t m_tEvent;
    bool_t m_bEvent;

} CEcoLab1Sink, *CEcoLab1SinkPtr;

int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ const char_t* name, /* in */ uint32_t kind, /* out */ IEcoLab1Events** ppIEcoLab1Events);
void ECOCALLMETHOD deleteCEcoLab1Sink(/* in */ IEcoLab1Events* pIEcoLab1Events);

#endif
