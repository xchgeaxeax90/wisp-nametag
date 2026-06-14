#include "fw_hal.h"
#include "pins.h"
#include "pwm.h"
#include "timer.h"
#include "animation.h"
#include "state_machine.h"
#include "debug.h"

/* TODO determine if we actually need the button state bit */
volatile __idata uint16_t button_timeout = 0;
volatile __BIT button_state = 0;
void poll_button(void){
    /* Button is active low */
    if(!(P3 & BUTTON_PIN)){
        if(!button_state){
            button_timeout = 0;
        } else {
            button_timeout += 1;
        }
        button_state = 1;
    } else {
        button_state = 0;
    }
}

/* Selects which cathode to enable */

// Called periodically by TCB0 to update the multiplexing for the eyes and top LEDs

static volatile __BIT eye_en = 0;
INTERRUPT_USING(Timer2_Routine, EXTI_VectTimer2, 1) {
    uint8_t p_sw2_save = P_SW2;
    poll_button();
    /* Disable cathodes */
    if(update_animation()){

        write_pwm();
    }
    /* Disable both cathodes between PWM setting update and when the
    setting is loaded to the capture compare unit */
    CATHODE0_PIN_BIT = SET;
    CATHODE1_PIN_BIT = SET;
    write_pwm_multiplexed(eye_en);
    /* Enable the interrupt for PWM overflow to synchronize cathode updates to PWM period */

    /* Enable the PWM update interrupt so the cathode setting can be updated synchronously to the PWM capture compare unit */
    SFRX_SET(PWMA_IER, 0);
    P_SW2 = p_sw2_save;
}

INTERRUPT_USING(PWMA_Routine, EXTI_VectPWMA, 2) {
    uint8_t p_sw2_save = P_SW2;
    if(eye_en){
        /* Cathode 0 is connected to the eyes, it should be low */
        CATHODE0_PIN_BIT = RESET;
        CATHODE1_PIN_BIT = SET;
    } else {
        /* Cathode 1 is connected to the head, it should be low */
        CATHODE0_PIN_BIT = SET;
        CATHODE1_PIN_BIT = RESET;
    }
    eye_en = !eye_en;
    SFRX_RESET(PWMA_IER, 0);
    P_SW2 = p_sw2_save;
}

void deep_sleep(void){
    /* stop_pwm(); */
    /* stop_timer(); */
    disable_pins();
    /* Enable the INT0 interrupt on P3.2 */
    EXTI_Int0_SetTrigByFall;
    EXTI_Int0_SetIntState(HAL_State_ON);
    /* TODO add disabling of the GPIO outputs */

    /* Put the MCU to sleep */
    RCC_SetPowerDownMode(HAL_State_ON);
    /* Disable the interrupt */
    EXTI_Int0_SetIntState(HAL_State_OFF);
    /* Software reset */
    IAP_SoftReset();
    /* For some reason, this doesn't seem to work right, the system comes out of sleep with the animation stopped */
    /* setup_gpio(); */
    /* setup_pwm(); */
    /* setup_timer2_interrupt(); */
    /* select_animation(); */
}

/* With no clock division, the multiplexing runs at 121Hz and PWM runs at 93 kHz */
/* At 1MHz, the multiplexing runs at 114Hz, and the PWM at 3.9 kHz */

void setup_clock(void){
    RCC_SetCLKDivider(24);
}

int main(void){
    setup_clock();
    //SYS_SetClock();
    setup_gpio();
    setup_pwm();

    setup_timer2_interrupt();
    DEBUG_INIT(9600);

    while(1) {
        /* Atomically read button state and timeout into local variables */
        EXTI_Global_SetIntState(HAL_State_OFF);
        uint16_t timeout = button_timeout;
        uint8_t state = button_state;
        EXTI_Global_SetIntState(HAL_State_ON);
        /* Use button state and timeout to determine how long the button was held */
        if(state == 0 && timeout > 20 && timeout < 300){
            short_button_press();
        }
        if(state == 0 && timeout >= 300 && timeout < 700){
            long_button_press();
        }
        if(state == 1 && timeout == 700){
            DEBUG_PRINTLN("select_off_animation()");
            select_off_animation();
        }
        if(state == 0 && timeout >= 700){
            DEBUG_PRINTLN("deep_sleep()");
            deep_sleep();
        }
        if(state == 0 && timeout != 0){
            EXTI_Global_SetIntState(HAL_State_OFF);
            button_timeout = 0;
            EXTI_Global_SetIntState(HAL_State_ON);
        }

        /* Loop, wait for interrupts */
        RCC_SetIdleMode(HAL_State_ON);
    }
}
