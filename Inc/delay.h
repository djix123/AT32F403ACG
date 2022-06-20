#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "at32f403a_407.h"

//void delay_init(void);
//void delay_us(uint32_t nus);
//void delay_ms(uint16_t nms);
//void delay_sec(uint16_t sec);

void systick_config(void);
void delay_decrement(void);
void delay_ms(uint32_t count);

#ifdef __cplusplus
}
#endif

#endif
