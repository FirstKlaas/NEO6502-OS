// THIS FILE IS AUTO GENERATED. DO NOT CHANGE
//

#include <pico/stdlib.h>
#include <Arduino.h>

typedef struct {
  uint16_t address;
  uint16_t size;
  uint8_t *data;
} TSegment;
TSegment segment[5];

// SEGMENT: isr @ 0x0a00
uint8_t isr_data[] = {
    0x48, 0x8a, 0x48, 0x98, 0x48, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 
    0xa9, 0xb4, 0x8d, 0x17, 0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 0x8d, 0x19, 0xd0, 0xa9, 
    0x17, 0x8d, 0x1a, 0xd0, 0x20, 0xeb, 0xe1, 0x68, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 0x00, 
    0x8d, 0x16, 0xd0, 0xa9, 0x14, 0x8d, 0x17, 0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 0x8d, 
    0x19, 0xd0, 0xa9, 0xa0, 0x8d, 0x1a, 0xd0, 0xa9, 0x37, 0x8d, 0x1b, 0xd0, 0x20, 0x24, 0xe2, 0x68, 
    0xad, 0xb9, 0xe4, 0xc9, 0x0a, 0x10, 0x08, 0xa9, 0x01, 0x8d, 0xa8, 0x0a, 0x4c, 0x6b, 0x0a, 0xad, 
    0xc0, 0xe4, 0xc9, 0xef, 0x30, 0x3b, 0xa9, 0xff, 0x8d, 0xa8, 0x0a, 0xad, 0xd9, 0xe4, 0xc9, 0x64, 
    0x30, 0x21, 0xa0, 0x08, 0xa9, 0x20, 0x99, 0xd9, 0xe4, 0x88, 0x10, 0xfa, 0xa0, 0x08, 0xa9, 0x30, 
    0x99, 0xe1, 0xe4, 0x88, 0x10, 0xfa, 0xa0, 0x08, 0xa9, 0x40, 0x99, 0xe9, 0xe4, 0x88, 0x10, 0xfa, 
    0x4c, 0xa1, 0x0a, 0xa0, 0x18, 0xb9, 0xd9, 0xe4, 0x18, 0x69, 0x04, 0x99, 0xd9, 0xe4, 0x88, 0x10, 
    0xf4, 0xa0, 0x07, 0xb9, 0xb9, 0xe4, 0x18, 0x69, 0x01, 0x99, 0xb9, 0xe4, 0x99, 0xc1, 0xe4, 0x99, 
    0xc9, 0xe4, 0x88, 0x10, 0xee, 0xad, 0x0d, 0xdc, 0x68, 0xa8, 0x68, 0xaa, 0x68, 0x40, 
    0x00 };

// SEGMENT: kernel_routines_entry_points @ 0xe000
uint8_t kernel_routines_entry_points_data[] = {
    0x4c, 0x00, 0xe1, 0x4c, 0x0c, 0xe1, 0x4c, 0x24, 0xe1, 0x4c, 0x98, 0xe1, 
    0x00 };

