// THIS FILE IS AUTO GENERATED. DO NOT CHANGE
//

#include <pico/stdlib.h>
#include <Arduino.h>

typedef struct {
  uint16_t address;
  uint16_t size;
  uint8_t *data;
} TSegment;
TSegment segment[6];

// SEGMENT: isr @ 0x0a00
uint8_t isr_data[] = {
    0x04, 0x48, 0xda, 0x5a, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 0xa9, 
    0x14, 0x8d, 0x17, 0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 0x8d, 0x19, 0xd0, 0xa9, 0xa0, 
    0x8d, 0x1a, 0xd0, 0xa9, 0x37, 0x8d, 0x1b, 0xd0, 0x20, 0xfd, 0xe2, 0x68, 0xa5, 0x05, 0x18, 0x69, 
    0x40, 0x85, 0x05, 0xa5, 0x06, 0x69, 0x00, 0x29, 0x03, 0x85, 0x06, 0x20, 0x79, 0xe5, 0x20, 0x10, 
    0xe3, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 0xa9, 0xb4, 0x8d, 0x17, 
    0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 0x8d, 0x19, 0xd0, 0xa9, 0x3c, 0x8d, 0x1a, 0xd0, 
    0xa9, 0x2a, 0x8d, 0x1b, 0xd0, 0x20, 0xfd, 0xe2, 0x68, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 
    0x00, 0x8d, 0x16, 0xd0, 0xa9, 0x14, 0x8d, 0x17, 0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 
    0x8d, 0x19, 0xd0, 0xa9, 0xa0, 0x8d, 0x1a, 0xd0, 0xa9, 0x17, 0x8d, 0x1b, 0xd0, 0x20, 0xea, 0xe2, 
    0x68, 0xa9, 0x2b, 0x20, 0x02, 0xe2, 0xa9, 0x02, 0x20, 0xd2, 0xe1, 0xa9, 0x1a, 0x20, 0xea, 0xe1, 
    0xa9, 0x7c, 0x85, 0xe0, 0xa9, 0x08, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xa9, 0x09, 0x20, 0xd2, 0xe1, 
    0xa9, 0x17, 0x20, 0xea, 0xe1, 0xad, 0xfd, 0xd0, 0x8d, 0x30, 0xe1, 0xad, 0xfe, 0xd0, 0x8d, 0x31, 
    0xe1, 0x20, 0x68, 0xe1, 0xad, 0x34, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x33, 0xe1, 0x20, 0x8e, 0xe2, 
    0xad, 0x32, 0xe1, 0x20, 0x8e, 0xe2, 0xa9, 0x02, 0x20, 0xd2, 0xe1, 0xa9, 0x17, 0x20, 0xea, 0xe1, 
    0xa9, 0x83, 0x85, 0xe0, 0xa9, 0x08, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xa9, 0x02, 0x20, 0xd2, 0xe1, 
    0xa9, 0x18, 0x20, 0xea, 0xe1, 0xa9, 0x89, 0x85, 0xe0, 0xa9, 0x08, 0x85, 0xe1, 0x20, 0x76, 0xe2, 
    0xa9, 0x09, 0x20, 0xd2, 0xe1, 0xa9, 0x18, 0x20, 0xea, 0xe1, 0xa5, 0x02, 0x8d, 0x30, 0xe1, 0xa5, 
    0x03, 0x8d, 0x31, 0xe1, 0x20, 0x68, 0xe1, 0xad, 0x34, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x33, 0xe1, 
    0x20, 0x8e, 0xe2, 0xad, 0x32, 0xe1, 0x20, 0x8e, 0xe2, 0xce, 0x00, 0x0a, 0xd0, 0x27, 0x20, 0xa5, 
    0xe1, 0x29, 0x07, 0x69, 0x07, 0x8d, 0x00, 0x0a, 0x20, 0x0a, 0xe7, 0x90, 0x18, 0x20, 0xa5, 0xe1, 
    0x29, 0x07, 0xa8, 0xb9, 0x22, 0xe6, 0x18, 0x69, 0x08, 0x9d, 0x8b, 0xe7, 0xb9, 0x42, 0xe6, 0x18, 
    0x69, 0x04, 0x9d, 0x90, 0xe7, 0x20, 0x1f, 0xe7, 0xad, 0x22, 0xe6, 0xc9, 0x0a, 0x10, 0x08, 0xa9, 
    0x01, 0x8d, 0xb0, 0x0b, 0x4c, 0x73, 0x0b, 0xad, 0x29, 0xe6, 0xc9, 0xef, 0x30, 0x3b, 0xa9, 0xff, 
    0x8d, 0xb0, 0x0b, 0xad, 0x42, 0xe6, 0xc9, 0x96, 0x30, 0x21, 0xa0, 0x07, 0xa9, 0x20, 0x99, 0x42, 
    0xe6, 0x88, 0x10, 0xfa, 0xa0, 0x07, 0xa9, 0x30, 0x99, 0x4a, 0xe6, 0x88, 0x10, 0xfa, 0xa0, 0x07, 
    0xa9, 0x40, 0x99, 0x52, 0xe6, 0x88, 0x10, 0xfa, 0x4c, 0xa9, 0x0b, 0xa0, 0x17, 0xb9, 0x42, 0xe6, 
    0x18, 0x69, 0x04, 0x99, 0x42, 0xe6, 0x88, 0x10, 0xf4, 0xa0, 0x07, 0xb9, 0x22, 0xe6, 0x18, 0x69, 
    0x01, 0x99, 0x22, 0xe6, 0x99, 0x2a, 0xe6, 0x99, 0x32, 0xe6, 0x88, 0x10, 0xee, 0xad, 0x0d, 0xdc, 
    0x7a, 0xfa, 0x68, 0x40, 
    0x00 };

