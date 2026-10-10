#ifndef __I_ECO_ADVANCED_MATH_H__
#define __I_ECO_ADVANCED_MATH_H__

#include "IEcoBase1.h"

/* IEcoAdvancedMath IID = {4EF92ACD-8656-4B68-821E-2E480C0651D9} */
#ifndef __IID_IEcoAdvancedMath
static const UGUID IID_IEcoAdvancedMath = {0x01, 0x10, {0x4E, 0xF9, 0x2A, 0xCD, 0x86, 0x56, 0x4B, 0x68, 0x82, 0x1E, 0x2E, 0x48, 0x0C, 0x06, 0x51, 0xD9}};
#endif /* __IID_IEcoAdvancedMath */

#ifndef ECO_LDOUBLE_T_DEFINED
#define ECO_LDOUBLE_T_DEFINED
typedef long double ldouble_t;
#endif

typedef int16_t (ECOCALLMETHOD *EcoOdeFunc)(/* in */ voidptr_t ctx, /* in */ double_t t, /* in */ const double_t* y, /* out */ double_t* dydt, /* in */ uint32_t n);
typedef int16_t (ECOCALLMETHOD *EcoOdeFuncF)(/* in */ voidptr_t ctx, /* in */ float_t t, /* in */ const float_t* y, /* out */ float_t* dydt, /* in */ uint32_t n);
typedef int16_t (ECOCALLMETHOD *EcoOdeFuncL)(/* in */ voidptr_t ctx, /* in */ ldouble_t t, /* in */ const ldouble_t* y, /* out */ ldouble_t* dydt, /* in */ uint32_t n);

typedef struct EcoOdeOptions {
    double_t Step;
    double_t RelTol;
    double_t AbsTol;
    uint32_t MaxSteps;
} EcoOdeOptions;

typedef struct EcoOdeStats {
    uint32_t Points;
    uint32_t Steps;
    uint32_t Rejected;
    uint32_t Evaluations;
} EcoOdeStats;

typedef struct IEcoAdvancedMath* IEcoAdvancedMathPtr_t;

typedef struct IEcoAdvancedMathVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoAdvancedMathPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoAdvancedMathPtr_t me);

    /* IEcoAdvancedMath */
    int16_t (ECOCALLMETHOD *Step)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t, /* in */ double_t h, /* in */ const double_t* y, /* out */ double_t* yOut);
    int16_t (ECOCALLMETHOD *Stepf)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t, /* in */ float_t h, /* in */ const float_t* y, /* out */ float_t* yOut);
    int16_t (ECOCALLMETHOD *Stepl)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t, /* in */ ldouble_t h, /* in */ const ldouble_t* y, /* out */ ldouble_t* yOut);

    int16_t (ECOCALLMETHOD *Solve)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFunc f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ double_t t0, /* in */ double_t t1, /* in */ const double_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ double_t* tOut, /* out */ double_t* yOut, /* out */ EcoOdeStats* stats);
    int16_t (ECOCALLMETHOD *Solvef)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncF f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ float_t t0, /* in */ float_t t1, /* in */ const float_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ float_t* tOut, /* out */ float_t* yOut, /* out */ EcoOdeStats* stats);
    int16_t (ECOCALLMETHOD *Solvel)(/* in */ IEcoAdvancedMathPtr_t me, /* in */ EcoOdeFuncL f, /* in */ voidptr_t ctx, /* in */ uint32_t n, /* in */ ldouble_t t0, /* in */ ldouble_t t1, /* in */ const ldouble_t* y0, /* in */ const EcoOdeOptions* opt, /* in */ uint32_t capacity, /* out */ ldouble_t* tOut, /* out */ ldouble_t* yOut, /* out */ EcoOdeStats* stats);

} IEcoAdvancedMathVTbl, *IEcoAdvancedMathVTblPtr_t;

interface IEcoAdvancedMath {
    struct IEcoAdvancedMathVTbl *pVTbl;
} IEcoAdvancedMath;

#endif /* __I_ECO_ADVANCED_MATH_H__ */
