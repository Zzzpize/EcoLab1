#ifndef __I_ECO_LAB1_EVENTS_H__
#define __I_ECO_LAB1_EVENTS_H__

#include "IEcoBase1.h"

#ifndef __IID_IEcoLab1Events
static const UGUID IID_IEcoLab1Events = {0x01, 0x10, {0x29, 0xEE, 0xA0, 0x95, 0x7A, 0x26, 0x41, 0x8C, 0x99, 0x26, 0x55, 0x0C, 0xEE, 0x12, 0x53, 0x09}};
#endif

typedef struct IEcoLab1Events* IEcoLab1EventsPtr_t;

typedef struct IEcoLab1EventsVTbl {

    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab1EventsPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab1EventsPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab1EventsPtr_t me);

    int16_t (ECOCALLMETHOD *OnSolveStarted)(/* in */ IEcoLab1EventsPtr_t me, /* in */ const char_t* method, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ double_t h, /* in */ const double_t* y0);
    int16_t (ECOCALLMETHOD *OnStep)(/* in */ IEcoLab1EventsPtr_t me, /* in */ uint32_t index, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* in */ uint32_t n, /* out */ bool_t* isStop);
    int16_t (ECOCALLMETHOD *OnStepRejected)(/* in */ IEcoLab1EventsPtr_t me, /* in */ uint32_t index, /* in */ double_t t, /* in */ double_t h, /* in */ double_t err);
    int16_t (ECOCALLMETHOD *OnSolveFinished)(/* in */ IEcoLab1EventsPtr_t me, /* in */ uint32_t steps, /* in */ uint32_t evaluations, /* in */ int16_t status);

} IEcoLab1EventsVTbl, *IEcoLab1EventsVTblPtr_t;

interface IEcoLab1Events {
    struct IEcoLab1EventsVTbl *pVTbl;
} IEcoLab1Events;

#endif
