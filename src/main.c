#include "fw_hal.h"
#include "pins.h"
#include "pwm.h"
#include "timer.h"
#include "animation.h"

/* TODO determine if we actually need the button state bit */
volatile __idata uint16_t button_timeout = 0;
volatile __BIT button_state = 0;
void poll_button(void){
    if(P3 & BUTTON_PIN){
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

// Called periodically by TCB0 to update the multiplexing for the eyes and top LEDs

/* Selects which cathode to enable */
static volatile __BIT cathode_select = 0;
INTERRUPT_USING(Timer2_Routine, EXTI_VectTimer2, 1) {
    poll_button();
    /* Disable cathodes */
    if(update_animation()){

        write_pwm(&animation_ptr->pwm_settings);
    }
    cathode_select = ~cathode_select;

    /* Enable the interrupt for PWM overflow to synchronize cathode updates to PWM period */
}

void deep_sleep(void){
    /* Enable the INT0 interrupt on P3.2 */
    EXTI_Int0_SetTrigByFall;
    EXTI_Int0_SetIntState(HAL_State_ON);
    /* TODO add disabling of the GPIO outputs */

    /* Put the MCU to sleep */
    RCC_SetPowerDownMode(HAL_State_ON);
    /* Disable the interrupt */
    EXTI_Int0_SetIntState(HAL_State_OFF);
}


int main(void){
    //SYS_SetClock();
    setup_gpio();
    setup_pwm();

    setup_timer2_interrupt();
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
            select_off_animation();
        }
        if(state == 0 && timeout >= 700){
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
