//
// Created by petr on 10.6.18.
//

#pragma once

/**
 * @file
 * @brief Functions related to detector and readout configuration.
 */

#include <stdbool.h>
#include <stdint.h>
#include <katherine/global.h>
#include <katherine/bmc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct katherine_device katherine_device_t;


typedef enum katherine_acquisition_mode {
    ACQUISITION_MODE_TOA_TOT        = 0,
    ACQUISITION_MODE_ONLY_TOA       = 1,
    ACQUISITION_MODE_EVENT_ITOT     = 2,
} katherine_acquisition_mode_t;


typedef struct katherine_trigger {
    bool enabled;
    char channel;
    bool use_falling_edge;
} katherine_trigger_t;


typedef union katherine_dacs {
    uint16_t array[18];

    struct {
        uint16_t Ibias_Preamp_ON;
        uint16_t Ibias_Preamp_OFF;
        uint16_t VPReamp_NCAS;
        uint16_t Ibias_Ikrum;
        uint16_t Vfbk;
        uint16_t Vthreshold_fine;
        uint16_t Vthreshold_coarse;
        uint16_t Ibias_DiscS1_ON;
        uint16_t Ibias_DiscS1_OFF;
        uint16_t Ibias_DiscS2_ON;
        uint16_t Ibias_DiscS2_OFF;
        uint16_t Ibias_PixelDAC;
        uint16_t Ibias_TPbufferIn;
        uint16_t Ibias_TPbufferOut;
        uint16_t VTP_coarse;
        uint16_t VTP_fine;
        uint16_t Ibias_CP_PLL;
        uint16_t PLL_Vcntrl;
    } named;
} katherine_dacs_t;


typedef enum katherine_phase {
    PHASE_1     = 0,
    PHASE_2     = 1,
    PHASE_4     = 2,
    PHASE_8     = 3,
    PHASE_16    = 4,
} katherine_phase_t;


typedef enum katherine_freq {
    FREQ_40     = 1,
    FREQ_80     = 2,
    FREQ_160    = 3,
} katherine_freq_t;


typedef struct katherine_config {
    katherine_bmc_t pixel_config;

    unsigned char bias_id;

    double acq_time; // ns
    int no_frames;

    float bias;
    katherine_trigger_t start_trigger;
    bool delayed_start;
    katherine_trigger_t stop_trigger;

    bool gray_disable;
    bool polarity_holes;

    katherine_phase_t phase;
    katherine_freq_t freq;
    katherine_dacs_t dacs;
} katherine_config_t;


KATHERINE_EXPORTED int
katherine_configure(katherine_device_t *, const katherine_config_t *);

KATHERINE_EXPORTED int
katherine_set_all_pixel_config(katherine_device_t *, const katherine_bmc_t *);

KATHERINE_EXPORTED int
katherine_set_acq_time(katherine_device_t *, double);

KATHERINE_EXPORTED int
katherine_set_acq_mode(katherine_device_t *, katherine_acquisition_mode_t, bool);

KATHERINE_EXPORTED int
katherine_set_no_frames(katherine_device_t *, int);

KATHERINE_EXPORTED int
katherine_set_bias(katherine_device_t *, unsigned char, float);

KATHERINE_EXPORTED int
katherine_set_seq_readout_start(katherine_device_t *, int);

KATHERINE_EXPORTED int
katherine_acquisition_setup(katherine_device_t *, const katherine_trigger_t *, bool, const katherine_trigger_t *);

typedef enum katherine_tpx3_reg {
    TPX3_REG_TEST_PULSE_METHOD      = 0,
    TPX3_REG_NUMBER_TEST_PULSES     = 1,
    TPX3_REG_OUT_BLOCK_CONFIG       = 2,
    TPX3_REG_PLL_CONFIG             = 3,
    TPX3_REG_GENERAL_CONFIG         = 4,
    TPX3_REG_SLVS_CONFIG            = 5,
    TPX3_REG_POWER_PULSING_PATTERN  = 6,
    TPX3_REG_SET_TIMER_LOW          = 7,
    TPX3_REG_SET_TIMER_MID          = 8,
    TPX3_REG_SET_TIMER_HIGH         = 9,
    TPX3_REG_SENSE_DAC_SELECTOR     = 10,
    TPX3_REG_EXT_DAC_SELECTOR       = 11,
} katherine_tpx3_reg_t;

KATHERINE_EXPORTED int
katherine_set_sensor_register(katherine_device_t *, char, int32_t);

KATHERINE_EXPORTED int
katherine_update_sensor_registers(katherine_device_t *);

KATHERINE_EXPORTED int
katherine_set_dacs(katherine_device_t *, const katherine_dacs_t *);

#ifdef __cplusplus
}
#endif
