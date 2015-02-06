#ifndef GLCD_LOW_H
#define GLCD_LOW_H

// GLCD uC specifican dio

// *************************************** sys includes *******************************************
#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_spi.h"
#endif
#ifdef STM32F4XX
	//#include "stm32f4xx_rcc.h"
	//#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_spi.h"
#endif
#include "spi.h"
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
/*
#define GLCD_LED_PORT	GPIOB
#define GLCD_LED_PIN	GPIO_Pin_0	// PB0
#define GLCD_DC_PORT	GPIOB
#define GLCD_DC_PIN	GPIO_Pin_1	// PB1
#define GLCD_RESET_PORT GPIOB
#define GLCD_RESET_PIN	GPIO_Pin_2	// PB2
#define GLCD_CS_PORT	GPIOB
#define GLCD_CS_PIN	GPIO_Pin_13	// PB10
*/
// STM32F4
#define GLCD_LED_PORT	GPIOD
#define GLCD_LED_PIN	GPIO_Pin_0	// PD0	// brown
#define GLCD_DC_PORT	GPIOD
#define GLCD_DC_PIN	GPIO_Pin_1	// PD1	// gray
#define GLCD_RESET_PORT GPIOD
#define GLCD_RESET_PIN	GPIO_Pin_2	// PD2	// purple
#define GLCD_CS_PORT	GPIOD
#define GLCD_CS_PIN	GPIO_Pin_3	// PD3	// blue
// *************************************** variables **********************************************

// *************************************** function prototypes ************************************

void glcd_io_init(void);
void glcd_spi_init(void);
uint8_t glcd_spi_send(uint8_t byte);
uint16_t glcd_spi_send16(uint16_t HalfWord);
//void glcd_write_dma(uint16_t *buf, uint16_t len);
//void glcd_write_dma(uint16_t *buf, uint32_t len);
void glcd_write_dma(const uint16_t *buf, uint16_t len);
//void glcd_write_dma(uint32_t *buf, uint32_t len);

/*
inline static void glcd_cs_low(void);
inline static void glcd_cs_high(void);
inline static void glcd_dc_low(void);
inline static void glcd_dc_high(void);
*/
/*
void glcd_cs_low(void);
void glcd_cs_high(void);
void glcd_dc_low(void);
void glcd_dc_high(void);
void glcd_led_off(void);
void glcd_led_on(void);
void glcd_rst_off(void);
void glcd_rst_on(void);
*/
#define glcd_dc_low(void)	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 0);
#define glcd_dc_high(void)	GPIO_WriteBit(GLCD_DC_PORT, GLCD_DC_PIN, 1);
#define glcd_cs_low(void)	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 0);
#define glcd_cs_high(void)	GPIO_WriteBit(GLCD_CS_PORT, GLCD_CS_PIN, 1);
#define glcd_led_off(void)	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 0);
#define glcd_led_on(void)	GPIO_WriteBit(GLCD_LED_PORT, GLCD_LED_PIN, 1);
#define glcd_rst_off(void)	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 1);
#define glcd_rst_on(void)	GPIO_WriteBit(GLCD_RESET_PORT, GLCD_RESET_PIN, 0);

#endif
