import numpy as np
import math
from animation import face_light_phases, timer_freq, write_animation, light_x_coords



def animation_circle():
    period = 16
    period_sec = 1.0
    face_lights = np.zeros((period, len(face_light_phases)))
    for i in range(period):
        face_lights[i] = np.sin(face_light_phases + (i/period)*math.pi*2)


    eyes = np.zeros((period, 2))
    lightsticks = np.zeros((period, 2))

    for i in range(period):
        lightsticks[i] = np.sin(i/period * math.pi*2)**5

    for i in range(period):
        eyes[i] = np.sin(i/period*2 * math.pi*2 + math.pi*1.3)**2



    lights = np.concat((lightsticks, eyes, face_lights), axis=1)
    write_animation('animation_circle', lights, period_sec)

def animation_breathe():
    period = 8
    period_sec = 1.0
    lights = np.zeros((period, len(face_light_phases) + 4))

    for i in range(period):
        lights[i] = np.sin(lights[i] + i/period * math.pi)
    write_animation('animation_breathe', lights, period_sec)

def animation_wave():
    period = 24
    period_sec = 1.5
    lights = np.zeros((period, len(face_light_phases) + 4))

    light_phase = math.pi * light_x_coords
    for i in range(period):
        lights[i] = np.sin(light_phase + i/period * math.pi*2)
    write_animation('animation_wave', lights, period_sec)

def animation_blink():
    period = 30
    period_sec = 2.0
    
    face_lights = np.zeros((period, len(face_light_phases)))
    eyes = np.zeros((period, 2))
    lightsticks = np.zeros((period, 2))
    lightstick_phase = np.array([0, math.pi])
    for i in range(period):
        phase = i/period * math.pi*2
        face_lights[i] = np.full(face_lights[i].shape, 0.5 + 0.1*np.sin(phase))
        eyes[i] = np.full(eyes[i].shape, 0.5 + 0.2*np.sin(phase))

        lightsticks[i] = np.sin(lightstick_phase + phase)**9

    lights = np.concat((lightsticks, eyes, face_lights), axis=1)
    write_animation('animation_blink', lights, period_sec)

    

if __name__ == '__main__':
    animation_circle()
    animation_breathe()
    animation_wave()
    animation_blink()
