#include "timer.h"
#include "fw_hal.h"


void setup_timer2_interrupt(void){
    TIM_Timer2_Set1TMode(HAL_State_ON);
    TIM_Timer2_SetPreScaler(0xff);
    uint16_t count = 0xffff - ((unsigned long long) __SYSCLOCK / (256 * 100));
    TIM_Timer2_SetInitValue(count >> 8, count & 0xff);
    /* Don't use this, it's enormous because it includes a division */
    /* TIM_Timer2_Config(HAL_State_ON, 0xff, 100); */
    EXTI_Timer2_SetIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer2_SetRunState(HAL_State_ON);
}