// SEGMENT: kernel_routines @ 0xe100
uint8_t kernel_routines_data[] = {
    0xad, 0x11, 0xd0, 0x10, 0xfb, 0x29, 0x70, 0xaa, 0xad, 0x10, 0xd0, 0x60, 0x48, 0x8d, 0x15, 0xd0, 
    0xa9, 0x03, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 
    0x30, 0xfb, 0x68, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x04, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 
    0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x68, 0x60, 0x48, 0x8d, 0x15, 0xd0, 
    0xa9, 0x07, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 
    0x30, 0xfb, 0x68, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x08, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 
    0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x68, 0x60, 0xa9, 0x01, 0x8d, 0x14, 
    0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0xad, 0x15, 
    0xd0, 0x60, 0xa9, 0x02, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 
    0x13, 0xd0, 0x30, 0xfb, 0xad, 0x15, 0xd0, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x0d, 0x8d, 0x14, 
    0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x68, 0x60, 
    0x8c, 0xc4, 0xe1, 0x8d, 0xc6, 0xe1, 0xa0, 0x00, 0xb1, 0xe0, 0xf0, 0x07, 0x20, 0x98, 0xe1, 0xc8, 
    0x4c, 0xb8, 0xe1, 0xa0, 0x00, 0xa9, 0x00, 0x60, 0x48, 0xa9, 0x00, 0x85, 0xe0, 0xa9, 0xf0, 0x85, 
    0xe1, 0x68, 0x48, 0x4a, 0x4a, 0x4a, 0x4a, 0x29, 0x0f, 0xa8, 0xb1, 0xe0, 0x20, 0x98, 0xe1, 0x68, 
    0x48, 0x29, 0x0f, 0xa8, 0xb1, 0xe0, 0x20, 0x98, 0xe1, 0x68, 0x60, 0xa9, 0x15, 0x8d, 0x14, 0xd0, 
    0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x0f, 
    0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 
    0x60, 0xa9, 0x1a, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 
    0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x1b, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 
    0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa2, 0x00, 0xa9, 0x69, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 
    0x9d, 0x79, 0xe5, 0xa2, 0x08, 0xa9, 0x79, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 
    0x10, 0xa9, 0x89, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x01, 0xa9, 0x69, 0x9d, 
    0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x09, 0xa9, 0x79, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 
    0x9d, 0x79, 0xe5, 0xa2, 0x11, 0xa9, 0x89, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 
    0x02, 0xa9, 0x69, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x0a, 0xa9, 0x79, 0x9d, 
    0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x12, 0xa9, 0x89, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 
    0x9d, 0x79, 0xe5, 0xa2, 0x03, 0xa9, 0x69, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 
    0x0b, 0xa9, 0x79, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x13, 0xa9, 0x89, 0x9d, 
    0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x04, 0xa9, 0x69, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 
    0x9d, 0x79, 0xe5, 0xa2, 0x0c, 0xa9, 0x79, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 
    0x14, 0xa9, 0x89, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x05, 0xa9, 0x69, 0x9d, 
    0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x0d, 0xa9, 0x79, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 
    0x9d, 0x79, 0xe5, 0xa2, 0x15, 0xa9, 0x89, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 
    0x06, 0xa9, 0x69, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x0e, 0xa9, 0x79, 0x9d, 
    0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x16, 0xa9, 0x89, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 
    0x9d, 0x79, 0xe5, 0xa2, 0x07, 0xa9, 0x69, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 
    0x0f, 0xa9, 0x79, 0x9d, 0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x17, 0xa9, 0x89, 0x9d, 
    0x59, 0xe5, 0xa9, 0xe4, 0x9d, 0x79, 0xe5, 0xa2, 0x00, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 
    0xe4, 0xa2, 0x01, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x02, 0xbd, 0x99, 0xe4, 
    0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x03, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 
    0x04, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x05, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 
    0x9d, 0x99, 0xe4, 0xa2, 0x06, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x07, 0xbd, 
    0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x08, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 
    0xe4, 0xa2, 0x09, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x0a, 0xbd, 0x99, 0xe4, 
    0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x0b, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 
    0x0c, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x0d, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 
    0x9d, 0x99, 0xe4, 0xa2, 0x0e, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x0f, 0xbd, 
    0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x10, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 
    0xe4, 0xa2, 0x11, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x12, 0xbd, 0x99, 0xe4, 
    0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x13, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 
    0x14, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x15, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 
    0x9d, 0x99, 0xe4, 0xa2, 0x16, 0xbd, 0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa2, 0x17, 0xbd, 
    0x99, 0xe4, 0x05, 0xc0, 0x9d, 0x99, 0xe4, 0xa9, 0x99, 0x8d, 0x15, 0xd0, 0xa9, 0xe4, 0x8d, 0x16, 
    0xd0, 0xa9, 0x20, 0x8d, 0x17, 0xd0, 0xa9, 0x17, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 
    0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0x02, 0x40, 0x07, 0xe0, 0x0f, 0xf0, 0x1d, 
    0xb8, 0x17, 0xe8, 0x17, 0xe8, 0x02, 0x40, 0x06, 0x60, 0x00, 0x00, 0x04, 0x40, 0x03, 0x80, 0x07, 
    0xc0, 0x05, 0x40, 0x07, 0xc0, 0x0a, 0xa0, 0x0a, 0xa0, 0x00, 0x00, 0x04, 0x40, 0x0f, 0xe0, 0x19, 
    0x30, 0x1f, 0xf0, 0x1f, 0xf0, 0x15, 0x50, 0x0a, 0xa0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 
    0x80, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
    0x1f, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 
    0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 
    0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x00, 0x16, 0x00, 0x00, 0x32, 0x00, 0x00, 0x64, 0x00, 0x01, 
    0x28, 0x00, 0x02, 0x56, 0x00, 0x05, 0x12, 0x00, 0x10, 0x24, 0x00, 0x20, 0x48, 0x00, 0x40, 0x96, 
    0x00, 0x81, 0x92, 0x01, 0x63, 0x84, 0x03, 0x27, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xa9, 
    0x00, 0x8d, 0xcb, 0xe5, 0x8d, 0xcc, 0xe5, 0x8d, 0xcd, 0xe5, 0xa2, 0x2d, 0x0e, 0xc9, 0xe5, 0x2e, 
    0xca, 0xe5, 0x90, 0x1c, 0xad, 0xcb, 0xe5, 0x18, 0x7d, 0x9b, 0xe5, 0x8d, 0xcb, 0xe5, 0xad, 0xcc, 
    0xe5, 0x7d, 0x9a, 0xe5, 0x8d, 0xcc, 0xe5, 0xad, 0xcd, 0xe5, 0x7d, 0x99, 0xe5, 0x8d, 0xcd, 0xe5, 
    0xca, 0xca, 0xca, 0x10, 0xd7, 0xd8, 0x60, 0x48, 0x29, 0x0f, 0x85, 0xe0, 0x68, 0x48, 0x4a, 0x4a, 
    0x4a, 0x4a, 0x85, 0xe1, 0x68, 0x60, 0xa5, 0xe0, 0x0a, 0x0a, 0x0a, 0x85, 0xe0, 0xa5, 0xe1, 0x4a, 
    0x4a, 0x4a, 0x29, 0x07, 0x05, 0xe0, 0x85, 0xe0, 0xa5, 0xe1, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x85, 
    0xe1, 0xa5, 0xe2, 0x29, 0x1f, 0x05, 0xe1, 0x85, 0xe1, 0x60, 
    0x00 };

