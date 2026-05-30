#include "fw_hal.h"

/*
  PWM Pin selections:
  - PWMA1 - Alt 0 - P1.0
  - PWMA2 - Alt 0 - P1.2
  - PWMA3 - Alt 0 - P1.4
  - PWMA4 - Alt 0 - P1.6
  - PWMB1 - Alt 1 - P1.7
  - PWMB2 - Alt 1 - P5.4
  - PWMB3 - Alt 1 - P3.3
  - PWMB4 - Alt 1 - P3.4

 */

static void setup_gpio(void){
    GPIO_P1_SetMode(GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7,
                    GPIO_Mode_Output_PP);
    GPIO_P3_SetMode(GPIO_Pin_3 | GPIO_Pin_4,
                    GPIO_Mode_Output_PP);
    GPIO_P5_SetMode(GPIO_Pin_4,
                    GPIO_Mode_Output_PP);
}


#define PWM_CCMR \
    (0x0 << 0) |                  /* CCS = 0 - output */ \
    (0x1 << 2) |                  /* Preload enable - required for PWM */ \
    (PWM_OutputMode_PWM_HighIfLess << 4) /* set OCx high if counter is less than compare match register */ 



/* Init PWM2 P/N, which outputs on: P1.2 - PWM2P P1.3 - PWM2N */
static void setup_pwm(void){
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
    PWMA_CCER1 = 0x55;
    PWMA_CCER2 = 0x55;
    PWMB_CCER1 = 0x55;
    PWMB_CCER2 = 0x55;
        
    SFRX_OFF();

    PWMA_PWM2_SetCaptureCompareValue(0xc0);

    PWMA_SetPrescaler(0);
    PWMA_SetPeriod(0xff);
    PWMA_SetCounterDirection(PWM_CounterDirection_Up);
    PWMA_SetAutoReloadPreload(HAL_State_ON);

    PWMB_SetPrescaler(0);
    PWMB_SetPeriod(0xff);
    PWMB_SetCounterDirection(PWM_CounterDirection_Up);
    PWMB_SetAutoReloadPreload(HAL_State_ON);

    PWMB_PWM1_SetPort(PWMB_PWM5_AlterPort_P17);
    PWMB_PWM2_SetPort(PWMB_PWM6_AlterPort_P54);
    PWMB_PWM3_SetPort(PWMB_PWM7_AlterPort_P33);
    PWMB_PWM4_SetPort(PWMB_PWM8_AlterPort_P34);


    PWMA_SetPinOutputState(PWM_Pin_1 | PWM_Pin_2 | PWM_Pin_3 | PWM_Pin_4, HAL_State_ON);
    PWMA_SetOverallState(HAL_State_ON);
    PWMA_SetCounterState(HAL_State_ON);

    PWMB_SetPinOutputState(PWM_Pin_1 | PWM_Pin_2 | PWM_Pin_3 | PWM_Pin_4, HAL_State_ON);
    PWMB_SetOverallState(HAL_State_ON);
    PWMB_SetCounterState(HAL_State_ON);

}

int main(void){
    //SYS_SetClock();
    setup_gpio();
    setup_pwm();

    P1 = GPIO_Pin_2;
    SYS_Delay(10);
    P1 = 0;

    uint8_t i=0;
    for(;;) {
        SFRX_ON();
        PWMA_CCR1L = i;
        PWMA_CCR2L = (i + 0x20);
        PWMA_CCR3L = (i + 0x40);
        PWMA_CCR4L = (i + 0x60);
        PWMB_CCR5L = (i + 0x80);
        PWMB_CCR6L = (i + 0xa0);
        PWMB_CCR7L = (i + 0xc0);
        PWMB_CCR8L = (i + 0xe0);
        SFRX_OFF();

        i += 1;
        SYS_Delay(20);
    }
}
