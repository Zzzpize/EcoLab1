#ifndef __I_ECO_LAB2_EVENTS_H__
#define __I_ECO_LAB2_EVENTS_H__

#include "IEcoBase1.h"

#ifndef __IID_IEcoLab2Events
static const UGUID IID_IEcoLab2Events = {0x01, 0x10, {0xAB, 0x50, 0xC6, 0xC5, 0xF6, 0xF9, 0x45, 0x7C, 0xA8, 0x34, 0xBB, 0x95, 0xC5, 0xD4, 0xF7, 0x69}};
#endif

typedef struct IEcoLab2Events* IEcoLab2EventsPtr_t;

typedef struct IEcoLab2EventsVTbl {

    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab2EventsPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab2EventsPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab2EventsPtr_t me);

    int16_t (ECOCALLMETHOD *OnHornerStarted)(/* in */ IEcoLab2EventsPtr_t me, /* in */ const int16_t* coeffs, /* in */ uint32_t n, /* in */ int16_t x);
    int16_t (ECOCALLMETHOD *OnHornerStep)(/* in */ IEcoLab2EventsPtr_t me, /* in */ uint32_t index, /* in */ int32_t product, /* in */ int16_t coeff, /* in */ int32_t acc);
    int16_t (ECOCALLMETHOD *OnHornerFinished)(/* in */ IEcoLab2EventsPtr_t me, /* in */ int32_t result, /* in */ int16_t status);

} IEcoLab2EventsVTbl, *IEcoLab2EventsVTblPtr_t;

interface IEcoLab2Events {
    struct IEcoLab2EventsVTbl *pVTbl;
} IEcoLab2Events;

#endif
