#include "fw_hal.h"

static void setup_gpio(void){
    GPIO_P1_SetMode(
                    GPIO_Pin_2 | GPIO_Pin_3,
                    GPIO_Mode_Output_PP);
}

int main(void){
    //SYS_SetClock();
    setup_gpio();

    P1 = GPIO_Pin_2;
    SYS_Delay(100);
    P1 = 0;

    for(;;) {
        P1 = GPIO_Pin_3;
        SYS_Delay(5);
        P1 = 0;
        SYS_Delay(5);
    }
}
