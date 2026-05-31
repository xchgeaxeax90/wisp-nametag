#pragma once

/*
  Pin selections:
  - PWMA1 - Alt 0 - P1.0 - Eye/Face Top L
  - PWMA2 - Alt 0 - P1.2 - Light L
  - PWMA3 - Alt 0 - P1.4 - Face Top C
  - PWMA4 - Alt 0 - P1.6 - Eye/Face Top R
  - PWMB1 - Alt 1 - P1.7 - Face Bot L
  - PWMB2 - Alt 1 - P5.4 - Face Bot C
  - PWMB3 - Alt 1 - P3.3 - Light R
  - PWMB4 - Alt 1 - P3.4 - Face Bot R
  - Button - P3.2 - INT0 - Internal Pullup to VCC
  - Cathode 0 - P3.7 
  - Cathode 1 - P1.5 
 */

#define BUTTON_PORT GPIO_Port_3
#define BUTTON_PIN GPIO_Pin_2
#define CATHODE0_PIN_BIT P37
#define CATHODE1_PIN_BIT P15

void setup_gpio(void);

void disable_pins(void);
