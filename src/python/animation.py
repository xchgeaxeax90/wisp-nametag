import numpy as np
import math


#bot_l, bot_c, bot_r, top_l, top_c, top_r
face_light_phases = np.array([210, 270, 310, 150, 70, 45]) * math.pi/180

light_x_coords = np.array([83.38, 112.34, 93.27, 102.53, 86.70, 97.53, 108.87, 87.46, 104.59, 106.45])
light_x_coords -= min(light_x_coords)
light_x_coords /= max(light_x_coords)
light_names = ['light_l', 'light_r', 'eye_l', 'eye_r', 'face_bot_l', 'face_bot_c', 'face_bot_r', 'face_top_l', 'face_top_c', 'face_top_r']

timer_freq = 244

def write_animation(name, lights, period_sec, green_scale):
    timeout = period_sec / len(lights) * timer_freq
    lights = np.clip(lights, 0, 1) * 255
    light_scale = [green_scale if 'face' in x else 1.0 for x in light_names]

    with open(f'{name}.inc', 'w') as f:
        f.write(f'const __CODE animation_data_t {name}[] = {{\n')
        for line in lights:
            output = []
            for i, light in enumerate(line):
                name = light_names[i]
                light = light * light_scale[i]
                output.append(f'.{name}={int(light)}')
            data = ','.join(output)
            f.write(f'{{{{{data}}}, .timeout = {int(timeout)}}},\n')
        f.write('};')
