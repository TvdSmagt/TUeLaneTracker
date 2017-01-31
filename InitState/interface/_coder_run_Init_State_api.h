/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_run_Init_State_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 28-Jan-2017 01:24:11
 */

#ifndef _CODER_RUN_INIT_STATE_API_H
#define _CODER_RUN_INIT_STATE_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_run_Init_State_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_MatlabStruct_laneFilter
#define typedef_MatlabStruct_laneFilter

typedef struct {
  emxArray_real_T *mFilter;
  emxArray_real_T *mPrior;
} MatlabStruct_laneFilter;

#endif                                 /*typedef_MatlabStruct_laneFilter*/

#ifndef typedef_MatlabStruct_likelihoods
#define typedef_MatlabStruct_likelihoods

typedef struct {
  emxArray_real_T *TOT_P_ALL;
  emxArray_real_T *DIR_ALL;
  emxArray_real_T *MASK_FOC_TOT_P;
  emxArray_real_T *TOT_P;
  emxArray_real_T *FOC_TOT_P;
  emxArray_real_T *AVG_DIR_TOT_P;
  emxArray_real_T *TOT_P_ALL_BACK_UP;
  emxArray_real_T *DIR_ALL_BACK_UP;
} MatlabStruct_likelihoods;

#endif                                 /*typedef_MatlabStruct_likelihoods*/

#ifndef typedef_MatlabStruct_templates
#define typedef_MatlabStruct_templates

typedef struct {
  emxArray_real_T *ROOT_DIR_TEMPLATE;
  emxArray_real_T *ROOT_PROB_TEMPLATE;
  emxArray_real_T *ROOT_DEPTH_TEMPLATE;
  emxArray_real_T *SEGMENT;
} MatlabStruct_templates;

#endif                                 /*typedef_MatlabStruct_templates*/

#ifndef typedef_MatlabStruct_vanishingPt
#define typedef_MatlabStruct_vanishingPt

typedef struct {
  real_T V;
  real_T H;
  real_T V_prev;
  real_T H_prev;
} MatlabStruct_vanishingPt;

#endif                                 /*typedef_MatlabStruct_vanishingPt*/

#ifndef typedef_MatlabStruct_vpFilter
#define typedef_MatlabStruct_vpFilter

typedef struct {
  emxArray_real_T *mFilter;
  emxArray_real_T *mPrior;
} MatlabStruct_vpFilter;

#endif                                 /*typedef_MatlabStruct_vpFilter*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void run_Init_State(real32_T RES_VH[2], real32_T NBUFFER,
  MatlabStruct_laneFilter *laneFilter, MatlabStruct_vpFilter *vpFilter, real_T
  *msg, MatlabStruct_likelihoods *likelihoods, MatlabStruct_templates *templates,
  MatlabStruct_vanishingPt *vanishingPt);
extern void run_Init_State_api(const mxArray *prhs[4], const mxArray *plhs[4]);
extern void run_Init_State_atexit(void);
extern void run_Init_State_initialize(void);
extern void run_Init_State_terminate(void);
extern void run_Init_State_xil_terminate(void);

#endif

/*
 * File trailer for _coder_run_Init_State_api.h
 *
 * [EOF]
 */