#ifndef YUY2_TO_RGB_H
#define YUY2_TO_RGB_H

#include <stdint.h>
#include <stdlib.h>

void yuy2_to_rgb          (const uint8_t* yuy2, uint8_t* rgb, size_t n_pixels);
void yuy2_to_rgb_threaded (const uint8_t* yuy2, uint8_t* rgb, size_t n_pixels);

#endif // YUY2_TO_RGB_H
