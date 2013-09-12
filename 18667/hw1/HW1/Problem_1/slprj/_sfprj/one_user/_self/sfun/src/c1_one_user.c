/* Include files */

#include <stddef.h>
#include "blas.h"
#include "one_user_sfun.h"
#include "c1_one_user.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "one_user_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define c1_event_acquire               (0)
#define c1_event_release               (1)
#define c1_event_use                   (2)
#define c1_event_clock                 (3)
#define c1_event_a_request             (4)
#define c1_event_b_request             (5)
#define c1_event_priority              (6)
#define CALL_EVENT                     (-1)
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_Shared_Resource          ((uint8_T)1U)
#define c1_IN_acquired_1               ((uint8_T)1U)
#define c1_IN_done_2                   ((uint8_T)2U)
#define c1_IN_idle_0                   ((uint8_T)3U)
#define c1_IN_busy_2                   ((uint8_T)1U)
#define c1_b_IN_idle_0                 ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void initialize_params_c1_one_user(SFc1_one_userInstanceStruct
  *chartInstance);
static void enable_c1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void disable_c1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_one_user(SFc1_one_userInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_one_user(SFc1_one_userInstanceStruct
  *chartInstance);
static void set_sim_state_c1_one_user(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_st);
static void c1_set_sim_state_side_effects_c1_one_user
  (SFc1_one_userInstanceStruct *chartInstance);
static void finalize_c1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void sf_c1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void c1_c1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void initSimStructsc1_one_user(SFc1_one_userInstanceStruct *chartInstance);
static void registerMessagesc1_one_user(SFc1_one_userInstanceStruct
  *chartInstance);
static void c1_a_USER(SFc1_one_userInstanceStruct *chartInstance);
static void c1_Shared_Resource(SFc1_one_userInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static void c1_broadcast_acquire(SFc1_one_userInstanceStruct *chartInstance);
static void c1_broadcast_release(SFc1_one_userInstanceStruct *chartInstance);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_clock, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_c_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint8_T c1_d_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_d_tp_idle_0, const char_T *c1_identifier);
static uint8_T c1_e_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_emlrt_marshallIn(SFc1_one_userInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier);
static const mxArray *c1_g_emlrt_marshallIn(SFc1_one_userInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_one_userInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  chartInstance->c1_tp_Shared_Resource = 0U;
  chartInstance->c1_is_active_Resource = 0U;
  chartInstance->c1_is_Resource = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_Resource = 0U;
  chartInstance->c1_tp_busy_2 = 0U;
  chartInstance->c1_b_tp_idle_0 = 0U;
  chartInstance->c1_is_active_a_USER = 0U;
  chartInstance->c1_is_a_USER = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_a_USER = 0U;
  chartInstance->c1_tp_acquired_1 = 0U;
  chartInstance->c1_tp_done_2 = 0U;
  chartInstance->c1_tp_idle_0 = 0U;
  chartInstance->c1_is_active_b_USER = 0U;
  chartInstance->c1_is_b_USER = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_b_USER = 0U;
  chartInstance->c1_b_tp_acquired_1 = 0U;
  chartInstance->c1_b_tp_done_2 = 0U;
  chartInstance->c1_c_tp_idle_0 = 0U;
  chartInstance->c1_is_active_c1_one_user = 0U;
  chartInstance->c1_is_c1_one_user = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_r_in_use = 0.0;
  chartInstance->c1_tmp = 0.0;
}

static void initialize_params_c1_one_user(SFc1_one_userInstanceStruct
  *chartInstance)
{
}

static void enable_c1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_one_user(SFc1_one_userInstanceStruct
  *chartInstance)
{
  uint32_T c1_prevAniVal;
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c1_is_active_c1_one_user == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_a_USER == c1_IN_idle_0) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_a_USER == c1_IN_acquired_1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_a_USER == c1_IN_done_2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_a_USER == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_Resource == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_Resource == c1_b_IN_idle_0) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_Resource == c1_IN_busy_2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_one_user == c1_IN_Shared_Resource) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_b_USER == c1_IN_idle_0) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_b_USER == c1_IN_done_2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_b_USER == c1_IN_acquired_1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_b_USER == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c1_one_user(SFc1_one_userInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  uint8_T c1_c_hoistedGlobal;
  uint8_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  uint8_T c1_d_hoistedGlobal;
  uint8_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  uint8_T c1_e_hoistedGlobal;
  uint8_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  uint8_T c1_f_hoistedGlobal;
  uint8_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  uint8_T c1_g_hoistedGlobal;
  uint8_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  uint8_T c1_h_hoistedGlobal;
  uint8_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  uint8_T c1_i_hoistedGlobal;
  uint8_T c1_i_u;
  const mxArray *c1_j_y = NULL;
  uint8_T c1_j_hoistedGlobal;
  uint8_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(10), FALSE);
  c1_hoistedGlobal = chartInstance->c1_r_in_use;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = chartInstance->c1_tmp;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = chartInstance->c1_is_active_c1_one_user;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = chartInstance->c1_is_active_a_USER;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = chartInstance->c1_is_active_Resource;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = chartInstance->c1_is_active_b_USER;
  c1_f_u = c1_f_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = chartInstance->c1_is_c1_one_user;
  c1_g_u = c1_g_hoistedGlobal;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_h_hoistedGlobal = chartInstance->c1_is_a_USER;
  c1_h_u = c1_h_hoistedGlobal;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_i_hoistedGlobal = chartInstance->c1_is_Resource;
  c1_i_u = c1_i_hoistedGlobal;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_j_hoistedGlobal = chartInstance->c1_is_b_USER;
  c1_j_u = c1_j_hoistedGlobal;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_one_user(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  c1_u = sf_mex_dup(c1_st);
  chartInstance->c1_r_in_use = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 0)), "r_in_use");
  chartInstance->c1_tmp = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 1)), "tmp");
  chartInstance->c1_is_active_c1_one_user = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 2)), "is_active_c1_one_user");
  chartInstance->c1_is_active_a_USER = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 3)), "is_active_a_USER");
  chartInstance->c1_is_active_Resource = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 4)), "is_active_Resource");
  chartInstance->c1_is_active_b_USER = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 5)), "is_active_b_USER");
  chartInstance->c1_is_c1_one_user = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 6)), "is_c1_one_user");
  chartInstance->c1_is_a_USER = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 7)), "is_a_USER");
  chartInstance->c1_is_Resource = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 8)), "is_Resource");
  chartInstance->c1_is_b_USER = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 9)), "is_b_USER");
  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 10)), "setSimStateSideEffectsInfo"), TRUE);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_one_user(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_one_user
  (SFc1_one_userInstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    if (chartInstance->c1_is_c1_one_user == c1_IN_Shared_Resource) {
      chartInstance->c1_tp_Shared_Resource = 1U;
    } else {
      chartInstance->c1_tp_Shared_Resource = 0U;
    }

    if (chartInstance->c1_is_active_a_USER == 1U) {
      chartInstance->c1_tp_a_USER = 1U;
    } else {
      chartInstance->c1_tp_a_USER = 0U;
    }

    if (chartInstance->c1_is_a_USER == c1_IN_acquired_1) {
      chartInstance->c1_tp_acquired_1 = 1U;
    } else {
      chartInstance->c1_tp_acquired_1 = 0U;
    }

    if (chartInstance->c1_is_a_USER == c1_IN_done_2) {
      chartInstance->c1_tp_done_2 = 1U;
    } else {
      chartInstance->c1_tp_done_2 = 0U;
    }

    if (chartInstance->c1_is_a_USER == c1_IN_idle_0) {
      chartInstance->c1_tp_idle_0 = 1U;
    } else {
      chartInstance->c1_tp_idle_0 = 0U;
    }

    if (chartInstance->c1_is_active_Resource == 1U) {
      chartInstance->c1_tp_Resource = 1U;
    } else {
      chartInstance->c1_tp_Resource = 0U;
    }

    if (chartInstance->c1_is_Resource == c1_IN_busy_2) {
      chartInstance->c1_tp_busy_2 = 1U;
    } else {
      chartInstance->c1_tp_busy_2 = 0U;
    }

    if (chartInstance->c1_is_Resource == c1_b_IN_idle_0) {
      chartInstance->c1_b_tp_idle_0 = 1U;
    } else {
      chartInstance->c1_b_tp_idle_0 = 0U;
    }

    if (chartInstance->c1_is_active_b_USER == 1U) {
      chartInstance->c1_tp_b_USER = 1U;
    } else {
      chartInstance->c1_tp_b_USER = 0U;
    }

    if (chartInstance->c1_is_b_USER == c1_IN_acquired_1) {
      chartInstance->c1_b_tp_acquired_1 = 1U;
    } else {
      chartInstance->c1_b_tp_acquired_1 = 0U;
    }

    if (chartInstance->c1_is_b_USER == c1_IN_done_2) {
      chartInstance->c1_b_tp_done_2 = 1U;
    } else {
      chartInstance->c1_b_tp_done_2 = 0U;
    }

    if (chartInstance->c1_is_b_USER == c1_IN_idle_0) {
      chartInstance->c1_c_tp_idle_0 = 1U;
    } else {
      chartInstance->c1_c_tp_idle_0 = 0U;
    }

    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_c1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
  real_T *c1_clock;
  real_T *c1_a_request;
  real_T *c1_b_request;
  real_T *c1_priority;
  c1_priority = (real_T *)*(ssGetInputPortSignalPtrs(chartInstance->S, 0) + 3);
  c1_b_request = (real_T *)*(ssGetInputPortSignalPtrs(chartInstance->S, 0) + 2);
  c1_a_request = (real_T *)*(ssGetInputPortSignalPtrs(chartInstance->S, 0) + 1);
  c1_clock = (real_T *)*(ssGetInputPortSignalPtrs(chartInstance->S, 0) + 0);
  c1_set_sim_state_side_effects_c1_one_user(chartInstance);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_r_in_use, 0U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_tmp, 1U);
  if (*c1_clock == 1.0) {
    chartInstance->c1_sfEvent = c1_event_clock;
    _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c1_event_clock,
                 chartInstance->c1_sfEvent);
    c1_c1_one_user(chartInstance);
    _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c1_event_clock,
                 chartInstance->c1_sfEvent);
  }

  if (*c1_a_request == 1.0) {
    chartInstance->c1_sfEvent = c1_event_a_request;
    _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c1_event_a_request,
                 chartInstance->c1_sfEvent);
    c1_c1_one_user(chartInstance);
    _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c1_event_a_request,
                 chartInstance->c1_sfEvent);
  }

  if (*c1_b_request == 1.0) {
    chartInstance->c1_sfEvent = c1_event_b_request;
    _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c1_event_b_request,
                 chartInstance->c1_sfEvent);
    c1_c1_one_user(chartInstance);
    _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c1_event_b_request,
                 chartInstance->c1_sfEvent);
  }

  if (*c1_priority != 0.0) {
    chartInstance->c1_sfEvent = c1_event_priority;
    _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c1_event_priority,
                 chartInstance->c1_sfEvent);
    c1_c1_one_user(chartInstance);
    _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c1_event_priority,
                 chartInstance->c1_sfEvent);
  }

  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_one_userMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_c1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  if (chartInstance->c1_is_active_c1_one_user == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_active_c1_one_user = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_one_user = c1_IN_Shared_Resource;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_Shared_Resource = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_active_a_USER = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_a_USER = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_a_USER = c1_IN_idle_0;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_idle_0 = 1U;
    chartInstance->c1_is_active_Resource = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_Resource = 1U;
    if (chartInstance->c1_is_Resource == c1_b_IN_idle_0) {
    } else {
      chartInstance->c1_is_Resource = c1_b_IN_idle_0;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
      chartInstance->c1_b_tp_idle_0 = 1U;
      chartInstance->c1_r_in_use = 0.0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_r_in_use, 0U);
    }

    chartInstance->c1_is_active_b_USER = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_b_USER = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_b_USER = c1_IN_idle_0;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
    chartInstance->c1_c_tp_idle_0 = 1U;
  } else if (chartInstance->c1_is_c1_one_user != c1_IN_Shared_Resource) {
  } else {
    c1_Shared_Resource(chartInstance);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_one_user(SFc1_one_userInstanceStruct *chartInstance)
{
}

static void registerMessagesc1_one_user(SFc1_one_userInstanceStruct
  *chartInstance)
{
}

static void c1_a_USER(SFc1_one_userInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  real_T c1_d0;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  boolean_T c1_e_out;
  boolean_T c1_f_out;
  boolean_T c1_g_out;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
  switch (chartInstance->c1_is_a_USER) {
   case c1_IN_acquired_1:
    CV_STATE_EVAL(4, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c1_sfEvent);
    c1_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0, _sfTime_ >
                chartInstance->c1_tmp != 0U, chartInstance->c1_sfEvent)) != 0);
    if (c1_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_acquired_1 = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_a_USER = c1_IN_done_2;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_done_2 = 1U;
      sf_mex_import_named("exprnd", sf_mex_call_debug("exprnd", 1U, 1U, 6, 10.0),
                          &c1_d0, 0, 0, 0U, 0, 0U, 0);
      chartInstance->c1_tmp = _sfTime_ + c1_d0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_tmp, 1U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_done_2:
    CV_STATE_EVAL(4, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c1_sfEvent);
    c1_b_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0, _sfTime_ >
      chartInstance->c1_tmp != 0U, chartInstance->c1_sfEvent)) != 0);
    guard3 = FALSE;
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_done_2 = 0U;
      chartInstance->c1_is_a_USER = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 2U,
                   chartInstance->c1_sfEvent);
      c1_broadcast_release(chartInstance);
      if (chartInstance->c1_is_a_USER == c1_IN_NO_ACTIVE_CHILD) {
        if (chartInstance->c1_is_active_a_USER == 0U) {
          _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
        }
      } else {
        _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      }

      if (chartInstance->c1_is_a_USER == c1_IN_NO_ACTIVE_CHILD) {
        if (chartInstance->c1_is_active_a_USER == 0U) {
          _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
        } else {
          chartInstance->c1_is_a_USER = c1_IN_idle_0;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_idle_0 = 1U;
          guard3 = TRUE;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                   chartInstance->c1_sfEvent);
      guard3 = TRUE;
    }

    if (guard3 == TRUE) {
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c1_sfEvent);
    }
    break;

   case c1_IN_idle_0:
    CV_STATE_EVAL(4, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U, chartInstance->c1_sfEvent);
    c1_c_out = (CV_TRANSITION_EVAL(0U, (int32_T)_SFD_CCP_CALL(0U, 0,
      chartInstance->c1_sfEvent == c1_event_a_request != 0U,
      chartInstance->c1_sfEvent)) != 0);
    guard1 = FALSE;
    guard2 = FALSE;
    if (c1_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                   chartInstance->c1_sfEvent);
      c1_d_out = (CV_TRANSITION_EVAL(8U, (int32_T)_SFD_CCP_CALL(8U, 0,
        chartInstance->c1_r_in_use == 1.0 != 0U, chartInstance->c1_sfEvent)) !=
                  0);
      if (c1_d_out) {
        if (_SFD_TRANSITION_CONFLICT_CHECK_ENABLED()) {
          unsigned int transitionList[2];
          unsigned int numTransitions = 1;
          transitionList[0] = 8;
          _SFD_TRANSITION_CONFLICT_CHECK_BEGIN();
          c1_e_out = (chartInstance->c1_r_in_use == 0.0);
          if (c1_e_out) {
            transitionList[numTransitions] = 7;
            numTransitions++;
          }

          _SFD_TRANSITION_CONFLICT_CHECK_END();
          if (numTransitions > 1) {
            _SFD_TRANSITION_CONFLICT(&(transitionList[0]),numTransitions);
          }
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_idle_0 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_a_USER = c1_IN_idle_0;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_idle_0 = 1U;
        guard1 = TRUE;
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                     chartInstance->c1_sfEvent);
        c1_f_out = (CV_TRANSITION_EVAL(7U, (int32_T)_SFD_CCP_CALL(7U, 0,
          chartInstance->c1_r_in_use == 0.0 != 0U, chartInstance->c1_sfEvent))
                    != 0);
        if (c1_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                       chartInstance->c1_sfEvent);
          c1_g_out = (CV_TRANSITION_EVAL(15U, (int32_T)_SFD_CCP_CALL(15U, 0,
            chartInstance->c1_sfEvent == c1_event_priority != 0U,
            chartInstance->c1_sfEvent)) != 0);
          if (c1_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
            chartInstance->c1_tp_idle_0 = 0U;
            chartInstance->c1_is_a_USER = c1_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 15U,
                         chartInstance->c1_sfEvent);
            c1_broadcast_acquire(chartInstance);
            if (chartInstance->c1_is_a_USER == c1_IN_NO_ACTIVE_CHILD) {
              if (chartInstance->c1_is_active_a_USER == 0U) {
                _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 15U,
                             chartInstance->c1_sfEvent);
              }
            } else {
              _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 15U,
                           chartInstance->c1_sfEvent);
            }

            if (chartInstance->c1_is_a_USER == c1_IN_NO_ACTIVE_CHILD) {
              if (chartInstance->c1_is_active_a_USER == 0U) {
                _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 15U,
                             chartInstance->c1_sfEvent);
              } else {
                chartInstance->c1_is_a_USER = c1_IN_acquired_1;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
                chartInstance->c1_tp_acquired_1 = 1U;
                chartInstance->c1_tmp = _sfTime_ + 1.0;
                _SFD_DATA_RANGE_CHECK(chartInstance->c1_tmp, 1U);
                guard1 = TRUE;
              }
            } else {
              _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 15U,
                           chartInstance->c1_sfEvent);
            }
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
            chartInstance->c1_tp_idle_0 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
            chartInstance->c1_is_a_USER = c1_IN_idle_0;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
            chartInstance->c1_tp_idle_0 = 1U;
            guard1 = TRUE;
          }
        } else {
          guard2 = TRUE;
        }
      }
    } else {
      guard2 = TRUE;
    }

    if (guard2 == TRUE) {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                   chartInstance->c1_sfEvent);
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c1_sfEvent);
    }
    break;

   default:
    CV_STATE_EVAL(4, 0, 0);
    chartInstance->c1_is_a_USER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
}

