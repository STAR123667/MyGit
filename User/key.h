#ifndef __KEY_H
#define __KEY_H
#include "include.h"
uint8_t GetKeyNum(void);
void ScanKeyDealwith(uint8_t knum);
void gpio_toggle_bits(uint32_t gpio_periph,uint32_t pin);
void motor_frequencyAdj(uint8_t adjNum);
#endif /* __KEY_H */
