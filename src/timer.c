#include "timer.h"
#include "fw_hal.h"

#define TIM2_FREQUENCY 244ULL
#define TIM2_PRESCALER 32ULL

void setup_timer2_interrupt(void){
    TIM_Timer2_Set1TMode(HAL_State_ON);
    TIM_Timer2_SetPreScaler(TIM2_PRESCALER-1ULL);
    uint16_t count = 0xffff - ((unsigned long long) __SYSCLOCK / (TIM2_PRESCALER * TIM2_FREQUENCY));
    TIM_Timer2_SetInitValue(count >> 8, count & 0xff);
    /* Don't use this, it's enormous because it includes a division */
    /* TIM_Timer2_Config(HAL_State_ON, 0xff, 100); */
    EXTI_Timer2_SetIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer2_SetRunState(HAL_State_ON);
}

void stop_timer(void){
    TIM_Timer2_SetRunState(HAL_State_OFF);
}
