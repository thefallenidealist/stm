#include "oled_novo.h"

#define OLED_RESOLUTION_X	128
#define OLED_RESOLUTION_Y	64

#define OLED_ADDR_W			0x78

// XXX jebote, odakle mi ovo dolje
#define OLED_CMD			0x22
#define OLED_DATA			0x40


// 1. Fundamental Command Table 
#define OLED_SET_CONTRAST	0x81	// after that send 8b contrast value
#define OLED_SUSPEND_ON		0xA4	// Output follows RAM content   default after reset
#define OLED_SUSPEND_OFF	0xA5
#define OLED_INVERSE_OFF	0xA6	// 0 is off, 1 is on		default after reset
#define OLED_INVERSE_ON		0xA7
#define OLED_DISPLAY_ON		0xAF
#define OLED_DISPLAY_OFF	0xAE	// sleep mode, default after reset
// 2. Scrolling Command Table TODO
// 3. Addressing Setting Commands
#define OLED_SET_COLUMN_LOWER	0x00
#define OLED_SET_COLUMN_HIGHER	0x10
#define OLED_SET_MEMORY_ADDRESSING_MODE	0x20
#define OLED_SET_COLUMN_ADDRESS			0x20
#define OLED_SET_PAGE_ADDRESS			0x22
#define OLED_SET_PAGE_START_ADDRESS		0xB0
// 4. Hardware Configuration (Panel resolution & layout related) Command Table
#define OLED_SET_DISPLAY_START_LINE		0x40
#define OLED_SET_SEGMENT_REMAP			0xA0
#define OLED_SET_MULTIPLEX_RATIO		0xA8
#define OLED_SCAN_MODE					0xC0
#define OLED_SET_DISPLAY_OFFSET			0xD3
#define OLED_SET_COM_PINS				0xDA
// 5. Timing & Driving Scheme Setting Command Table 
#define	OLED_SET_DIV_OR_FREQ			0xD5
#define OLED_SET_PRECHARGE_PERIOD		0xD9
#define OLED_VCOMH_DESELECT_LEVEL		0xDB
#define OLED_NOP						0xE3

// INFO uvijek salje ACK na write
/*
 * GRAM
 * PAGE0..PAGE7			PAGE0(COM0..COM7)
 *
 */
// I2C moze samo pisat jer je WR pin =0 u I2C modu
// When “SDAOUT” pin is disconnected, the acknowledgement signal will be ignored in the I2C-bus.  
 I

uint8_t g_oled_mode = OLED_MODE_INVALID;

/*************************************************************************************************
				oled_io_init()
*************************************************************************************************/
void oled_io_init(void)
{
	i2c_init(2,100000);
}

/*************************************************************************************************
				oled_init()
*************************************************************************************************/
void oled_init(void)
{
	//oled_display_on();

	// datasheet, page 64
	oled_write_cmd(0xA8);
	oled_write_cmd(0x3F);
	oled_write_cmd(0xD3);	// display offset
	oled_write_cmd(0x00);
	oled_write_cmd(0x40);	// start line
	oled_write_cmd(0xA1);	// segment remap		A0 ili A1
	oled_write_cmd(0xC8);	// scan direction		C0 ili C8
	oled_write_cmd(0xDA);	// COM pins hardware configuration
	oled_write_cmd(0x02);	
	oled_write_cmd(0x81);	// contrast
	oled_write_cmd(0x7F);
	oled_write_cmd(0xA4);	// disable entire display on
	oled_write_cmd(0xa6);	// normal display
	oled_write_cmd(0xD5);	// oscil frequency
	oled_write_cmd(0x80);
	oled_write_cmd(0x8D);	// charge pump
	oled_write_cmd(0xAF);	// display on


}

/*************************************************************************************************
				oled_write_cmd()
*************************************************************************************************/
void oled_write_cmd(uint8_t cmd)
{
	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	i2c_write(2, cmd);
	i2c_stop(2);
}

