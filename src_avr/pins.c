#include <avr/io.h>
#include "pins.h"
#include <avr/interrupt.h>

void init_pins(void){
    PORTA.DIR = 0;
    PORTC.DIR = 0;
    PORTD.DIR = 0;

    /* Set PWM0-7 and the cathode pins as outputs */
    PWM0to5_PORT.DIRSET = PWM0_bm | PWM1_bm | PWM2_bm | PWM3_bm | PWM4_bm | PWM5_bm;
    CATHODE_PORT.DIRSET = CAT0_bm | CAT1_bm;
    PORTD.DIRSET = PWM6_bm | PWM7_bm | PORTD_EXTRA;
    
    /* Configure the button input as an input with a pullup */
    BTN_PORT.DIRCLR = BTN_bm;
    PORTC.DIRSET = PORTC_EXTRA;
    BTN_PORT.PINCONFIG = PORT_PULLUPEN_bm | PORT_INVEN_bm;
    BTN_PORT.PINCTRLUPD = BTN_bm;

    /* drive all outputs, including unused pins to 0 */
    PORTA.OUT = 0;
    PORTC.OUT = 0;
    PORTD.OUT = 0;
    
    /* Disable input buffers on all pins that are outputs to save power */
    PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
    PORTA.PINCTRLUPD = 0xFF;
    PORTD.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PINCTRLUPD = 0xFF;
    PORTC.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
    PORTC.PINCTRLUPD = PORTC_EXTRA;
}

void disable_pins(void){
    PORTA.OUT = 0;
    PORTD.OUT = 0;
    PORTC.OUT = 0;
}

void enable_button_interrupt(void){
    BTN_PORT.PINCONFIG = PORT_PULLUPEN_bm | PORT_INVEN_bm | PORT_ISC_RISING_gc;
    BTN_PORT.PINCTRLUPD = BTN_bm;
}
void disable_button_interrupt(void){
    BTN_PORT.PINCONFIG = PORT_PULLUPEN_bm | PORT_INVEN_bm;
    BTN_PORT.PINCTRLUPD = BTN_bm;
}


// In the future we might want to set the button up as the TCB1 input
// and have it sense how long the button is held
ISR(PORTC_PORT_vect) {

    // Clear the CAPT interrupt
    PORTC.INTFLAGS = BTN_bm;
}
