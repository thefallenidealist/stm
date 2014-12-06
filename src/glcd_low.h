#ifndef GLCD_LOW_H
#define GLCD_LOW_H

// GLCD uC specifican dio

// *************************************** sys includes *******************************************
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
// *************************************** local includes *****************************************
//#include "glcd.c"
// *************************************** defines ************************************************

/*
#if !defined (GLCD_SPI1) || !defined GLCD_SPI2
	#define GLCD_SPI1
#endif
*/

//#ifdef GLCD_SPI1
  #define SPI1_PORT	GPIOA
  #define SPI1_SCK	GPIO_Pin_5	// PA5
  #define SPI1_MOSI	GPIO_Pin_7	// PA7
//#endif

/*
#ifdef GLCD_SPI2
  // GLCD SPI2
  #define SPI2_PORT	GPIOB
  #define SPI2_SCK	GPIO_Pin_13
  #define SPI2_MOSI	GPIO_Pin_15
#endif
*/

// zajednicko za SPI1 i SPI2
#define GLCD_LED_PORT	GPIOB
#define GLCD_LED_PIN	GPIO_Pin_0	// PB0
#define GLCD_DC_PORT	GPIOB
#define GLCD_DC_PIN	GPIO_Pin_1	// PB1
#define GLCD_RESET_PORT GPIOB
#define GLCD_RESET_PIN	GPIO_Pin_2	// PB2
#define GLCD_CS_PORT	GPIOB
#define GLCD_CS_PIN	GPIO_Pin_10	// PB10
// *************************************** variables **********************************************

// *************************************** function prototypes ************************************

void glcd_io_init();
void glcd_spi_init();
uint8_t glcd_spi_send(uint8_t byte);
uint16_t glcd_spi_send16(uint16_t HalfWord);
/*
inline static void glcd_cs_low();
inline static void glcd_cs_high();
inline static void glcd_dc_low();
inline static void glcd_dc_high();
*/
/*
void glcd_cs_low();
void glcd_cs_high();
void glcd_dc_low();
void glcd_dc_high();
void glcd_led_off();
void glcd_led_on();
void glcd_rst_off();
void glcd_rst_on();
*/
#define glcd_dc_low()	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 0);
#define glcd_dc_high()	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 1);
#define glcd_cs_low()	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 0);
#define glcd_cs_high()	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 1);
#define glcd_led_off()	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 0);
#define glcd_led_on()	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 1);
#define glcd_rst_off()	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 1);
#define glcd_rst_on()	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 0);

#endif
