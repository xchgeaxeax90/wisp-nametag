#include "state_machine.h"
#include "animation.h"
#include "pwm.h"

static enum state_t state = STATE_ANIMATION_SEL;


void short_button_press(void){
    switch(state){
    case STATE_ANIMATION_SEL:
	select_animation();
	break;
    case STATE_BRIGHTNESS_SEL:
	select_brightness();
	break;
    }
}

void long_button_press(void){
    switch(state){
    case STATE_ANIMATION_SEL:
	select_on_animation();
	state = STATE_BRIGHTNESS_SEL;
	break;
    case STATE_BRIGHTNESS_SEL:
	select_animation();
	state = STATE_ANIMATION_SEL;
	break;
    }
}