static void c1_Shared_Resource(SFc1_one_userInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  real_T c1_d1;
  boolean_T c1_d_out;
  boolean_T c1_e_out;
  boolean_T c1_f_out;
  boolean_T c1_g_out;
  boolean_T c1_h_out;
  boolean_T c1_i_out;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  if (chartInstance->c1_is_active_a_USER == 0U) {
  } else {
    c1_a_USER(chartInstance);
  }

  if (chartInstance->c1_is_active_Resource == 0U) {
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
    switch (chartInstance->c1_is_Resource) {
     case c1_IN_busy_2:
      CV_STATE_EVAL(1, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                   chartInstance->c1_sfEvent);
      c1_out = (CV_TRANSITION_EVAL(6U, (int32_T)_SFD_CCP_CALL(6U, 0,
                  chartInstance->c1_sfEvent == c1_event_release != 0U,
                  chartInstance->c1_sfEvent)) != 0);
      if (c1_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_busy_2 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_Resource = c1_b_IN_idle_0;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
        chartInstance->c1_b_tp_idle_0 = 1U;
        chartInstance->c1_r_in_use = 0.0;
        _SFD_DATA_RANGE_CHECK(chartInstance->c1_r_in_use, 0U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c1_sfEvent);
      break;

     case c1_b_IN_idle_0:
      CV_STATE_EVAL(1, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                   chartInstance->c1_sfEvent);
      c1_b_out = (CV_TRANSITION_EVAL(5U, (int32_T)_SFD_CCP_CALL(5U, 0,
        chartInstance->c1_sfEvent == c1_event_acquire != 0U,
        chartInstance->c1_sfEvent)) != 0);
      if (c1_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
        chartInstance->c1_b_tp_idle_0 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_Resource = c1_IN_busy_2;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_busy_2 = 1U;
        chartInstance->c1_r_in_use = 1.0;
        _SFD_DATA_RANGE_CHECK(chartInstance->c1_r_in_use, 0U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c1_sfEvent);
      break;

     default:
      CV_STATE_EVAL(1, 0, 0);
      chartInstance->c1_is_Resource = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_b_USER == 0U) {
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
    switch (chartInstance->c1_is_b_USER) {
     case c1_IN_acquired_1:
      CV_STATE_EVAL(8, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                   chartInstance->c1_sfEvent);
      c1_c_out = (CV_TRANSITION_EVAL(12U, (int32_T)_SFD_CCP_CALL(12U, 0,
        _sfTime_ > chartInstance->c1_tmp != 0U, chartInstance->c1_sfEvent)) != 0);
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        chartInstance->c1_b_tp_acquired_1 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_b_USER = c1_IN_done_2;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        chartInstance->c1_b_tp_done_2 = 1U;
        sf_mex_import_named("exprnd", sf_mex_call_debug("exprnd", 1U, 1U, 6,
          10.0), &c1_d1, 0, 0, 0U, 0, 0U, 0);
        chartInstance->c1_tmp = _sfTime_ + c1_d1;
        _SFD_DATA_RANGE_CHECK(chartInstance->c1_tmp, 1U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                     chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_done_2:
      CV_STATE_EVAL(8, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                   chartInstance->c1_sfEvent);
      c1_d_out = (CV_TRANSITION_EVAL(10U, (int32_T)_SFD_CCP_CALL(10U, 0,
        _sfTime_ > chartInstance->c1_tmp != 0U, chartInstance->c1_sfEvent)) != 0);
      guard3 = FALSE;
      if (c1_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        chartInstance->c1_b_tp_done_2 = 0U;
        chartInstance->c1_is_b_USER = c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 10U,
                     chartInstance->c1_sfEvent);
        c1_broadcast_release(chartInstance);
        if (chartInstance->c1_is_b_USER == c1_IN_NO_ACTIVE_CHILD) {
          if (chartInstance->c1_is_active_b_USER == 0U) {
            _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
          }
        } else {
          _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        }

        if (chartInstance->c1_is_b_USER == c1_IN_NO_ACTIVE_CHILD) {
          if (chartInstance->c1_is_active_b_USER == 0U) {
            _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
          } else {
            chartInstance->c1_is_b_USER = c1_IN_idle_0;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
            chartInstance->c1_c_tp_idle_0 = 1U;
            guard3 = TRUE;
          }
        } else {
          _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        }
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                     chartInstance->c1_sfEvent);
        guard3 = TRUE;
      }

      if (guard3 == TRUE) {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c1_sfEvent);
      }
      break;

     case c1_IN_idle_0:
      CV_STATE_EVAL(8, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                   chartInstance->c1_sfEvent);
      c1_e_out = (CV_TRANSITION_EVAL(13U, (int32_T)_SFD_CCP_CALL(13U, 0,
        chartInstance->c1_sfEvent == c1_event_b_request != 0U,
        chartInstance->c1_sfEvent)) != 0);
      guard1 = FALSE;
      guard2 = FALSE;
      if (c1_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                     chartInstance->c1_sfEvent);
        c1_f_out = (CV_TRANSITION_EVAL(14U, (int32_T)_SFD_CCP_CALL(14U, 0,
          chartInstance->c1_r_in_use == 1.0 != 0U, chartInstance->c1_sfEvent))
                    != 0);
        if (c1_f_out) {
          if (_SFD_TRANSITION_CONFLICT_CHECK_ENABLED()) {
            unsigned int transitionList[2];
            unsigned int numTransitions = 1;
            transitionList[0] = 14;
            _SFD_TRANSITION_CONFLICT_CHECK_BEGIN();
            c1_g_out = (chartInstance->c1_r_in_use == 0.0);
            if (c1_g_out) {
              transitionList[numTransitions] = 11;
              numTransitions++;
            }

            _SFD_TRANSITION_CONFLICT_CHECK_END();
            if (numTransitions > 1) {
              _SFD_TRANSITION_CONFLICT(&(transitionList[0]),numTransitions);
            }
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
          chartInstance->c1_c_tp_idle_0 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_b_USER = c1_IN_idle_0;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
          chartInstance->c1_c_tp_idle_0 = 1U;
          guard1 = TRUE;
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                       chartInstance->c1_sfEvent);
          c1_h_out = (CV_TRANSITION_EVAL(11U, (int32_T)_SFD_CCP_CALL(11U, 0,
            chartInstance->c1_r_in_use == 0.0 != 0U, chartInstance->c1_sfEvent))
                      != 0);
          if (c1_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U,
                         chartInstance->c1_sfEvent);
            c1_i_out = (CV_TRANSITION_EVAL(18U, (int32_T)_SFD_CCP_CALL(18U, 0,
              chartInstance->c1_sfEvent == c1_event_priority != 0U,
              chartInstance->c1_sfEvent)) != 0);
            if (c1_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c1_sfEvent);
              chartInstance->c1_c_tp_idle_0 = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
              chartInstance->c1_is_b_USER = c1_IN_idle_0;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
              chartInstance->c1_c_tp_idle_0 = 1U;
              guard1 = TRUE;
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c1_sfEvent);
              chartInstance->c1_c_tp_idle_0 = 0U;
              chartInstance->c1_is_b_USER = c1_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
              _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 17U,
                           chartInstance->c1_sfEvent);
              c1_broadcast_acquire(chartInstance);
              if (chartInstance->c1_is_b_USER == c1_IN_NO_ACTIVE_CHILD) {
                if (chartInstance->c1_is_active_b_USER == 0U) {
                  _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 17U,
                               chartInstance->c1_sfEvent);
                }
              } else {
                _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 17U,
                             chartInstance->c1_sfEvent);
              }

              if (chartInstance->c1_is_b_USER == c1_IN_NO_ACTIVE_CHILD) {
                if (chartInstance->c1_is_active_b_USER == 0U) {
                  _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 17U,
                               chartInstance->c1_sfEvent);
                } else {
                  chartInstance->c1_is_b_USER = c1_IN_acquired_1;
                  _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
                  chartInstance->c1_b_tp_acquired_1 = 1U;
                  chartInstance->c1_tmp = _sfTime_ + 1.0;
                  _SFD_DATA_RANGE_CHECK(chartInstance->c1_tmp, 1U);
                  guard1 = TRUE;
                }
              } else {
                _SFD_CT_CALL(TRANSITION_INACTIVE_TAG, 17U,
                             chartInstance->c1_sfEvent);
              }
            }
          } else {
            guard2 = TRUE;
          }
        }
      } else {
        guard2 = TRUE;
      }

      if (guard2 == TRUE) {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                     chartInstance->c1_sfEvent);
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c1_sfEvent);
      }
      break;

     default:
      CV_STATE_EVAL(8, 0, 0);
      chartInstance->c1_is_b_USER = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