/*************************************************************************************************
				oled_write_data()
*************************************************************************************************/
void oled_write_data(uint8_t data)
{
	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_DATA);
	i2c_write(2, data);
	i2c_stop(2);
}

/*************************************************************************************************
				oled_set_contrast()
*************************************************************************************************/
void oled_set_contrast(uint8_t contrast)
{
	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	i2c_write(2, OLED_SET_CONTRAST);
	i2c_write(2, contrast);
	i2c_stop(2);

}

/*************************************************************************************************
				oled_resume()
*************************************************************************************************/
void oled_suspend(bool suspend)
{
	if (suspend == 1)
	{
		oled_write_cmd(OLED_SUSPEND_ON);
	}
	else
	{
		oled_write_cmd(OLED_SUSPEND_OFF);
	}
}

/*************************************************************************************************
				oled_inverse()
*************************************************************************************************/
void oled_inverse(bool arg)
{
	if (arg == 1)
	{
		oled_write_cmd(OLED_INVERSE_ON);
	}
	else
	{
		oled_write_cmd(OLED_INVERSE_OFF);
	}
}

/*************************************************************************************************
				oled_display_on()
*************************************************************************************************/
void oled_display_on(void)
{
	// TODO RESET	low, RESET high (at least 3us)
	// page 27
	oled_write_cmd(OLED_DISPLAY_ON);
	delay_ms(100);	// TODO doista potrebno?
}

/*************************************************************************************************
				oled_display_off()
*************************************************************************************************/
void oled_display_off(void)
{
	oled_write_cmd(OLED_DISPLAY_OFF);
	//delay_ms(100);
}

/*************************************************************************************************
				oled_setXY
*************************************************************************************************/
void oled_setXY(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1)
{
	// TODO provjere jesu kordinate ispravne
	oled_write_cmd(x0);
	oled_write_cmd(x1);

	oled_write_cmd(y0);
	oled_write_cmd(y1);
}

/*************************************************************************************************
				oled_set_mode()
*************************************************************************************************/
void oled_set_mode(oled_mode_t mode)
{
	if (mode > OLED_MODE_INVALID)
	{
		printf("%s(): Zajeb, wrong mode: %d, exiting.\n", __func__, mode);
		return;
	}
	oled_write_cmd(OLED_SET_MEMORY_ADDRESSING_MODE | mode);
	g_oled_mode = mode;
}

/*************************************************************************************************
				oled_get_mode()
*************************************************************************************************/
oled_mode_t oled_get_mode(void)
{
	return g_oled_mode;
}

/*************************************************************************************************
				oled_set_column_lower()
*************************************************************************************************/
void oled_set_column_lower(uint8_t column)
{
	oled_mode_t mode = oled_get_mode();
	if (mode != OLED_MODE_PAGE_ADDRESSING)
	{
		printf("%s(): This command is only for page addressing mode. Exiting\n", __func__);
	}
	// samo 4 bita
	if (column > 0b1111)
	{
		printf("%s(): Zajeb, lower column (%d) larger than %d, exiting\n", __func__, column, 0b1111);
	}

	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	i2c_write(2, OLED_SET_COLUMN_LOWER | column);
	i2c_stop(2);
}


