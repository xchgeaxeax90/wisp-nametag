#include "animation.h"
#include "python/animation_circle.inc"
#include "python/animation_breathe.inc"
#include "python/animation_wave.inc"
#include "python/animation_blink.inc"

const __CODE animation_data_t *animation_ptr = &animation_circle[0];
const uint8_t animation_size = sizeof(animation_circle)/sizeof(animation_circle[0]);

__idata uint16_t timeout_counter = 0;
__idata uint8_t animation_idx = 0;
__BIT update_animation(void){
    if(timeout_counter >= animation_ptr->timeout){
        animation_idx += 1;
        if(animation_idx >= animation_size){
            animation_idx = 0;
        }
        animation_ptr = &animation_circle[animation_idx];
        timeout_counter = 0;
        return 1;
    } else {
        timeout_counter += 1;
        return 0;
    }
}

void select_animation(void){
}
void select_on_animation(void){
}
void select_off_animation(void){
}
