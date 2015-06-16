// created 150530
// WS2812 driver
#ifndef LED_ARRAY_H
#define LED_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dma.h"

#define T0H	0.35	// us
#define T0L	0.8
#define T1H	0.7
#define T1L	0.6
#define TRES	50	// 50+ us

//#define SIG0	T0H + T0L
//#define SIG1	T1H + T1L
// define SIG_RESET	TRES low

void led_array_init(void);
void stopwatch_delay(uint32_t ticks);

int led_main(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// LED_ARRAY_H

/*
 *
 * The WS2811/12 parts have DIN (Data In) and DOUT (Data Out) signals so they can be simply connected in serial ("daisy-chained"). Each part keeps the first 24 bits that it sees on its DIN pin and retransmits any additional data out on its DOUT pin, as illustrated in Figure 8.
 * Once the data stream starts, each part expects to see a continuous stream of data. If the data signal does not have a rising edge for more than 50 µs, the part latches the data, and starts to look for the next 24 bits of data as its own, and retransmits the rest.
 *
 */
