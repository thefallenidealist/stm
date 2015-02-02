/*
   srednji layer, mijenja se u ovisnosti o LCDu, vjerojatno i protokolu

   sadrzi init
   	sendCmd
	sendData

   moguce da send* pizdarije pripadaju low level dijelu

   */

#include "glcd_mid.h"

//void glcd_sendCmd(unsigned char data)
void glcd_sendCmd(uint8_t data)
{
	glcd_dc_low();
	glcd_cs_low();
	glcd_spi_send(data);
	glcd_cs_high();
}

//void glcd_sendData(unsigned char data)
void glcd_sendData(uint8_t data)
{
	glcd_dc_high();
	glcd_cs_low();
	glcd_spi_send(data);
	glcd_cs_high();
}

void glcd_sendData16(uint16_t data)
{
	unsigned char dataH = data >> 8;
	unsigned char dataL = data & 0xFF;
	glcd_dc_high();
	glcd_cs_low();
	glcd_spi_send(dataH);
	glcd_spi_send(dataL);
	glcd_cs_high();
}

void glcd_ili9341_init(void)
{
	glcd_cs_high();
	glcd_dc_high();

	glcd_rst_on();
	delay_ms(10);
	glcd_rst_off();

	// "neka se nadje": u boljim danima radi bez toga, kad zvijezde nisu dobro nastimane
	// onda radi samo nakon prvog reflasha

	//glcd_setOrientation(P1);	// default

	glcd_sendCmd(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	glcd_sendData(ILI9341_CMD_IDLE_MODE_ON);
	glcd_sendData(ILI9341_CMD_MEMORY_WRITE);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_TEARING_EFFECT_LINE_OFF);
	glcd_sendData(0x02); 

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_B);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_PARTIAL_AREA);

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	glcd_sendData(0x85);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x78);

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0xED);
	glcd_sendData(0x64);
	glcd_sendData(0x03);
	glcd_sendData(ILI9341_CMD_PARTIAL_MODE_ON);
	glcd_sendData(0X81);

	glcd_sendCmd(ILI9341_CMD_PUMP_RATIO_CONTROL);
	glcd_sendData(ILI9341_CMD_DISP_INVERSION_OFF);

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_1);
	glcd_sendData(0x23);	//VRH[5:0]

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
	delay_ms(DELAY120);						// neka se nadje

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_1);
	glcd_sendData(ILI9341_CMD_READ_MEMORY_CONTINUE);
	glcd_sendData(ILI9341_CMD_DISPLAY_OFF);
	delay_ms(DELAY120);		// treba inace inicijalizira 2/3 ekrana

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_2);
	glcd_sendData(0x86);

	glcd_sendCmd(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(0x48);	//C8	//48 68gal.gal.gal.//28 E8 gal.gal.gal.	

	glcd_sendCmd(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	glcd_sendData(ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS);

	glcd_sendCmd(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x18); 

	glcd_sendCmd(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
	glcd_sendData(0x08); 
	glcd_sendData(0x82);
	glcd_sendData(0x27);

	glcd_sendCmd(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0x26);	//Gamma curve selected 	
	glcd_sendData(ILI9341_CMD_SOFTWARE_RESET);

	glcd_sendCmd(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
	glcd_sendData(0x0F);
	glcd_sendData(0x31);
	glcd_sendData(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x08);
	glcd_sendData(0x4E);
	glcd_sendData(0xF1);
	glcd_sendData(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
	glcd_sendData(0x07);
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
	delay_ms(DELAY120);						// neka se nadje
	glcd_sendData(0x03);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(ILI9341_CMD_READ_DISP_STATUS);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x14);
	glcd_sendData(0x03);
	glcd_sendData(ILI9341_CMD_SLEEP_OUT);
	delay_ms(DELAY120);						// neka se nadje
	glcd_sendData(0x07);
	glcd_sendData(0x31);
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(0x48);
	glcd_sendData(0x08);
	glcd_sendData(0x0F);
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(0x31);
	glcd_sendData(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC);

	glcd_sendCmd(ILI9341_CMD_SLEEP_OUT);
	delay_ms(DELAY120); 	// nakon sleep outa treba 120 ms

	glcd_sendCmd(ILI9341_CMD_DISPLAY_ON);
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	//glcd_bg(bgcolor);
}
