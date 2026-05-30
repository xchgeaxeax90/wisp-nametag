#pragma once

// Lightstick L - PWM6
// Lightstick R - PWM7
// Face Bottom L - PWM3
// Face Bottom C - PWM0
// Face Bottom R - PWM1
// Eye L - PWM5 Cathode 0
// Eye R - PWM4 Cathode 0
// Face Top L - PWM5 Cathode 1
// Face Top R - PWM4 Cathode 1
// Face Top C - PWM2

#define PWM0to5_PORT PORTA
#define PWM0_bm PIN0_bm
#define PWM1_bm PIN1_bm
#define PWM2_bm PIN2_bm
#define PWM3_bm PIN3_bm
#define PWM4_bm PIN4_bm
#define PWM5_bm PIN5_bm

#define PWM67_PORT PORTD
#define PWM6_bm PIN4_bm
#define PWM7_bm PIN5_bm

#define CATHODE_PORT PORTA
#define CAT0_bi PIN6_bi
#define CAT1_bi PIN7_bi
#define CAT0_bm PIN6_bm
#define CAT1_bm PIN7_bm

#define BTN_PORT PORTC
#define BTN_bm PIN1_bm

void init_pins(void);
void enable_button_interrupt(void);
void disable_button_interrupt(void);

void disable_pins(void);
