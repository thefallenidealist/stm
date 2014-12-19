// created 141205

#include "oled.h"
#include <stdio.h>
#include "delay.h"
#include <stdbool.h>

#define SSD1306_LCDWIDTH      128
#define SSD1306_LCDHEIGHT      64
#define SSD1306_SETCONTRAST   0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP	0xA0
#define SSD1306_CHARGEPUMP	0x8D
#define SSD1306_EXTERNALVCC	0x1
#define SSD1306_SWITCHCAPVCC	0x2

uint8_t a[] = {0b01001100, 0b10010010, 0b10010010, 0b10010010, 0b01111110};

void ssd1306_command(uint8_t cmd)
{
    uint8_t control = 0x00; // some use 0X00 other examples use 0X80. I tried both 
    i2c_start();
    i2c_write(OLED_ADDR_W);
    i2c_write(control); // This is Command
    i2c_write(cmd);
    i2c_stop();
}

void  ssd1306_data(uint8_t cmd)
{
    i2c_start();
    i2c_write(OLED_ADDR_W);
    i2c_write(0X40); // This byte is DATA
    i2c_write(cmd);
    i2c_stop();
}

void oled_io_init(void)
{
	printf("oled_io_init pocetak\n");
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // SCL, SDA
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	//I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	//I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1,&I2C_InitStruct);

	printf("oled_io_init kraj\n");
}

//void ssd1306_setXY(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1)
void ssd1306_setXY(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	if(x1<128)
	{
		ssd1306_command(0x21);	// column
		ssd1306_command(x0);
		ssd1306_command(x1);
	}
	else
		printf("ssd1306_setXY(): x1 larger than 128\n");

	if(y1<64)
	{
		ssd1306_command(0x22);	// row
		ssd1306_command(y0);
		ssd1306_command(y1);
	}
	else
		printf("ssd1306_setXY(): y1 larger than 64\n");
}

void ssd1306_fillRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color)
{
	ssd1306_setXY(x0, y0, x1, y1);

	i2c_start();
	i2c_write(OLED_ADDR_W);
	i2c_write(0X40); // data not command

	uint16_t count = (x1 - x0) * (y1 - y0) /8;
	printf("ssd1306_fillRectangle(): count: %d\n", count);

	for(uint8_t i=0; i<count ; i++)
		if(color)
		{
			i2c_write(0xFF);

		}
		else
			i2c_write(0x00);

	i2c_stop();
}

void crtaj_a(void)
{
	//uint8_t t = 
}

void ssd1306_bg(bool arg)
{
	ssd1306_setXY(0, 0, 127, 63);

	i2c_start();
	i2c_write(OLED_ADDR_W);
	i2c_write(0X40); // data not command

	for(uint16_t z=0; z<128*64/8; z++)
		if(arg)
			i2c_write(0xFF);
		else
			i2c_write(0x00);
	i2c_stop();
}

uint32_t oled_init()
{
	printf("oled_init() pocetak\n");

	// Init sequence for 128x64 OLED module
	ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
	ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
	ssd1306_command(0x80);                			// the suggested ratio 0x80
	ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
	ssd1306_command(0x3F);
	ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
	ssd1306_command(0x0);                                   // no offset
	ssd1306_command(SSD1306_SETSTARTLINE);// | 0x0);        // line #0
	ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
	ssd1306_command(0x14); 					// using internal VCC
	ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
	ssd1306_command(0x00);					// 0x00 horizontal addressing
	ssd1306_command(SSD1306_SEGREMAP | 0x1);		// rotate screen 180
	ssd1306_command(SSD1306_COMSCANDEC);			// rotate screen 180
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x12);
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	ssd1306_command(0xCF);
	ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
	ssd1306_command(0xF1);
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
	ssd1306_command(0x40);
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
	ssd1306_command(SSD1306_DISPLAYON);                     //switch on OLED

	printf("oled_init() kraj\n");

	ssd1306_bg(0);
	ssd1306_bg(1);
	//ssd1306_bg(0);
	ssd1306_fillRectangle(30,30,50,50,0);

	return 0;
}