const mxArray *sf_c1_one_user_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c1_nameCaptureInfo;
}

static void c1_broadcast_acquire(SFc1_one_userInstanceStruct *chartInstance)
{
  int32_T c1_previousEvent;
  c1_previousEvent = chartInstance->c1_sfEvent;
  chartInstance->c1_sfEvent = c1_event_acquire;
  _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c1_event_acquire,
               chartInstance->c1_sfEvent);
  c1_c1_one_user(chartInstance);
  _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c1_event_acquire,
               chartInstance->c1_sfEvent);
  chartInstance->c1_sfEvent = c1_previousEvent;
}

static void c1_broadcast_release(SFc1_one_userInstanceStruct *chartInstance)
{
  int32_T c1_previousEvent;
  c1_previousEvent = chartInstance->c1_sfEvent;
  chartInstance->c1_sfEvent = c1_event_release;
  _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c1_event_release,
               chartInstance->c1_sfEvent);
  c1_c1_one_user(chartInstance);
  _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c1_event_release,
               chartInstance->c1_sfEvent);
  chartInstance->c1_sfEvent = c1_previousEvent;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_clock, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_clock), &c1_thisId);
  sf_mex_destroy(&c1_clock);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_clock;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)chartInstanceVoid;
  c1_clock = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_clock), &c1_thisId);
  sf_mex_destroy(&c1_clock);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_c_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i0, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  uint8_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint8_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static uint8_T c1_d_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_d_tp_idle_0, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_tp_idle_0),
    &c1_thisId);
  sf_mex_destroy(&c1_d_tp_idle_0);
  return c1_y;
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_one_userInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_d_tp_idle_0;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y;
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)chartInstanceVoid;
  c1_d_tp_idle_0 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_tp_idle_0),
    &c1_thisId);
  sf_mex_destroy(&c1_d_tp_idle_0);
  *(uint8_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_emlrt_marshallIn(SFc1_one_userInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  sf_mex_assign(&c1_y, c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), FALSE);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_g_emlrt_marshallIn(SFc1_one_userInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), FALSE);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_one_userInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_one_user_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3589704036U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3332845214U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1568366440U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3067394299U);
}

