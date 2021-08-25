#ifndef _LOGGING_H
#define _LOGGING_H

#include "stm32f4xx.h"

void enableLogging();
void print(char* str, uint32_t data, uint8_t base);

enum base {DEC, HEX, BIN};
#endif