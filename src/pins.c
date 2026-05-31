#include "pins.h"
#include "fw_hal.h"


/*
  Pin selections:
  - PWMA1 - Alt 0 - P1.0
  - PWMA2 - Alt 0 - P1.2
  - PWMA3 - Alt 0 - P1.4
  - PWMA4 - Alt 0 - P1.6
  - PWMB1 - Alt 1 - P1.7
  - PWMB2 - Alt 1 - P5.4
  - PWMB3 - Alt 1 - P3.3
  - PWMB4 - Alt 1 - P3.4
  - Button - P3.2 - INT0 - Internal Pullup to VCC

 */

void setup_gpio(void){
    GPIO_P1_SetMode(GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7,
                    GPIO_Mode_Output_PP);
    GPIO_P3_SetMode(GPIO_Pin_3 | GPIO_Pin_4,
                    GPIO_Mode_Output_PP);
    GPIO_P3_SetMode(GPIO_Pin_2, GPIO_Mode_Input_HIP);
    GPIO_SetPullUp(GPIO_Port_3, GPIO_Pin_2, HAL_State_ON);
    GPIO_P5_SetMode(GPIO_Pin_4,
                    GPIO_Mode_Output_PP);
}
