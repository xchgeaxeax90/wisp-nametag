#pragma once

enum state_t {
    STATE_ANIMATION_SEL,
    STATE_BRIGHTNESS_SEL
};

void short_button_press(void);

void long_button_press(void);

/* Sets animation state to whatever the state variable says it is */
void set_animation_state(void);