// SEGMENT: kernel_data @ 0xf000
uint8_t kernel_data_data[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 
    0x57, 0x65, 0x6c, 0x63, 0x6f, 0x6d, 0x65, 0x20, 0x74, 0x6f, 0x20, 0x46, 0x69, 0x72, 0x73, 0x74, 
    0x4b, 0x6c, 0x61, 0x61, 0x73, 0x20, 0x4f, 0x53, 0x20, 0x76, 0x30, 0x2e, 0x31, 
    0x00 };

// SEGMENT: main_program @ 0x0800
uint8_t main_program_data[] = {
    0xa2, 0xff, 0x9a, 0xa9, 0x00, 0x8d, 0xfe, 0xff, 0xa9, 0x0a, 0x8d, 0xff, 0xff, 0xa9, 0x00, 0x8d, 
    0xfa, 0xff, 0xa9, 0x0a, 0x8d, 0xfb, 0xff, 0xad, 0x13, 0xd0, 0x09, 0x0c, 0x8d, 0x13, 0xd0, 0xa9, 
    0x84, 0x8d, 0x0d, 0xdc, 0xa9, 0x20, 0x20, 0x3c, 0xe1, 0xa9, 0x02, 0x20, 0x0c, 0xe1, 0xa9, 0x01, 
    0x20, 0x24, 0xe1, 0xa9, 0xf7, 0x85, 0xe0, 0xa9, 0x08, 0x85, 0xe1, 0x20, 0xb0, 0xe1, 0xa9, 0xff, 
    0x8d, 0xc9, 0xe5, 0xa9, 0xff, 0x8d, 0xca, 0xe5, 0xad, 0xca, 0xe5, 0x8d, 0xff, 0xd0, 0xad, 0xc9, 
    0xe5, 0x8d, 0xff, 0xd0, 0x20, 0xce, 0xe5, 0xad, 0xcd, 0xe5, 0x8d, 0xff, 0xd0, 0xad, 0xcc, 0xe5, 
    0x8d, 0xff, 0xd0, 0xad, 0xcb, 0xe5, 0x8d, 0xff, 0xd0, 0x4c, 0x69, 0x08, 0xa9, 0xf0, 0x8d, 0x05, 
    0xdc, 0xa9, 0x00, 0x8d, 0x04, 0xdc, 0xa9, 0x81, 0x8d, 0x0d, 0xdc, 0xa9, 0x11, 0x8d, 0x0e, 0xdc, 
    0x60, 0xc8, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xba, 0x00, 0xc7, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xbb, 
    0x00, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 
    0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 
    0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0x00, 0x4e, 0x45, 0x2f, 0x4f, 0x53, 0x20, 0x76, 0x30, 0x2e, 
    0x31, 0x20, 0x2d, 0x20, 0x4b, 0x65, 0x72, 0x6e, 0x65, 0x6c, 0x20, 0x53, 0x69, 0x7a, 0x65, 0x20, 
    0x39, 0x37, 0x34, 0x20, 0x62, 0x79, 0x74, 0x65, 0x73, 0x00, 
    0x00 };

void load_kernel_to_memory(uint8_t *memory) {
    segment[0].address = 0x0a00;
    segment[0].size = 190;
    segment[0].data = isr_data;
    segment[1].address = 0xe000;
    segment[1].size = 12;
    segment[1].data = kernel_routines_entry_points_data;
    segment[2].address = 0xe100;
    segment[2].size = 1338;
    segment[2].data = kernel_routines_data;
    segment[3].address = 0xf000;
    segment[3].size = 45;
    segment[3].data = kernel_data_data;
    segment[4].address = 0x0800;
    segment[4].size = 282;
    segment[4].data = main_program_data;

    for (uint8_t i=0; i<5; i++) {
        Serial.printf("Loading segment [%02d] at [%04x]. %d bytes\n", i+1, segment[i].address, segment[i].size);
        memcpy(memory+segment[i].address,segment[i].data, segment[i].size);
    };
}


