// created 141005

/*
   RS = 1	data
   RS = 0	cmd

   nWR		write enable


   nCS		chip select
   nRESET
   nWR		write enable
   nRD		read enable

   8b:
   RS=0		nRD=1		nWR=rising	write cmd
   RS=1		nRD=1		nWR=rising	write data
   RS=1		nRD=rising	nWR=1		read data
   RS=1		nRD=rising	nWR=1		read parameter/status

*/

#include <stdbool.h>

//void glcd_st7781_send8b(uint8_t data);
void glcd_send8b(uint8_t data);
//void glcd_sendCmd(uint16_t cmd);
void glcd_sendCmd(uint16_t cmd);
void glcd_writeReg(uint16_t reg, uint16_t data);
void glcd_bg(uint16_t color);

void glcd_st7781_io_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Pin = ST7781_RESET_PIN;
	GPIO_Init(ST7781_RESET_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_CS_PIN;
	GPIO_Init(ST7781_CS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_RS_PIN;
	GPIO_Init(ST7781_RS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_WR_PIN;
	GPIO_Init(ST7781_WR_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_RD_PIN;
	GPIO_Init(ST7781_RD_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D0_PIN;
	GPIO_Init(ST7781_D0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D1_PIN;
	GPIO_Init(ST7781_D1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D2_PIN;
	GPIO_Init(ST7781_D2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D3_PIN;
	GPIO_Init(ST7781_D3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D4_PIN;
	GPIO_Init(ST7781_D4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D5_PIN;
	GPIO_Init(ST7781_D5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D6_PIN;
	GPIO_Init(ST7781_D6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ST7781_D7_PIN;
	GPIO_Init(ST7781_D7_PORT, &GPIO_InitStructure);
}

//void glcd_sendCmd(uint16_t cmd)
void glcd_sendCmd(uint16_t cmd)
{
	glcd_wr_high();
	glcd_cs_low();
	glcd_rs_low();
	glcd_rd_high();

	//glcd_st7781_send8b(cmd >> 8);	// visih 8b
	glcd_send8b(cmd >> 8);	// visih 8b

	glcd_wr_low();
	glcd_wr_high();
	
	//glcd_st7781_send8b(cmd & 0xFF);	// nizih 8b
	glcd_send8b(cmd & 0xFF);	// nizih 8b

	glcd_wr_low();
	glcd_wr_high();

	glcd_cs_high();
}

//void glcd_st7781_sendData(uint16_t data)
void glcd_sendData16(uint16_t data)
{
	glcd_wr_high();	// nepotrebno? TODO
	glcd_cs_low();
	glcd_rs_high();	// stize data
	glcd_rd_high();

	//glcd_st7781_send8b(data >> 8);
	glcd_send8b(data >> 8);
	glcd_wr_low();
	glcd_wr_high();

	//glcd_st7781_send8b(data & 0xFF);
	glcd_send8b(data & 0xFF);
	glcd_wr_low();
	glcd_wr_high();

	glcd_cs_high();
}

//void glcd_st7781_send8b(uint8_t data)
void glcd_send8b(uint8_t data)
{
	GPIO_WriteBit(ST7781_D7_PORT, ST7781_D7_PIN, (data >> 7 & 1));	
	GPIO_WriteBit(ST7781_D6_PORT, ST7781_D6_PIN, (data >> 6 & 1));
	GPIO_WriteBit(ST7781_D5_PORT, ST7781_D5_PIN, (data >> 5 & 1));
	GPIO_WriteBit(ST7781_D4_PORT, ST7781_D4_PIN, (data >> 4 & 1));
	GPIO_WriteBit(ST7781_D3_PORT, ST7781_D3_PIN, (data >> 3 & 1));
	GPIO_WriteBit(ST7781_D2_PORT, ST7781_D2_PIN, (data >> 2 & 1));
	GPIO_WriteBit(ST7781_D1_PORT, ST7781_D1_PIN, (data >> 1 & 1));
	GPIO_WriteBit(ST7781_D0_PORT, ST7781_D0_PIN, (data >> 0 & 1));
}

//void glcd_writeReg(uint16_t reg, uint16_t data)
void glcd_writeReg(uint16_t reg, uint16_t data)
{
	//glcd_sendCmd(reg);

	glcd_wr_high();
	glcd_cs_low();
	glcd_rs_low();
	glcd_rd_high();

	//glcd_st7781_send8b(reg >> 8);	// visih 8b
	glcd_send8b(reg >> 8);	// visih 8b
	glcd_wr_low();
	glcd_wr_high();
	
	//glcd_st7781_send8b(reg & 0xFF);	// nizih 8b
	glcd_send8b(reg & 0xFF);	// nizih 8b
	glcd_wr_low();
	glcd_wr_high();

	glcd_cs_high();





	//glcd_sendData(data);
	glcd_wr_high();
	glcd_cs_low();
	glcd_rs_high();	// stize data
	glcd_rd_high();

	//glcd_st7781_send8b(data >> 8);	// visih 8b
	glcd_send8b(data >> 8);	// visih 8b
	glcd_wr_low();
	glcd_wr_high();

	//glcd_st7781_send8b(data & 0xFF);	// nizih 8b
	glcd_send8b(data & 0xFF);	// nizih 8b
	glcd_wr_low();
	glcd_wr_high();

	glcd_cs_high();
}

void glcd_st7781_init()
{

	glcd_st7781_io_init();

	glcd_rst_low();
	delay_ms(100);
	glcd_rst_high();

	glcd_writeReg(0x0001,0x0100);
	glcd_writeReg(0x0002,0x0700);
	glcd_writeReg(0x0003,0x1030);   // Portrait, Landscape
	glcd_writeReg(0x0008,0x0302);
	glcd_writeReg(0x0009,0x0000);
	glcd_writeReg(0x0010,0x0000);
	glcd_writeReg(0x0011,0x0007);
	glcd_writeReg(0x0012,0x0000);
	glcd_writeReg(0x0013,0x0000);
	//delay_ms(1000);
	//delay_ms(1000);
	glcd_writeReg(0x0010,0x14B0);
	//delay_ms(1000);
	glcd_writeReg(0x0011,0x0007);
	//delay_ms(500);
	glcd_writeReg(0x0012,0x008E);
	glcd_writeReg(0x0013,0x0C00);
	glcd_writeReg(0x0029,0x0015);
	//delay_ms(500);
	glcd_writeReg(0x0030,0x0000);
	glcd_writeReg(0x0031,0x0107);
	glcd_writeReg(0x0032,0x0000);
	glcd_writeReg(0x0035,0x0203);
	glcd_writeReg(0x0036,0x0402);
	glcd_writeReg(0x0037,0x0000);
	glcd_writeReg(0x0038,0x0207);
	glcd_writeReg(0x0039,0x0000);
	glcd_writeReg(0x003C,0x0203);
	glcd_writeReg(0x003D,0x0403);
	glcd_writeReg(0x0050,0x0000); // Horizontal Start
	glcd_writeReg(0x0051,0x00EF); // Horizontal Ende			239
	glcd_writeReg(0x0052,0x0000); // Vertikal Start
	glcd_writeReg(0x0053,0x013F); // Vertikal Ende				319
	glcd_writeReg(0x0060,0xA700);	
	glcd_writeReg(0x0061,0x0001);
	glcd_writeReg(0x0090,0x0029);
	glcd_writeReg(0x0007,0x0133); // display on
	//delay_ms(500);
	//glcd_writeReg( 0xF1,0x0022		// cmd
	glcd_sendCmd(0x0022);
}

//void glcd_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);

//void glcd_st7781_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
void glcd_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
	glcd_writeReg(0x0050, x0);
	glcd_writeReg(0x0051, x1);
	glcd_writeReg(0x0052, y0);
	glcd_writeReg(0x0053, y1);
	glcd_sendCmd(0x0022);	// write to GRAM
}

//void glcd_st7781_bg(uint16_t color)
void glcd_bg(uint16_t color)
{
	// fast line
	// case 0
	//glcd_writeReg(0x03, 0x1030);
	//glcd_writeReg(0x03, 0b0000000000011000);


	//for(int x=0; x<240; x++)

	/*
	// pixel
	glcd_writeReg(0x20, 0);		// x
	glcd_writeReg(0x21, 0);	// y
	glcd_sendCmd(0x22);	// write to GRAM
	*/

	//glcd_st7781_setXY(0,239, 0,319);
	glcd_setXY(0,239, 0,319);

	/*
	glcd_cs_low();
	glcd_rs_high();
	glcd_rd_high();
	glcd_wr_high();
	*/

	for(int i=0; i<240*321; i++)	// madjija, treba za jednu vise
	{
		//glcd_st7781_sendData(color);
		glcd_sendData16(color);
	}

}
