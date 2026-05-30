#pragma once
#include "pwm.h"

typedef struct {
    pwm_settings_t pwm_settings;
    uint16_t timeout;
} animation_data_t;

extern const __flash animation_data_t *animation_ptr;

uint8_t update_animation(void);

void select_animation(void);
void select_on_animation(void);
void select_off_animation(void);
