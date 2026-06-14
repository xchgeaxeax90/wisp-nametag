#include "pwm.h"
#include "fw_hal.h"
#include "animation.h"

#define PWM_CCMR \
    (0x0 << 0) |                  /* CCS = 0 - output */ \
    (0x1 << 2) |                  /* Preload enable - required for PWM */ \
    (PWM_OutputMode_PWM_HighIfLess << 4) /* set OCx high if counter is less than compare match register */ 



/* Init PWM2 P/N, which outputs on: P1.2 - PWM2P P1.3 - PWM2N */
void setup_pwm(void){
    SFRX_ON();
    /* Disable all port outputs, equivalent to SetPortState(HAL_State_Off)*/
    PWMA_CCER1 = 0;
    PWMA_CCER2 = 0;
    PWMB_CCER1 = 0;
    PWMB_CCER2 = 0;
    /* Set direction for all outputs -
       SetPortDirection(PortDirOut);
       ConfigOutputMode(LowIfLess);
       SetComparePreload(ON);*/
    PWMA_CCMR1 = PWM_CCMR;
    PWMA_CCMR2 = PWM_CCMR;
    PWMA_CCMR3 = PWM_CCMR;
    PWMA_CCMR4 = PWM_CCMR;
    PWMB_CCMR1 = PWM_CCMR;
    PWMB_CCMR2 = PWM_CCMR;
    PWMB_CCMR3 = PWM_CCMR;
    PWMB_CCMR4 = PWM_CCMR;

    /* Enable the compare outputs for all pwm ports on PWMA/B
     Equivalent to SetPortState(ON), SetPortPolar(High)*/
    PWMA_CCER1 = 0x11;
    PWMA_CCER2 = 0x11;
    PWMB_CCER1 = 0x11;
    PWMB_CCER2 = 0x11;

    /* Set prescaler to 0 */
    PWMA_PSCRH = 0;
    PWMA_PSCRL = 0;
    PWMB_PSCRH = 0;
    PWMB_PSCRL = 0;

    /* Set auto reload register/period to 0xff */
    PWMA_ARRH = 0x0;
    PWMB_ARRH = 0x0;
    PWMA_ARRL = 0xff;
    PWMB_ARRL = 0xff;

    /* Set Capture Compare registers to 0 */
    PWMA_CCR1H = 0;
    PWMA_CCR1L = 0;
    PWMA_CCR2H = 0;
    PWMA_CCR2L = 0;
    PWMA_CCR3H = 0;
    PWMA_CCR3L = 0;
    PWMA_CCR4H = 0;
    PWMA_CCR4L = 0;

    PWMB_CCR5H = 0;
    PWMB_CCR5L = 0;
    PWMB_CCR6H = 0;
    PWMB_CCR6L = 0;
    PWMB_CCR7H = 0;
    PWMB_CCR7L = 0;
    PWMB_CCR8H = 0;
    PWMB_CCR8L = 0;

    /* Set all PWMB ports to alternate pin selection 1 */
    PWMB_PS = 0x55;

    /* Enable all output pins on both PWMs */
    PWMA_ENO = PWM_Pin_1 | PWM_Pin_2 | PWM_Pin_3 | PWM_Pin_4;
    PWMB_ENO = PWM_Pin_1 | PWM_Pin_2 | PWM_Pin_3 | PWM_Pin_4;

    /* Disable the brake - enable PWM */
    PWMA_BKR |= 1<<7;
    PWMB_BKR |= 1<<7;

    /* Set CR1 to enable the counter */
    PWMA_CR1 =
        1 << 7 |                /* Enable auto reload preload */
        0 << 5 |                /* Edge aligned */
        0 << 4 |                /* Count up */
        0 << 3 |                /* Continuous Pulses */
        1 << 0;                 /* Enable counter */
    PWMB_CR1 =
        1 << 7 |                /* Enable auto reload preload */
        0 << 5 |                /* Edge aligned */
        0 << 4 |                /* Count up */
        0 << 3 |                /* Continuous Pulses */
        1 << 0;                 /* Enable counter */


    SFRX_OFF();
}


void stop_pwm(void){
    SFRX_ON();
    PWMA_CR1 = 0;
    PWMB_CR1 = 0;
    PWMA_BKR = 0;
    PWMB_BKR = 0;
    PWMA_ENO = 0;
    PWMB_ENO = 0;
    SFRX_OFF();
}

uint8_t brightness = 0x40;

static uint8_t scale_pwm(uint8_t pwm_in){
    uint16_t product = pwm_in * brightness;
    return product >> 8;
}

extern const __CODE animation_data_t *animation_ptr;

void write_pwm(void){
    uint8_t light_l = scale_pwm(animation_ptr->pwm_settings.light_l);
    uint8_t light_r = scale_pwm(animation_ptr->pwm_settings.light_r);
    uint8_t face_bot_l = scale_pwm(animation_ptr->pwm_settings.face_bot_l);
    uint8_t face_bot_c = scale_pwm(animation_ptr->pwm_settings.face_bot_c);
    uint8_t face_bot_r = scale_pwm(animation_ptr->pwm_settings.face_bot_r);
    uint8_t face_top_c = scale_pwm(animation_ptr->pwm_settings.face_top_c);
    SFRX_ON();
    PWMA_CCR2L = light_l;
    PWMA_CCR3L = face_top_c;
    PWMB_CCR5L = face_bot_l;
    PWMB_CCR6L = face_bot_c;
    PWMB_CCR7L = light_r;
    PWMB_CCR8L = face_bot_r;
    SFRX_OFF();
}

void write_pwm_multiplexed(__idata uint8_t eye_sel) {
    uint8_t face_eye_l = 0;
    uint8_t face_eye_r = 0;
    if(eye_sel){
        face_eye_l = animation_ptr->pwm_settings.eye_l;
        face_eye_r = animation_ptr->pwm_settings.eye_r;
    } else {
        face_eye_l = animation_ptr->pwm_settings.face_top_l;
        face_eye_r = animation_ptr->pwm_settings.face_top_r;
    }
    face_eye_l = scale_pwm(face_eye_l);
    face_eye_r = scale_pwm(face_eye_r);
    SFRX_ON();
    PWMA_CCR1L = face_eye_l;
    PWMA_CCR4L = face_eye_r;
    SFRX_OFF();
}

void select_brightness(void) {
    if(brightness <= 0x8)
	brightness = 0xff;
    else
	brightness = brightness >> 1;
}
