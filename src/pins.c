#include "pins.h"
#include "fw_hal.h"


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
