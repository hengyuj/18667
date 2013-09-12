#ifndef __c1_one_user_h__
#define __c1_one_user_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc1_one_userInstanceStruct
#define typedef_SFc1_one_userInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_idle_0;
  uint8_T c1_tp_acquired_1;
  uint8_T c1_tp_done_2;
  uint8_T c1_tp_a_USER;
  uint8_T c1_tp_Resource;
  uint8_T c1_b_tp_idle_0;
  uint8_T c1_tp_busy_2;
  uint8_T c1_tp_Shared_Resource;
  uint8_T c1_c_tp_idle_0;
  uint8_T c1_b_tp_done_2;
  uint8_T c1_b_tp_acquired_1;
  uint8_T c1_tp_b_USER;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_one_user;
  uint8_T c1_is_c1_one_user;
  uint8_T c1_is_a_USER;
  uint8_T c1_is_active_a_USER;
  uint8_T c1_is_Resource;
  uint8_T c1_is_active_Resource;
  uint8_T c1_is_b_USER;
  uint8_T c1_is_active_b_USER;
  real_T c1_r_in_use;
  real_T c1_tmp;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
} SFc1_one_userInstanceStruct;

#endif                                 /*typedef_SFc1_one_userInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_one_user_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_one_user_get_check_sum(mxArray *plhs[]);
extern void c1_one_user_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
