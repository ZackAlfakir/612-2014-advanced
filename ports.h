#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

// DriveTrain Channels
const static uint32_t TALON_FL_CHANNEL = 1; //real
const static uint32_t TALON_FR_CHANNEL = 6; //real
const static uint32_t TALON_RL_CHANNEL = 2; //real
const static uint32_t TALON_RR_CHANNEL = 7; //real
// DriveTrain Modules
const static uint8_t  TALON_FL_MODULE  = 1; //real
const static uint8_t  TALON_FR_MODULE  = 1; //real
const static uint8_t  TALON_RL_MODULE  = 1; //real
const static uint8_t  TALON_RR_MODULE  = 1; //real

// Pneumatics Channels
const static uint32_t PNUM_DIGIN_CHANNEL = 1;
const static uint32_t PNUM_RELAY_CHANNEL = 0;
// Pneumatics Modules
const static uint8_t  PNUM_DIGIN_MODULE  = 1;
const static uint8_t  PNUM_RELAY_MODULE  = 0;

// Shifter
const static uint32_t SHIFT_CHAN  = 0;
const static uint8_t  SHIFT_MOD_F = 1;
const static uint8_t  SHIFT_MOD_R = 2;

// Joystick
const uint32_t DRIVER_JOY_PORT = 1;
const uint32_t GUNNER_JOY_PORT = 2;

//Encoders

#endif