mxArray *sf_c1_one_user_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("dr6cSv3cl7JrVQeXmeOgAC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_one_user_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_one_user(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[3],M[20],T\"r_in_use\",},{M[3],M[21],T\"tmp\",},{M[8],M[0],T\"is_active_c1_one_user\",},{M[8],M[5],T\"is_active_a_USER\",},{M[8],M[6],T\"is_active_Resource\",},{M[8],M[55],T\"is_active_b_USER\",},{M[9],M[0],T\"is_c1_one_user\",},{M[9],M[5],T\"is_a_USER\",},{M[9],M[6],T\"is_Resource\",},{M[9],M[55],T\"is_b_USER\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 10, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_one_user_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_one_userInstanceStruct *chartInstance;
    chartInstance = (SFc1_one_userInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _one_userMachineNumber_,
           1,
           12,
           19,
           2,
           7,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_one_userMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_one_userMachineNumber_,
             chartInstance->chartNumber,0);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _one_userMachineNumber_,
            chartInstance->chartNumber,
            7,
            7,
            7);
          _SFD_SET_DATA_PROPS(0,0,0,0,"r_in_use");
          _SFD_SET_DATA_PROPS(1,0,0,0,"tmp");
          _SFD_EVENT_SCOPE(0,0);
          _SFD_EVENT_SCOPE(1,0);
          _SFD_EVENT_SCOPE(2,0);
          _SFD_EVENT_SCOPE(3,1);
          _SFD_EVENT_SCOPE(4,1);
          _SFD_EVENT_SCOPE(5,1);
          _SFD_EVENT_SCOPE(6,1);
          _SFD_STATE_INFO(0,1,0);
          _SFD_STATE_INFO(1,0,1);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,1);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,1);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,0);
          _SFD_CH_SUBSTATE_COUNT(1);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,4);
          _SFD_ST_SUBSTATE_INDEX(0,1,1);
          _SFD_ST_SUBSTATE_INDEX(0,2,8);
          _SFD_ST_SUBSTATE_COUNT(4,3);
          _SFD_ST_SUBSTATE_INDEX(4,0,5);
          _SFD_ST_SUBSTATE_INDEX(4,1,6);
          _SFD_ST_SUBSTATE_INDEX(4,2,7);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(1,2);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(8,3);
          _SFD_ST_SUBSTATE_INDEX(8,0,9);
          _SFD_ST_SUBSTATE_INDEX(8,1,10);
          _SFD_ST_SUBSTATE_INDEX(8,2,11);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
        }

        _SFD_CV_INIT_CHART(1,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 9 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(0,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 7 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 7 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(12,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 9 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(13,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(11,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 8 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(15,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 8 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(18,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_TRANS_COV_WTS(3,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(3,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(2,0,1,0,1);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          _SFD_TRANS_COV_MAPS(2,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              1,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(1,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          _SFD_TRANS_COV_MAPS(1,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(0,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 9 };

          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(8,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          _SFD_TRANS_COV_MAPS(8,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(7,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          _SFD_TRANS_COV_MAPS(7,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(6,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 7 };

          _SFD_TRANS_COV_MAPS(6,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(5,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 7 };

          _SFD_TRANS_COV_MAPS(5,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(4,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(4,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(9,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(9,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(10,0,1,0,1);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          _SFD_TRANS_COV_MAPS(10,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              1,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(12,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 6 };

          _SFD_TRANS_COV_MAPS(12,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(13,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 9 };

          _SFD_TRANS_COV_MAPS(13,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(14,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          _SFD_TRANS_COV_MAPS(14,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(11,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 12 };

          _SFD_TRANS_COV_MAPS(11,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(15,0,1,0,1);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 8 };

          _SFD_TRANS_COV_MAPS(15,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              1,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(16,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(16,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(17,0,0,0,1);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(17,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(18,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 8 };

          _SFD_TRANS_COV_MAPS(18,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, &chartInstance->c1_r_in_use);
        _SFD_SET_DATA_VALUE_PTR(1U, &chartInstance->c1_tmp);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _one_userMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "IaMFycqbMGef0CZjVYkNH";
}

static void sf_opaque_initialize_c1_one_user(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_one_userInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
  initialize_c1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_one_user(void *chartInstanceVar)
{
  enable_c1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_one_user(void *chartInstanceVar)
{
  disable_c1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_one_user(void *chartInstanceVar)
{
  sf_c1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_one_user(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_one_user((SFc1_one_userInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_one_user();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_one_user(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_one_user();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_one_user((SFc1_one_userInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_one_user(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_one_user(S);
}

static void sf_opaque_set_sim_state_c1_one_user(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_one_user(S, st);
}

static void sf_opaque_terminate_c1_one_user(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_one_userInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_one_user_optimization_info();
    }

    finalize_c1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_one_user((SFc1_one_userInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_one_user(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_one_user((SFc1_one_userInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_one_user(SimStruct *S)
{
  ssSetNeedAbsoluteTime(S,1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_one_user_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
    }

    ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=0; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1827884372U));
  ssSetChecksum1(S,(3741130737U));
  ssSetChecksum2(S,(3316340500U));
  ssSetChecksum3(S,(1842611755U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_one_user(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_one_user(SimStruct *S)
{
  SFc1_one_userInstanceStruct *chartInstance;
  chartInstance = (SFc1_one_userInstanceStruct *)utMalloc(sizeof
    (SFc1_one_userInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_one_userInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_one_user;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_one_user;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_one_user;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_one_user;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_one_user;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_one_user;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_one_user;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_one_user;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_one_user;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_one_user;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_one_user;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_one_user_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_one_user(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_one_user(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_one_user(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_one_user_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
