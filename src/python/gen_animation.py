import numpy as np
import math
import argparse
from animation import face_light_phases, timer_freq, write_animation, light_x_coords



def animation_circle(args):
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
    write_animation('animation_circle', lights, period_sec, args.green_scale)

def animation_breathe(args):
    period = 20
    period_sec = 1.0
    lights = np.zeros((period, len(face_light_phases) + 4))

    for i in range(period):
        lights[i] = np.sin(lights[i] + i/period * math.pi)
    write_animation('animation_breathe', lights, period_sec, args.green_scale)

def animation_wave(args):
    period = 24
    period_sec = 1.5
    lights = np.zeros((period, len(face_light_phases) + 4))

    light_phase = math.pi * light_x_coords
    for i in range(period):
        lights[i] = np.sin(light_phase + i/period * math.pi*2)
    write_animation('animation_wave', lights, period_sec, args.green_scale)

def animation_blink(args):
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
    write_animation('animation_blink', lights, period_sec, args.green_scale)


def animation_twinkle(args):
    period = 150
    period_sec = 12

    np.random.seed(2)
    face_lights = np.zeros((period, 8))
    lightsticks = np.zeros((period, 2))

    # Give each light on the face, including the eyes, a random frequency and phase
    face_light_phases = np.random.rand(8) * 2 * math.pi
    face_light_frequencies = np.random.rand(8) * 8 + 1
    face_light_frequencies = np.round(face_light_frequencies * period_sec) / period_sec

    lightstick_phases = np.full(2, 0.5*math.pi)
    lightstick_frequency = np.full(2, 0.5*math.pi)


    for i in range(period):
        t = i/period * period_sec
        phase = face_light_phases + face_light_frequencies * t

        face_lights[i] = np.sin(phase)**9

        lightsticks[i] = np.sin(lightstick_phases + lightstick_frequency * t) ** 2

    lights = np.concat((lightsticks, face_lights), axis=1)
    write_animation('animation_twinkle', lights, period_sec, args.green_scale)

def animation_on(args):
    lights = np.ones((1, 10))
    write_animation('animation_on', lights, 0.1, args.green_scale)

    

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--green-scale', type=float, default=1.0, help='Factor to scale the green light brightness')
    args = parser.parse_args()
    animation_circle(args)
    animation_breathe(args)
    animation_wave(args)
    animation_blink(args)
    animation_twinkle(args)
    animation_on(args)