/*************************************************************************************************
				oled_set_column_higher()
*************************************************************************************************/
void oled_set_column_higher(uint8_t column)
{
	oled_mode_t mode = oled_get_mode();
	if (mode != OLED_MODE_PAGE_ADDRESSING)
	{
		printf("%s(): This command is only for page addressing mode. Exiting\n", __func__);
	}
	// samo 4 bita
	if (column > 0b1111)
	{
		printf("%s(): Zajeb, higher column (%d) larger than %d, exiting\n", __func__, column, 0b1111);
	}

	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	i2c_write(2, OLED_SET_COLUMN_HIGHER | column);
	i2c_stop(2);
}
/*************************************************************************************************
				oled_set_column()
*************************************************************************************************/
void oled_set_column(uint8_t start, uint8_t end)
{
	oled_mode_t mode = oled_get_mode();
	if ( (mode != OLED_MODE_HORIZONTAL_ADDRESSING) || (mode != OLED_MODE_VERTICAL_ADDRESSING) )
	{
		printf("%s(): This command is only for horizontal or vertical addressing mode. Exiting\n", __func__);
	}
	if (end > 127)
	{
		printf("%s(): Zajeb, end column (%d) larger than 127, exiting\n", __func__, end);
		return ;
	}

	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	//i2c_write(2, OLED_SET_COLUMN | start);
	i2c_write(2, OLED_SET_COLUMN_ADDRESS | start);
	i2c_write(2, start);
	i2c_write(2, end);
	i2c_stop(2);
}

/*************************************************************************************************
				oled_
*************************************************************************************************/
void oled_set_page(uint8_t start, uint8_t end)
{
	oled_mode_t mode = oled_get_mode();
	if ( (mode != OLED_MODE_HORIZONTAL_ADDRESSING) || (mode != OLED_MODE_VERTICAL_ADDRESSING) )
	{
		printf("%s(): This command is only for horizontal or vertical addressing mode. Exiting\n", __func__);
	}
	if ( (start > 7) || (end > 7) )
	{
		printf("%s(): Zajeb, page start (%d) or end (%d) larger than 7, exiting\n", __func__, start, end);
		return ;
	}

	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	i2c_write(2, OLED_SET_PAGE_ADDRESS | start);
	i2c_write(2, start);
	i2c_write(2, end);
	i2c_stop(2);
}

/*************************************************************************************************
				oled_set_page_start()
*************************************************************************************************/
void oled_set_page_start(uint8_t page)
{
	// Set GDDRAM Page Start Address PAGE0~PAGE7) for Page Addressing Mode 
	// This command is only for page addressing mode
	if (page > 7)	// 3 bita
	{
		printf("%s(): page (%d) larger than 7, exiting\n", __func__, page);
		return ;
	}
	oled_write_cmd(OLED_SET_PAGE_START_ADDRESS | page);
}

/*************************************************************************************************
				oled_
*************************************************************************************************/

/*************************************************************************************************
				oled_
*************************************************************************************************/

/*************************************************************************************************
				oled_
*************************************************************************************************/

/*************************************************************************************************
				oled_
*************************************************************************************************/

/*************************************************************************************************
				oled_
*************************************************************************************************/

/*************************************************************************************************
				oled_
*************************************************************************************************/

/*************************************************************************************************
				oled_example()
*************************************************************************************************/
void oled_example()
{
	printf("%s() pocetak\n", __func__);

	oled_io_init();
	oled_init();

	oled_display_on();

	for (uint8_t i=0; i<2; i++)
	{
		oled_bg(0);
		delay_s(1);
		oled_bg(1);
		delay_s(1);
	}

	//oled_suspend(0);
	//oled_inverse(1);
	//oled_suspend(1);

	//oled_set_mode(OLED_MODE_PAGE_ADDRESSING);
	//printf("OLED mode: %d\n", oled_get_mode());

	/*
	oled_setXY(0,0,64,32);

	for (uint8_t i=0; i<10; i++)
		oled_write_data(0xFF);
		*/

	printf("%s() kraj\n", __func__);
}

/*************************************************************************************************
				oled_bg()
*************************************************************************************************/
void oled_bg(bool arg)
{
	//oled_setXY(0, 0, 127, 63);
	oled_setXY(0, 127, 0, 63);

	i2c_start(2);
	i2c_sendAddr_tx(2, OLED_ADDR_W);
	i2c_write(2, OLED_DATA);

	for (uint16_t i=0; i<128*64/8; i++)
	{
		if (arg)
		{
			i2c_write(2, 0xFF);
		}
		else
		{
			i2c_write(2, 0x00);
		}
	}
	i2c_stop(2);
}
