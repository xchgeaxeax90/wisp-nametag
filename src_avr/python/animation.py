import numpy as np
import math


#bot_l, bot_c, bot_r, top_l, top_c, top_r
face_light_phases = np.array([210, 270, 310, 150, 70, 45]) * math.pi/180

light_x_coords = np.array([83.38, 112.34, 93.27, 102.53, 86.70, 97.53, 108.87, 87.46, 104.59, 106.45])
light_x_coords -= min(light_x_coords)
light_x_coords /= max(light_x_coords)

timer_freq = 244

def write_animation(name, lights, period_sec):
    timeout = period_sec / len(lights) * timer_freq
    lights = np.clip(lights, 0, 1) * 255

    with open(f'{name}.inc', 'w') as f:
        f.write(f'const __flash animation_data_t {name}[] = {{\n')
        for line in lights:
            line = [f'{int(x):4}' for x in line]
            data = ','.join(line)
            f.write(f'{{{{{data}}}, .timeout = {int(timeout)}}},\n')
        f.write('};')
