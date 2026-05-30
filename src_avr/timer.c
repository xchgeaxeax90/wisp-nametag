#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"


extern void multiplex_update(void);


void init_timer(void){

    // Configure for a period of 1MHz/(16*256) = 244HZ - this should make TCB0 yield an interrupt every 16 PWM periods of TCA0
    TCB0.CCMP = 16*256;

    // Configure TCB0 for periodic interrupts, no waveform output, no CC input
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;

    // Enable the TCB0 CAPT (triggers when the counter = CCMP) interrupt
    TCB0.INTCTRL = TCB_CAPT_bm;


    // Enable, use TCA0's clock source
    TCB0.CTRLA = TCB_ENABLE_bm | TCB_CLKSEL_TCA0_gc;
}

void disable_timer(void){
    TCB0.CTRLA &= ~(TCB_ENABLE_bm);
}
