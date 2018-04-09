#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

uint32_t getWord(unsigned char *str);
void intToString(int64_t value, char * pBuf, uint32_t len, uint32_t base, uint8_t zeros);
void floatToString(float value, char *pBuf, uint32_t len, uint32_t base, uint8_t zeros, uint8_t precision);

#endif