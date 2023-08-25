#include <Arduino.h>

#pragma once
// 
// Author: Base work done by Rien Matthijsse. Modified by Klaas Nebuhr
// 

// 65c02 connections
//
// NEO6502 board v1.0
#define uP_RESET  26 // RESB(40) <-- UEXT pin 9
#define uP_CLOCK  21 // PHI2
#define uP_RW     11 // RW#
#define uP_BUZZ   20

// mux bus enable pins
//                                2         1         0
//                              21098765432109876543210

// The GPIO Pins 8/9/10 are connected to the output enable
// pin of the bus transreceiver. The OE pin of the transreceiver
// is active low.  
// GPIO 8 controlles bit 0-7 of the addressbus
// GPIO 9 controlles bit 8-15 of the addressbus
// GPIO 10 controlles bit 0-7 of the databus

constexpr uint32_t en_MASK =  0b00000000000011100000000;
constexpr uint32_t en_NONE =  0b00000000000011100000000;
constexpr uint32_t en_A0_7 =  0b00000000000011000000000;
constexpr uint32_t en_A8_15 = 0b00000000000010100000000;
constexpr uint32_t en_D0_7 =  0b00000000000001100000000;
