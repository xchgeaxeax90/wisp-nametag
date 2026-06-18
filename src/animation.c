#include "animation.h"
#include "python/animation_circle.inc"
#include "python/animation_breathe.inc"
#include "python/animation_wave.inc"
#include "python/animation_blink.inc"
#include "python/animation_on.inc"

const __CODE animation_data_t animation_off[] = {
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, .timeout = 10}
};

const __CODE animation_data_t* animation_array[] = {
    animation_circle,
    animation_breathe,
    animation_wave,
    animation_blink,
    animation_on,
    animation_off
};

const __CODE uint8_t animation_sizes[] = {
    sizeof(animation_circle)/sizeof(animation_circle[0]),
    sizeof(animation_breathe)/sizeof(animation_breathe[0]),
    sizeof(animation_wave)/sizeof(animation_wave[0]),
    sizeof(animation_blink)/sizeof(animation_blink[0]),
    sizeof(animation_on)/sizeof(animation_on[0]),
    sizeof(animation_off)/sizeof(animation_off[0]),
};

const uint8_t max_animation_select = 4;

const __CODE animation_data_t *animation_ptr = &animation_circle[0];
const uint8_t animation_size = sizeof(animation_circle)/sizeof(animation_circle[0]);

__idata uint16_t timeout_counter = 0;
__idata uint8_t animation_idx = 0;
__idata uint8_t selected_animation = 0;
__BIT update_animation(void){
    if(timeout_counter >= animation_ptr->timeout){
        animation_idx += 1;
        if(animation_idx >= animation_sizes[selected_animation]){
            animation_idx = 0;
        }
        animation_ptr = &animation_array[selected_animation][animation_idx];
        timeout_counter = 0;
        return 1;
    } else {
        timeout_counter += 1;
        return 0;
    }
}

void select_animation(void){
    EXTI_Global_SetIntState(HAL_State_OFF);

    selected_animation += 1;
    if(selected_animation >= max_animation_select){
        selected_animation = 0;
    }
    animation_idx = 0;
    timeout_counter = 0;
    EXTI_Global_SetIntState(HAL_State_ON);
}
void select_on_animation(void){
    EXTI_Global_SetIntState(HAL_State_OFF);

    selected_animation = max_animation_select;
    animation_idx = 0;
    timeout_counter = 0;
    EXTI_Global_SetIntState(HAL_State_ON);
}
void select_off_animation(void){
    EXTI_Global_SetIntState(HAL_State_OFF);

    selected_animation = max_animation_select + 1;
    animation_idx = 0;
    timeout_counter = 0;
    EXTI_Global_SetIntState(HAL_State_ON);
}