// SEGMENT: kernel_routines_entry_points @ 0xe000
uint8_t kernel_routines_entry_points_data[] = {
    0x4c, 0xc6, 0xe1, 0x4c, 0xd2, 0xe1, 0x4c, 0xea, 0xe1, 0x4c, 0x5e, 0xe2, 
    0x00 };

// SEGMENT: kernel_routines @ 0xe100
uint8_t kernel_routines_data[] = {
    0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x00, 0x16, 0x00, 
    0x00, 0x32, 0x00, 0x00, 0x64, 0x00, 0x01, 0x28, 0x00, 0x02, 0x56, 0x00, 0x05, 0x12, 0x00, 0x10, 
    0x24, 0x00, 0x20, 0x48, 0x00, 0x40, 0x96, 0x00, 0x81, 0x92, 0x01, 0x63, 0x84, 0x03, 0x27, 0x68, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xa5, 0xe0, 0x0a, 0x0a, 0x0a, 0x85, 0xe0, 0xa5, 0xe1, 0x4a, 0x4a, 
    0x4a, 0x29, 0x07, 0x05, 0xe0, 0x85, 0xe0, 0xa5, 0xe1, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x85, 0xe1, 
    0xa5, 0xe2, 0x29, 0x1f, 0x05, 0xe1, 0x85, 0xe1, 0x60, 0x48, 0x29, 0x0f, 0x85, 0xe0, 0x68, 0x48, 
    0x4a, 0x4a, 0x4a, 0x4a, 0x85, 0xe1, 0x68, 0x60, 0xf8, 0xda, 0x48, 0xa9, 0x00, 0x8d, 0x32, 0xe1, 
    0x8d, 0x33, 0xe1, 0x8d, 0x34, 0xe1, 0xa2, 0x2d, 0x0e, 0x30, 0xe1, 0x2e, 0x31, 0xe1, 0x90, 0x1c, 
    0xad, 0x32, 0xe1, 0x18, 0x7d, 0x02, 0xe1, 0x8d, 0x32, 0xe1, 0xad, 0x33, 0xe1, 0x7d, 0x01, 0xe1, 
    0x8d, 0x33, 0xe1, 0xad, 0x34, 0xe1, 0x7d, 0x00, 0xe1, 0x8d, 0x34, 0xe1, 0xca, 0xca, 0xca, 0x10, 
    0xd7, 0xd8, 0x68, 0xfa, 0x60, 0xa9, 0x1f, 0x0a, 0x49, 0x35, 0x8d, 0xa6, 0xe1, 0x6d, 0xa9, 0xe1, 
    0x8d, 0xa9, 0xe1, 0x60, 0x48, 0x29, 0xd9, 0x18, 0x69, 0x0f, 0x8d, 0xa9, 0xe1, 0x68, 0x29, 0x26, 
    0x69, 0x53, 0x8d, 0xa6, 0xe1, 0x60, 0xad, 0x11, 0xd0, 0x10, 0xfb, 0x29, 0x70, 0xaa, 0xad, 0x10, 
    0xd0, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x03, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 
    0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x68, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x04, 
    0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 
    0x68, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x07, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 
    0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x68, 0x60, 0x48, 0x8d, 0x15, 0xd0, 0xa9, 0x08, 
    0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 
    0x68, 0x60, 0xa9, 0x01, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 
    0x13, 0xd0, 0x30, 0xfb, 0xad, 0x15, 0xd0, 0x60, 0xa9, 0x02, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 
    0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0xad, 0x15, 0xd0, 0x60, 0x48, 0x8d, 
    0x15, 0xd0, 0xa9, 0x0d, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 
    0x13, 0xd0, 0x30, 0xfb, 0x68, 0x60, 0x8c, 0x8a, 0xe2, 0x8d, 0x8c, 0xe2, 0xa0, 0x00, 0xb1, 0xe0, 
    0xf0, 0x07, 0x20, 0x5e, 0xe2, 0xc8, 0x4c, 0x7e, 0xe2, 0xa0, 0x00, 0xa9, 0x00, 0x60, 0x48, 0xa9, 
    0x00, 0x85, 0xe0, 0xa9, 0xf0, 0x85, 0xe1, 0x68, 0x48, 0x4a, 0x4a, 0x4a, 0x4a, 0x29, 0x0f, 0xa8, 
    0xb1, 0xe0, 0x20, 0x5e, 0xe2, 0x68, 0x48, 0x29, 0x0f, 0xa8, 0xb1, 0xe0, 0x20, 0x5e, 0xe2, 0x68, 
    0x60, 0xa9, 0x15, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 
    0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x16, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 
    0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x0f, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 
    0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x1a, 0x8d, 0x14, 0xd0, 0xad, 
    0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x1b, 0x8d, 
    0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 
    0xa9, 0x1e, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 
    0x30, 0xfb, 0x60, 0xa9, 0x20, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 
    0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x1f, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 
    0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x1c, 0x8d, 0x14, 0xd0, 0xad, 0x13, 
    0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x1d, 0x8d, 0x14, 
    0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 
    0x21, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 
    0xfb, 0x60, 0xa9, 0x22, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 
    0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x23, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 
    0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x24, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 
    0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0x0e, 0x8d, 0x14, 0xd0, 
    0xad, 0x13, 0xd0, 0x09, 0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 
    0x00 };

