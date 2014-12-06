// glcd_low.c
#include "glcd_spi.c"

void glcd_sendCmd(unsigned char data)
{
	glcd_dc_low();
	glcd_cs_low();
	SPI1_send(data);
	glcd_cs_high();
}

void glcd_sendData(unsigned char data)
{
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data);
	glcd_cs_high();
}

void glcd_sendData16(unsigned int data)
{
	unsigned char data1 = data>>8;
	unsigned char data2 = data&0xff;
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data1);
	SPI1_send(data2);
	glcd_cs_high();
}

void glcd_init(void)
{
	//SPI_MasterInit();
	glcd_cs_high();
	glcd_dc_high();

	glcd_rst_on();
	delay_ms(10);
	glcd_rst_off();

	glcd_setOrientation(PORTRAIT);	// default
	delay_ms(120); 
	delay_ms(200); 

	glcd_sendCmd(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_IDLE_MODE_ON);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_MEMORY_WRITE);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_NOP);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_TEARING_EFFECT_LINE_OFF);
	delay_ms(200); 
	glcd_sendData(0x02); 	// XXX 
	delay_ms(200); 
	delay_ms(120); 

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_B);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_NOP);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_PARTIAL_AREA);
	delay_ms(200); 
	delay_ms(120); 

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	delay_ms(200); 
	glcd_sendData(0x85); 	// XXX
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_NOP);
	delay_ms(200); 
	glcd_sendData(0x78); 	// XXX
	delay_ms(200); 
	delay_ms(120); 

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_NOP);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_NOP);
	delay_ms(200); 

	glcd_sendCmd(0xED);	// XXX
	delay_ms(200); 
	glcd_sendData(0x64); 	// XXX
	delay_ms(200); 
	glcd_sendData(0x03);	// XXX
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_PARTIAL_MODE_ON);
	delay_ms(200); 
	glcd_sendData(0X81); 	// XXX
	delay_ms(200); 
	delay_ms(120); 
	delay_ms(200); 

	glcd_sendCmd(ILI9341_CMD_PUMP_RATIO_CONTROL);
	delay_ms(200); 
	glcd_sendData(ILI9341_CMD_DISP_INVERSION_OFF);
	delay_ms(200); 

	delay_ms(200); 
	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_1);
	delay_ms(200); 
	glcd_sendData(0x23);	//VRH[5:0] 	// XXX
	delay_ms(200); 

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_1);
	glcd_sendData(ILI9341_CMD_READ_MEMORY_CONTINUE);
	glcd_sendData(ILI9341_CMD_DISPLAY_OFF);

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_2);
	glcd_sendData(0x86);	//--	// XXX

	glcd_sendCmd(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(0x48);	//C8	//48 68gal.gal.gal.//28 E8 gal.gal.gal.	// XXX

	glcd_sendCmd(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	glcd_sendData(ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS);

	glcd_sendCmd(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x18); 	// XXX

	glcd_sendCmd(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
	glcd_sendData(0x08); 	// XXX
	glcd_sendData(0x82);	// XXX
	glcd_sendData(0x27);	// XXX

	glcd_sendCmd(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0x26);	//Gamma curve selected 	// XXX
	glcd_sendData(ILI9341_CMD_SOFTWARE_RESET);

	glcd_sendCmd(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
	glcd_sendData(0x0F); 	// XXX
	glcd_sendData(0x31);	// XXX
	glcd_sendData(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x08); 	// XXX
	glcd_sendData(0x4E); 	// XXX
	glcd_sendData(0xF1); 	// XXX
	glcd_sendData(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
	glcd_sendData(0x07); 	// XXX
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
	glcd_sendData(0x03);	// XXX
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(ILI9341_CMD_READ_DISP_STATUS);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x14); 	// XXX
	glcd_sendData(0x03);	// XXX
	glcd_sendData(ILI9341_CMD_SLEEP_OUT);
	glcd_sendData(0x07); 	// XXX
	glcd_sendData(0x31); 	// XXX
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(0x48); 	// XXX
	glcd_sendData(0x08); 	// XXX
	glcd_sendData(0x0F); 	// XXX
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(0x31); 	// XXX
	glcd_sendData(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC);

	glcd_sendCmd(ILI9341_CMD_SLEEP_OUT);
	delay_ms(120); 	// bilo u originalu

	glcd_sendCmd(ILI9341_CMD_DISPLAY_ON);
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	glcd_bg(bgcolor);
	delay_ms(200); 
}

void glcd_setX(unsigned int x0, unsigned int x1)
{
	glcd_sendCmd(ILI9341_CMD_COLUMN_ADDRESS_SET);
	glcd_sendData16(x0);
	glcd_sendData16(x1);
}

void glcd_setY(unsigned int y0,unsigned int y1)
{
	glcd_sendCmd(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData16(y0);
	glcd_sendData16(y1);
}

void glcd_setOrientation(char orientation)
{
	glcd_orientation = orientation;
	if((glcd_orientation == PORTRAIT) || (glcd_orientation == P1) || (glcd_orientation == P2))
	{
		max_x = 240;
		max_y = 320;
	}
	else if((glcd_orientation == LANDSCAPE) || (glcd_orientation == L1) || (glcd_orientation == L2))
	{
		max_x = 320;
		max_y = 240;
	}
}

void glcd_setXY(unsigned int x0, unsigned int x1, unsigned int y0, unsigned y1)
{
	if(glcd_orientation == P1)
	{
		glcd_setX(x0, x1);
		glcd_setY(y0, y1);
	}
	else if(glcd_orientation == P2)
	{
		glcd_setX(max_x - x1, max_x - x0);
		glcd_setY(max_y - y1, max_y - y0);
	}
	else if(glcd_orientation == L1)
	{
		glcd_setX(y1, y0);
		glcd_setY(max_x-x1, max_x-x0);
	}
	else if(glcd_orientation == L2)
	{
		glcd_setX(max_y-y0, max_y-y1);
		glcd_setY(x0,x1);
	}
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
}
