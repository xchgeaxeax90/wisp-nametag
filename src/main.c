#include "fw_hal.h"
#include "pins.h"
#include "pwm.h"
#include "timer.h"

static __idata uint8_t timer2_int_count;
INTERRUPT_USING(Timer2_Routine, EXTI_VectTimer2, 1) {
    SFRX_ON();
    PWMA_CCR1L = timer2_int_count;
    PWMA_CCR2L = (timer2_int_count + 0x20);
    PWMA_CCR3L = (timer2_int_count + 0x40);
    PWMA_CCR4L = (timer2_int_count + 0x60);
    PWMB_CCR5L = (timer2_int_count + 0x80);
    PWMB_CCR6L = (timer2_int_count + 0xa0);
    PWMB_CCR7L = (timer2_int_count + 0xc0);
    PWMB_CCR8L = (timer2_int_count + 0xe0);
    SFRX_OFF();

    timer2_int_count += 1;
}

void deep_sleep(void){
    /* Enable the INT0 interrupt on P3.2 */
    EXTI_Int0_SetTrigByFall;
    EXTI_Int0_SetIntState(HAL_State_ON);

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
        /* SYS_Delay(2000); */
        /* deep_sleep(); */
        /* Enter idle state */
        RCC_SetIdleMode(HAL_State_ON);
    }
}