// SEGMENT: space_invaders @ 0x1000
uint8_t space_invaders_data[] = {
    0x04, 0x48, 0xda, 0x5a, 0xa9, 0x29, 0x8d, 0x15, 0xd0, 0x20, 0xbb, 0xe3, 0x48, 0xa9, 0x05, 0x8d, 
    0x15, 0xd0, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 0xa9, 0x14, 0x8d, 0x17, 0xd0, 0xa9, 0xfa, 0x8d, 0x18, 
    0xd0, 0xa9, 0x00, 0x8d, 0x19, 0xd0, 0xa9, 0xa0, 0x8d, 0x1a, 0xd0, 0xa9, 0x37, 0x8d, 0x1b, 0xd0, 
    0x20, 0xfd, 0xe2, 0x68, 0xa5, 0x05, 0x18, 0x69, 0x40, 0x85, 0x05, 0xa5, 0x06, 0x69, 0x00, 0x29, 
    0x03, 0x85, 0x06, 0x20, 0x79, 0x12, 0x20, 0x10, 0xe3, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 
    0x00, 0x8d, 0x16, 0xd0, 0xa9, 0xb4, 0x8d, 0x17, 0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 
    0x8d, 0x19, 0xd0, 0xa9, 0x3c, 0x8d, 0x1a, 0xd0, 0xa9, 0x2a, 0x8d, 0x1b, 0xd0, 0x20, 0xfd, 0xe2, 
    0x68, 0x48, 0xa9, 0x05, 0x8d, 0x15, 0xd0, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 0xa9, 0x14, 0x8d, 0x17, 
    0xd0, 0xa9, 0xfa, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 0x8d, 0x19, 0xd0, 0xa9, 0xa0, 0x8d, 0x1a, 0xd0, 
    0xa9, 0x17, 0x8d, 0x1b, 0xd0, 0x20, 0xea, 0xe2, 0x68, 0xa9, 0x2b, 0x20, 0x02, 0xe2, 0xa9, 0x02, 
    0x20, 0xd2, 0xe1, 0xa9, 0x1a, 0x20, 0xea, 0xe1, 0xa9, 0x45, 0x85, 0xe0, 0xa9, 0x09, 0x85, 0xe1, 
    0x20, 0x76, 0xe2, 0xa9, 0x09, 0x20, 0xd2, 0xe1, 0xa9, 0x17, 0x20, 0xea, 0xe1, 0xad, 0xfd, 0xd0, 
    0x8d, 0x30, 0xe1, 0xad, 0xfe, 0xd0, 0x8d, 0x31, 0xe1, 0x20, 0x68, 0xe1, 0xad, 0x34, 0xe1, 0x20, 
    0x8e, 0xe2, 0xad, 0x33, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x32, 0xe1, 0x20, 0x8e, 0xe2, 0xa9, 0x02, 
    0x20, 0xd2, 0xe1, 0xa9, 0x17, 0x20, 0xea, 0xe1, 0xa9, 0x4c, 0x85, 0xe0, 0xa9, 0x09, 0x85, 0xe1, 
    0x20, 0x76, 0xe2, 0xa9, 0x02, 0x20, 0xd2, 0xe1, 0xa9, 0x18, 0x20, 0xea, 0xe1, 0xa9, 0x52, 0x85, 
    0xe0, 0xa9, 0x09, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xa9, 0x09, 0x20, 0xd2, 0xe1, 0xa9, 0x18, 0x20, 
    0xea, 0xe1, 0xa5, 0x02, 0x8d, 0x30, 0xe1, 0xa5, 0x03, 0x8d, 0x31, 0xe1, 0x20, 0x68, 0xe1, 0xad, 
    0x34, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x33, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x32, 0xe1, 0x20, 0x8e, 
    0xe2, 0xce, 0x00, 0x10, 0xd0, 0x27, 0x20, 0xa5, 0xe1, 0x29, 0x07, 0x69, 0x07, 0x8d, 0x00, 0x10, 
    0x20, 0xe3, 0x16, 0x90, 0x18, 0x20, 0xa5, 0xe1, 0x29, 0x0f, 0xa8, 0xb9, 0x78, 0x13, 0x18, 0x69, 
    0x08, 0x9d, 0x64, 0x17, 0xb9, 0x98, 0x13, 0x18, 0x69, 0x04, 0x9d, 0x69, 0x17, 0x20, 0xf8, 0x16, 
    0xad, 0x78, 0x13, 0xc9, 0x0a, 0x10, 0x08, 0xa9, 0x01, 0x8d, 0xb8, 0x11, 0x4c, 0x7b, 0x11, 0xad, 
    0x7f, 0x13, 0xc9, 0xef, 0x30, 0x3b, 0xa9, 0xff, 0x8d, 0xb8, 0x11, 0xad, 0x98, 0x13, 0xc9, 0x96, 
    0x30, 0x21, 0xa0, 0x07, 0xa9, 0x20, 0x99, 0x98, 0x13, 0x88, 0x10, 0xfa, 0xa0, 0x07, 0xa9, 0x30, 
    0x99, 0xa0, 0x13, 0x88, 0x10, 0xfa, 0xa0, 0x07, 0xa9, 0x40, 0x99, 0xa8, 0x13, 0x88, 0x10, 0xfa, 
    0x4c, 0xb1, 0x11, 0xa0, 0x17, 0xb9, 0x98, 0x13, 0x18, 0x69, 0x04, 0x99, 0x98, 0x13, 0x88, 0x10, 
    0xf4, 0xa0, 0x07, 0xb9, 0x78, 0x13, 0x18, 0x69, 0x01, 0x99, 0x78, 0x13, 0x99, 0x80, 0x13, 0x99, 
    0x88, 0x13, 0x88, 0x10, 0xee, 0xad, 0x0d, 0xdc, 0x7a, 0xfa, 0x68, 0x40, 0x48, 0xda, 0x5a, 0x48, 
    0xa9, 0x00, 0x8d, 0x15, 0xd0, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 0xa9, 0xb0, 0x8d, 0x17, 0xd0, 0xa9, 
    0x00, 0x8d, 0x18, 0xd0, 0xa9, 0x64, 0x8d, 0x19, 0xd0, 0xa9, 0x18, 0x8d, 0x1a, 0xd0, 0xa9, 0x04, 
    0x8d, 0x1b, 0xd0, 0x20, 0xfd, 0xe2, 0x68, 0xa9, 0x09, 0x20, 0xd2, 0xe1, 0xa9, 0x17, 0x20, 0xea, 
    0xe1, 0xad, 0xfd, 0xd0, 0x8d, 0x30, 0xe1, 0xad, 0xfe, 0xd0, 0x8d, 0x31, 0xe1, 0x20, 0x68, 0xe1, 
    0xad, 0x34, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x33, 0xe1, 0x20, 0x8e, 0xe2, 0xad, 0x32, 0xe1, 0x20, 
    0x8e, 0xe2, 0xa9, 0x02, 0x20, 0xd2, 0xe1, 0xa9, 0x1a, 0x20, 0xea, 0xe1, 0xa9, 0x45, 0x85, 0xe0, 
    0xa9, 0x09, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xad, 0x0d, 0xdc, 0x7a, 0xfa, 0x68, 0x40, 0xa9, 0x7f, 
    0x8d, 0x0d, 0xdc, 0xa9, 0x29, 0x8d, 0x15, 0xd0, 0x20, 0xbb, 0xe3, 0x78, 0xa9, 0x01, 0x8d, 0xfe, 
    0xff, 0xa9, 0x10, 0x8d, 0xff, 0xff, 0xa9, 0x01, 0x8d, 0xfa, 0xff, 0xa9, 0x10, 0x8d, 0xfb, 0xff, 
    0x58, 0x20, 0x9a, 0x16, 0x20, 0x68, 0x14, 0xa9, 0x84, 0x8d, 0x0d, 0xdc, 0xa9, 0xff, 0x8d, 0xff, 
    0xd0, 0x4c, 0x71, 0x12, 0xa9, 0xfe, 0x8d, 0xff, 0xd0, 0xa6, 0x06, 0xbd, 0x58, 0x14, 0x8d, 0x18, 
    0x14, 0x8d, 0x19, 0x14, 0x8d, 0x1a, 0x14, 0x8d, 0x1b, 0x14, 0x8d, 0x1c, 0x14, 0x8d, 0x1d, 0x14, 
    0x8d, 0x1e, 0x14, 0x8d, 0x1f, 0x14, 0xbd, 0x5c, 0x14, 0x8d, 0x38, 0x14, 0x8d, 0x39, 0x14, 0x8d, 
    0x3a, 0x14, 0x8d, 0x3b, 0x14, 0x8d, 0x3c, 0x14, 0x8d, 0x3d, 0x14, 0x8d, 0x3e, 0x14, 0x8d, 0x3f, 
    0x14, 0xbd, 0x60, 0x14, 0x8d, 0x20, 0x14, 0x8d, 0x21, 0x14, 0x8d, 0x22, 0x14, 0x8d, 0x23, 0x14, 
    0x8d, 0x24, 0x14, 0x8d, 0x25, 0x14, 0x8d, 0x26, 0x14, 0x8d, 0x27, 0x14, 0xbd, 0x64, 0x14, 0x8d, 
    0x40, 0x14, 0x8d, 0x41, 0x14, 0x8d, 0x42, 0x14, 0x8d, 0x43, 0x14, 0x8d, 0x44, 0x14, 0x8d, 0x45, 
    0x14, 0x8d, 0x46, 0x14, 0x8d, 0x47, 0x14, 0x60, 0x02, 0x40, 0x07, 0xe0, 0x0f, 0xf0, 0x1d, 0xb8, 
    0x17, 0xe8, 0x17, 0xe8, 0x02, 0x40, 0x06, 0x60, 0x02, 0x40, 0x07, 0xe0, 0x0f, 0xf0, 0x1d, 0xb8, 
    0x17, 0xe8, 0x07, 0xc0, 0x02, 0x60, 0x06, 0x00, 0x02, 0x40, 0x07, 0xe0, 0x0f, 0xf0, 0x1d, 0xb8, 
    0x17, 0xe8, 0x03, 0xe0, 0x06, 0x40, 0x00, 0x60, 0x00, 0x00, 0x04, 0x40, 0x03, 0x80, 0x07, 0xc0, 
    0x05, 0x40, 0x07, 0xc0, 0x0a, 0xa0, 0x0a, 0xa0, 0x00, 0x00, 0x04, 0x40, 0x03, 0x80, 0x07, 0xc0, 
    0x05, 0x40, 0x07, 0xc0, 0x0a, 0xa0, 0x15, 0x40, 0x00, 0x00, 0x04, 0x40, 0x03, 0x80, 0x07, 0xc0, 
    0x05, 0x40, 0x07, 0xc0, 0x0a, 0xa0, 0x05, 0x50, 0x00, 0x00, 0x04, 0x40, 0x0f, 0xe0, 0x19, 0x30, 
    0x1f, 0xf0, 0x1f, 0xf0, 0x15, 0x50, 0x0a, 0xa0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
    0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa2, 0x00, 0xa9, 0xe8, 0x9d, 0x18, 0x14, 0xa9, 
    0x12, 0x9d, 0x38, 0x14, 0xa2, 0x08, 0xa9, 0x18, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 
    0xa2, 0x10, 0xa9, 0x48, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x01, 0xa9, 0xe8, 
    0x9d, 0x18, 0x14, 0xa9, 0x12, 0x9d, 0x38, 0x14, 0xa2, 0x09, 0xa9, 0x18, 0x9d, 0x18, 0x14, 0xa9, 
    0x13, 0x9d, 0x38, 0x14, 0xa2, 0x11, 0xa9, 0x48, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 
    0xa2, 0x02, 0xa9, 0xe8, 0x9d, 0x18, 0x14, 0xa9, 0x12, 0x9d, 0x38, 0x14, 0xa2, 0x0a, 0xa9, 0x18, 
    0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x12, 0xa9, 0x48, 0x9d, 0x18, 0x14, 0xa9, 
    0x13, 0x9d, 0x38, 0x14, 0xa2, 0x03, 0xa9, 0xe8, 0x9d, 0x18, 0x14, 0xa9, 0x12, 0x9d, 0x38, 0x14, 
    0xa2, 0x0b, 0xa9, 0x18, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x13, 0xa9, 0x48, 
    0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x04, 0xa9, 0xe8, 0x9d, 0x18, 0x14, 0xa9, 
    0x12, 0x9d, 0x38, 0x14, 0xa2, 0x0c, 0xa9, 0x18, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 
    0xa2, 0x14, 0xa9, 0x48, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x05, 0xa9, 0xe8, 
    0x9d, 0x18, 0x14, 0xa9, 0x12, 0x9d, 0x38, 0x14, 0xa2, 0x0d, 0xa9, 0x18, 0x9d, 0x18, 0x14, 0xa9, 
    0x13, 0x9d, 0x38, 0x14, 0xa2, 0x15, 0xa9, 0x48, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 
    0xa2, 0x06, 0xa9, 0xe8, 0x9d, 0x18, 0x14, 0xa9, 0x12, 0x9d, 0x38, 0x14, 0xa2, 0x0e, 0xa9, 0x18, 
    0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x16, 0xa9, 0x48, 0x9d, 0x18, 0x14, 0xa9, 
    0x13, 0x9d, 0x38, 0x14, 0xa2, 0x07, 0xa9, 0xe8, 0x9d, 0x18, 0x14, 0xa9, 0x12, 0x9d, 0x38, 0x14, 
    0xa2, 0x0f, 0xa9, 0x18, 0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x17, 0xa9, 0x48, 
    0x9d, 0x18, 0x14, 0xa9, 0x13, 0x9d, 0x38, 0x14, 0xa2, 0x00, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 
    0x58, 0x13, 0xa2, 0x01, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x02, 0xbd, 0x58, 
    0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x03, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 
    0xa2, 0x04, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x05, 0xbd, 0x58, 0x13, 0x05, 
    0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x06, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x07, 
    0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x08, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 
    0x58, 0x13, 0xa2, 0x09, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x0a, 0xbd, 0x58, 
    0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x0b, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 
    0xa2, 0x0c, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x0d, 0xbd, 0x58, 0x13, 0x05, 
    0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x0e, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x0f, 
    0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x10, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 
    0x58, 0x13, 0xa2, 0x11, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x12, 0xbd, 0x58, 
    0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x13, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 
    0xa2, 0x14, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x15, 0xbd, 0x58, 0x13, 0x05, 
    0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x16, 0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa2, 0x17, 
    0xbd, 0x58, 0x13, 0x05, 0xc0, 0x9d, 0x58, 0x13, 0xa9, 0x58, 0x8d, 0x15, 0xd0, 0xa9, 0x13, 0x8d, 
    0x16, 0xd0, 0xa9, 0x20, 0x8d, 0x17, 0xd0, 0xa9, 0x17, 0x8d, 0x14, 0xd0, 0xad, 0x13, 0xd0, 0x09, 
    0x80, 0x8d, 0x13, 0xd0, 0x2c, 0x13, 0xd0, 0x30, 0xfb, 0x60, 0xa9, 0xe8, 0x8d, 0x58, 0x14, 0x8d, 
    0x5a, 0x14, 0xa9, 0x12, 0x8d, 0x5c, 0x14, 0x8d, 0x5e, 0x14, 0xa9, 0xf8, 0x8d, 0x59, 0x14, 0xa9, 
    0x12, 0x8d, 0x5d, 0x14, 0xa9, 0x08, 0x8d, 0x5b, 0x14, 0xa9, 0x13, 0x8d, 0x5f, 0x14, 0xa9, 0x18, 
    0x8d, 0x60, 0x14, 0x8d, 0x62, 0x14, 0xa9, 0x13, 0x8d, 0x64, 0x14, 0x8d, 0x66, 0x14, 0xa9, 0x28, 
    0x8d, 0x61, 0x14, 0xa9, 0x13, 0x8d, 0x65, 0x14, 0xa9, 0x38, 0x8d, 0x63, 0x14, 0xa9, 0x13, 0x8d, 
    0x67, 0x14, 0x60, 0xa2, 0x04, 0xbd, 0x5f, 0x17, 0x30, 0x09, 0x09, 0x80, 0x9d, 0x5f, 0x17, 0x38, 
    0x4c, 0xf7, 0x16, 0xca, 0x10, 0xef, 0x18, 0x60, 0x20, 0x02, 0x17, 0x20, 0x17, 0x17, 0x20, 0x31, 
    0x17, 0x60, 0xa2, 0x05, 0xbd, 0x5f, 0x17, 0x10, 0x0a, 0xbd, 0x69, 0x17, 0x18, 0x7d, 0x6e, 0x17, 
    0x9d, 0x69, 0x17, 0xca, 0x10, 0xee, 0x60, 0xa2, 0x04, 0xbd, 0x5f, 0x17, 0x10, 0x0f, 0xbd, 0x69, 
    0x17, 0xc9, 0xaa, 0x30, 0x08, 0xbd, 0x5f, 0x17, 0x29, 0x7f, 0x9d, 0x5f, 0x17, 0xca, 0x10, 0xe9, 
    0x60, 0xa9, 0x00, 0x8d, 0x16, 0xd0, 0xa9, 0x04, 0x8d, 0x18, 0xd0, 0xa9, 0x00, 0x8d, 0x19, 0xd0, 
    0xa9, 0x17, 0x8d, 0x1a, 0xd0, 0xa2, 0x04, 0xbd, 0x5f, 0x17, 0x10, 0x0f, 0xbd, 0x64, 0x17, 0x8d, 
    0x15, 0xd0, 0xbd, 0x69, 0x17, 0x8d, 0x17, 0xd0, 0x20, 0xc4, 0xe2, 0xca, 0x10, 0xe9, 0x60, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x02, 0x02, 
    0x02, 0x02, 0x02, 
    0x00 };

