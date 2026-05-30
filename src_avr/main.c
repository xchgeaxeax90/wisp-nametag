#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "pwm.h"
#include "pins.h"
#include "timer.h"
#include "animation.h"
#include "state_machine.h"


void init_clock();
volatile uint16_t button_timeout = 0;
volatile uint8_t button_state = 0;
void poll_button(void){
    if(BTN_PORT.IN & BTN_bm){
	if(!button_state){
	    button_timeout = 0;
	} else {
	    button_timeout += 1;
	}
	button_state = 1;
    } else {
	button_state = 0;
    }
}

// Called periodically by TCB0 to update the multiplexing for the eyes and top LEDs
static volatile uint8_t eye_en = 0;

ISR(TCB0_INT_vect) {
    poll_button();
    CATHODE_PORT.OUTSET = CAT0_bm | CAT1_bm;
    // Toggle the multiplex driver pins
    if(update_animation()){

	write_pwm(&animation_ptr->pwm_settings);
    }
    eye_en = ~eye_en;
    // Set the actual multiplex pins on the TCA interrupt, so they're synced to the PWM period
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_HUNF_bm;
    TCA0.SPLIT.INTCTRL = TCA_SPLIT_HUNF_bm;
    TCB0.INTFLAGS = TCB_CAPT_bm;
}

ISR(TCA0_HUNF_vect) {
    if(eye_en){
	CATHODE_PORT.OUTCLR = CAT0_bm;
    } else {
	CATHODE_PORT.OUTCLR = CAT1_bm;
    }
    write_pwm_multiplexed(&animation_ptr->pwm_settings, eye_en);
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_HUNF_bm;
    TCA0.SPLIT.INTCTRL = 0;
}

void deep_sleep(void){
    stop_pwm();
    disable_pins();
    disable_timer();
    enable_button_interrupt();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    disable_button_interrupt();
    init_pins();
    init_timer();
    init_pwm();
}

int main(void){
    init_clock();

    init_pins();
    //init_button_interrupt();

    init_pwm();

    init_timer();

    sei();
    while(1){
	cli();
	uint16_t timeout = button_timeout;
	uint8_t state = button_state;
	sei();
	if(state == 0 && timeout > 20 && timeout < 300){
	    short_button_press();
	}
	if(state == 0 && timeout >= 300 && timeout < 700){
	    long_button_press();
	}
	/* use == instead of >= so as not to continuously call
	select_off_animation() every time we poll the button
	state. Doing so causes update_animation to never fire because
	the animation timeout is never reached */
	if(state == 1 && timeout == 700){
	    select_off_animation();
	}
	if(state == 0 && timeout >= 700){
	    deep_sleep();
	}
	if(state == 0 && timeout != 0){
	    cli();
	    button_timeout = 0;
	    sei();
	}
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode();
    }
}


void init_clock(void){
    // Select the HF RC oscillator
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSCHF_gc);
    // Wait until clock switch is over
    while(CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {}

    // Select 1MHz, no run standby
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_1M_gc);

}

