#pragma once
#include <stdint.h>
#include "fw_hal.h"

void setup_pwm(void);
void stop_pwm(void);

typedef struct _pwm_settings_t {
    uint8_t light_l;
    uint8_t light_r;
    uint8_t eye_l;
    uint8_t eye_r;
    uint8_t face_bot_l;
    uint8_t face_bot_c;
    uint8_t face_bot_r;
    uint8_t face_top_l;
    uint8_t face_top_c;
    uint8_t face_top_r;
} pwm_settings_t;

void write_pwm(void);
void write_pwm_multiplexed(__idata uint8_t eye_sel);
void select_brightness(void);
