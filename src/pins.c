#include "pins.h"
#include "fw_hal.h"

/* In order to sleep with the lowest power possible, I need to make sure no pins are floating
   With only the PWM pins set as output, and with all ports driven to 0, the mcu sleeps at ~30uA
   With every pin but the button set as output, the mcu sleeps at 0.4uA, the sleep current listed in the datasheet
   With the input buffer disabled on the extra pins, the mcu sleeps at 10uA
   With input buffer and schmitt trigger disabled on the extra pins, the mcu sleeps at 5uA
   With pull up enabled on the extra pins, the mcu sleeps at >1mA OH NO
 */

#define PWM_PINS_P1 ((GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7))
#define PWM_PINS_P3 ((GPIO_Pin_3 | GPIO_Pin_4))
#define PWM_PINS_P5 ((GPIO_Pin_4))

#define CATH_PINS_P1 ((GPIO_Pin_5))
#define CATH_PINS_P3 ((GPIO_Pin_7))
#define EXTRA_PINS_P1 ((GPIO_Pin_1 | GPIO_Pin_3))
#define EXTRA_PINS_P3 ((GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6))


void setup_gpio(void){
    GPIO_P1_SetMode(PWM_PINS_P1 | CATH_PINS_P1 | EXTRA_PINS_P1,
                    GPIO_Mode_Output_PP);
    GPIO_P3_SetMode(PWM_PINS_P3 | CATH_PINS_P3 | EXTRA_PINS_P3,
                    GPIO_Mode_Output_PP);
    GPIO_P5_SetMode(GPIO_Pin_4,
                    GPIO_Mode_Output_PP);
    GPIO_P3_SetMode(BUTTON_PIN, GPIO_Mode_Input_HIP);
    GPIO_SetPullUp(GPIO_Port_3, BUTTON_PIN, HAL_State_ON);
}

void disable_pins(void){
    /* Instead of putting all pins into high impedance input, try driving them all low */
    /* I worry that HIP causes the inputs to float and the input buffers to waste power */
    P1 = 0;
    P3 = 0;
    P5 = 0;
    
    /* GPIO_P1_SetMode(GPIO_Pin_All, GPIO_Mode_Input_HIP); */
    /* GPIO_P3_SetMode(GPIO_Pin_All, GPIO_Mode_Input_HIP); */
    /* GPIO_P5_SetMode(GPIO_Pin_All, GPIO_Mode_Input_HIP); */
}
