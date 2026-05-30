#include "fw_hal.h"

static void setup_gpio(void){
    GPIO_P1_SetMode(
                    GPIO_Pin_2 | GPIO_Pin_3,
                    GPIO_Mode_Output_PP);
}

int main(void){
    setup_gpio();

    while(1) {
        P1 ^= GPIO_Pin_2 | GPIO_Pin_3;
        SYS_Delay(500);
    }
}