// SEGMENT: kernel_data @ 0xf000
uint8_t kernel_data_data[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 
    0x57, 0x65, 0x6c, 0x63, 0x6f, 0x6d, 0x65, 0x20, 0x74, 0x6f, 0x20, 0x46, 0x69, 0x72, 0x73, 0x74, 
    0x4b, 0x6c, 0x61, 0x61, 0x73, 0x20, 0x4f, 0x53, 0x20, 0x76, 0x30, 0x2e, 0x31, 
    0x00 };

// SEGMENT: main_program @ 0x0800
uint8_t main_program_data[] = {
    0xa2, 0xff, 0x9a, 0xad, 0x13, 0xd0, 0x09, 0x0c, 0x8d, 0x13, 0xd0, 0xa9, 0x29, 0x8d, 0x15, 0xd0, 
    0x20, 0xbb, 0xe3, 0xa9, 0x2e, 0x20, 0x02, 0xe2, 0xa9, 0x02, 0x20, 0xd2, 0xe1, 0xa9, 0x01, 0x20, 
    0xea, 0xe1, 0xa9, 0x22, 0x85, 0xe0, 0xa9, 0x09, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xa9, 0x1f, 0x20, 
    0x02, 0xe2, 0xa9, 0x0a, 0x20, 0xd2, 0xe1, 0xa9, 0x0a, 0x20, 0xea, 0xe1, 0xa9, 0x58, 0x85, 0xe0, 
    0xa9, 0x09, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xa9, 0x0a, 0x20, 0xd2, 0xe1, 0xa9, 0x0c, 0x20, 0xea, 
    0xe1, 0xa9, 0x69, 0x85, 0xe0, 0xa9, 0x09, 0x85, 0xe1, 0x20, 0x76, 0xe2, 0xa9, 0xaa, 0x8d, 0xfe, 
    0xff, 0x8d, 0xfa, 0xff, 0xa9, 0x08, 0x8d, 0xff, 0xff, 0x8d, 0xfb, 0xff, 0xa9, 0x88, 0x8d, 0x0d, 
    0xdc, 0xad, 0x93, 0x08, 0x10, 0xfb, 0xa9, 0x12, 0x8d, 0xff, 0xd0, 0xa9, 0x00, 0x8d, 0x93, 0x08, 
    0xa9, 0x22, 0x8d, 0x15, 0xd0, 0x20, 0xbb, 0xe3, 0x4c, 0x3e, 0x12, 0x4c, 0x8b, 0x08, 0x6c, 0x91, 
    0x08, 0x00, 0x00, 0x00, 0xa9, 0xf0, 0x8d, 0x05, 0xdc, 0xa9, 0x00, 0x8d, 0x04, 0xdc, 0xa9, 0x81, 
    0x8d, 0x0d, 0xdc, 0xa9, 0x11, 0x8d, 0x0e, 0xdc, 0x60, 0x00, 0x48, 0xda, 0x5a, 0xa9, 0x55, 0x8d, 
    0xff, 0xd0, 0xad, 0x0d, 0xdc, 0x8d, 0xa9, 0x08, 0x8d, 0xff, 0xd0, 0xa9, 0x04, 0x2c, 0xa9, 0x08, 
    0xf0, 0x08, 0xa9, 0x66, 0x8d, 0xff, 0xd0, 0x4c, 0xf7, 0x08, 0xa9, 0x08, 0x2c, 0xa9, 0x08, 0xf0, 
    0x0b, 0xa9, 0x77, 0x8d, 0xff, 0xd0, 0x20, 0xfb, 0x08, 0x4c, 0xf7, 0x08, 0xa9, 0x01, 0x2c, 0xa9, 
    0x08, 0xf0, 0x08, 0xa9, 0x88, 0x8d, 0xff, 0xd0, 0x4c, 0xf7, 0x08, 0xa9, 0x02, 0x2c, 0xa9, 0x08, 
    0xf0, 0x05, 0xa9, 0x99, 0x8d, 0xff, 0xd0, 0x7a, 0xfa, 0x68, 0x40, 0xad, 0x10, 0xd0, 0xc9, 0x32, 
    0xd0, 0x1f, 0xa9, 0xea, 0x8d, 0xff, 0xd0, 0xa9, 0x7f, 0x8d, 0x0d, 0xdc, 0xa9, 0x20, 0x8d, 0x15, 
    0xd0, 0x20, 0xbb, 0xe3, 0xa9, 0x3f, 0x8d, 0x15, 0xd0, 0x20, 0xbb, 0xe3, 0xa9, 0x80, 0x8d, 0x93, 
    0x08, 0x60, 0x4e, 0x45, 0x2f, 0x4f, 0x53, 0x20, 0x76, 0x30, 0x2e, 0x31, 0x20, 0x2d, 0x20, 0x46, 
    0x69, 0x72, 0x73, 0x74, 0x4b, 0x6c, 0x61, 0x61, 0x73, 0x20, 0x45, 0x78, 0x70, 0x65, 0x72, 0x69, 
    0x65, 0x6e, 0x63, 0x65, 0x00, 0x46, 0x52, 0x41, 0x4d, 0x45, 0x3a, 0x00, 0x4c, 0x45, 0x56, 0x45, 
    0x4c, 0x00, 0x53, 0x43, 0x4f, 0x52, 0x45, 0x00, 0x5b, 0x31, 0x5d, 0x20, 0x4c, 0x6f, 0x61, 0x64, 
    0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x00, 0x5b, 0x32, 0x5d, 0x20, 0x50, 0x6c, 0x61, 
    0x79, 0x20, 0x53, 0x70, 0x61, 0x63, 0x65, 0x20, 0x49, 0x6e, 0x76, 0x61, 0x64, 0x65, 0x72, 0x73, 
    0x00, 
    0x00 };

void load_kernel_to_memory(uint8_t *memory) {
    segment[0].address = 0x0a00;
    segment[0].size = 452;
    segment[0].data = isr_data;
    segment[1].address = 0xe000;
    segment[1].size = 12;
    segment[1].data = kernel_routines_entry_points_data;
    segment[2].address = 0xe100;
    segment[2].size = 718;
    segment[2].data = kernel_routines_data;
    segment[3].address = 0x1000;
    segment[3].size = 1907;
    segment[3].data = space_invaders_data;
    segment[4].address = 0xf000;
    segment[4].size = 45;
    segment[4].data = kernel_data_data;
    segment[5].address = 0x0800;
    segment[5].size = 385;
    segment[5].data = main_program_data;

    for (uint8_t i=0; i<6; i++) {
        Serial.printf("Loading segment [%02d] at [%04x]. %d bytes\n", i+1, segment[i].address, segment[i].size);
        memcpy(memory+segment[i].address,segment[i].data, segment[i].size);
    };
}


