// created 141005
/*

		PA 12 11 10	1 2 3	8
		PB 5 6 7 8 9	11 12

   reset	PA12
   CS		PA1
   RS		PA2
   WR		PA3
   RD		PA8

   D7	PA11
   D6	PB5
   D5	PB6
   D4	PB7
   D3	PB8
   D2	PB9
   D1	PB11
   D0	PB12

   */

#define ST7781_RESET_RCC	RCC_APB2Periph_GPIOA
#define ST7781_RESET_PORT	GPIOA
#define ST7781_RESET_PIN	GPIO_Pin_12

#define ST7781_CS_RCC	RCC_APB2Periph_GPIOA
#define ST7781_CS_PORT	GPIOA
#define ST7781_CS_PIN	GPIO_Pin_1

#define ST7781_RS_RCC	RCC_APB2Periph_GPIOA
#define ST7781_RS_PORT	GPIOA
#define ST7781_RS_PIN	GPIO_Pin_2

#define ST7781_WR_RCC	RCC_APB2Periph_GPIOA
#define ST7781_WR_PORT	GPIOA
#define ST7781_WR_PIN	GPIO_Pin_3

#define ST7781_RD_RCC	RCC_APB2Periph_GPIOA
#define ST7781_RD_PORT	GPIOA
#define ST7781_RD_PIN	GPIO_Pin_8
//

#define ST7781_D7_RCC	RCC_APB2Periph_GPIOA
#define ST7781_D7_PORT	GPIOA
#define ST7781_D7_PIN	GPIO_Pin_11

#define ST7781_D6_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D6_PORT	GPIOB
#define ST7781_D6_PIN	GPIO_Pin_5

#define ST7781_D5_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D5_PORT	GPIOB
#define ST7781_D5_PIN	GPIO_Pin_6

#define ST7781_D4_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D4_PORT	GPIOB
#define ST7781_D4_PIN	GPIO_Pin_7

#define ST7781_D3_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D3_PORT	GPIOB
#define ST7781_D3_PIN	GPIO_Pin_8

#define ST7781_D2_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D2_PORT	GPIOB
#define ST7781_D2_PIN	GPIO_Pin_9

#define ST7781_D1_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D1_PORT	GPIOB
#define ST7781_D1_PIN	GPIO_Pin_11

#define ST7781_D0_RCC	RCC_APB2Periph_GPIOB
#define ST7781_D0_PORT	GPIOB 
#define ST7781_D0_PIN	GPIO_Pin_12


inline static void glcd_cs_low()
{
	// active low
	GPIO_WriteBit(ST7781_CS_PORT, ST7781_CS_PIN, 0);
}

inline static void glcd_cs_high()
{
	// active low
	GPIO_WriteBit(ST7781_CS_PORT, ST7781_CS_PIN, 1);
}

/*
inline static void glcd_dc_low()
{
	GPIO_WriteBit(ST7781_DC_PORT, ST7781_DC_PIN, 0);
}

inline static void glcd_dc_high()
{
	GPIO_WriteBit(ST7781_DC_PORT, ST7781_DC_PIN, 1);
}
*/

/*
void glcd_led_off()
{
	GPIO_WriteBit(ST7781_LED_PORT, ST7781_LED_PIN, 0);
}

void glcd_led_on()
{
	GPIO_WriteBit(ST7781_LED_PORT, ST7781_LED_PIN, 1);
}
*/

void glcd_rst_high()
{
	// active low
	GPIO_WriteBit(ST7781_RESET_PORT, ST7781_RESET_PIN, 1);
}
void glcd_rst_low()
{
	// active low
	GPIO_WriteBit(ST7781_RESET_PORT, ST7781_RESET_PIN, 0);
}

inline static void glcd_rs_high()
{
	GPIO_WriteBit(ST7781_RS_PORT, ST7781_RS_PIN, 1);
}

inline static void glcd_rs_low()
{
	GPIO_WriteBit(ST7781_RS_PORT, ST7781_RS_PIN, 0);
}

inline static void glcd_wr_high()
{
	GPIO_WriteBit(ST7781_WR_PORT, ST7781_WR_PIN, 1);
}

inline static void glcd_wr_low()
{
	GPIO_WriteBit(ST7781_WR_PORT, ST7781_WR_PIN, 0);
}

inline static void glcd_rd_high()
{
	GPIO_WriteBit(ST7781_RD_PORT, ST7781_RD_PIN, 1);
}

inline static void glcd_rd_low()
{
	GPIO_WriteBit(ST7781_RD_PORT, ST7781_RD_PIN, 0);
}

/*
void glcd_reg()
{
	// mora bit u funkciji inace se nece kompajlirat

	bool SM = 0, SS = 0;
	bool BC0 = 0, EOR = 0;
	bool TRI = 0, DFM = 0, BGR = 0, HWM = 0, R03_ID1 = 0, R03_ID0 = 0, AM = 0;
	bool RCV1 = 0, RCV0 = 0, RCH1 = 0, RCH0 = 0, RSZ1 = 0, RSZ0 = 0;
	bool PTDE1 = 0, PTDE0 = 0, BASEE = 0, GON = 0, DTE = 0, CL = 0, D1 = 0, D0 = 0;
	bool FP6 = 0, FP5 = 0, FP4 = 0, FP3 = 0, FP2 = 0, FP1 = 0, FP0 = 0, BP6 = 0, BP5 = 0, BP4 = 0, BP3 = 0, BP2 = 0, BP1 = 0, BP0 = 0;
	bool PTS2 = 0, PTS1 = 0, PTS0 = 0, PTG1 = 0, PTG0 = 0, ISC3 = 0, ISC2 = 0, ISC1 = 0, ISC0 = 0;
	bool FMARKOE = 0, FMI2 = 0, FMI1 = 0, FMI0 = 0;
	bool FMP8 = 0, FMP7 = 0, FMP6 = 0, FMP5 = 0, FMP4 = 0, FMP3 = 0, FMP2 = 0, FMP1 = 0, FMP0 = 0;
	bool SAP = 0, BT2 = 0, BT1 = 0, BT0 = 0, APE = 0, AP2 = 0, AP1 = 0, AP0 = 0, STB = 0;
	bool DC12 = 0, DC11 = 0, DC10 = 0, DC02 = 0, DC01 = 0, DC00 = 0, VC2 = 0, VC1 = 0, VC0 = 0;
	bool VCIRE = 0, VRH3 = 0, VRH2 = 0, VRH1 = 0, VRH0 = 0;
	bool VDV4 = 0, VDV3 = 0, VDV2 = 0, VDV1 = 0, VDV0 = 0;
	bool AD7 = 0, AD6 = 0, AD5 = 0, AD4 = 0, AD3 = 0, AD2 = 0, AD1 = 0, AD0 =0;
	bool AD16 = 0, AD15 = 0, AD14 = 0, AD13 = 0, AD12 = 0, AD11 = 0, AD10 = 0, AD9 = 0, AD8 = 0;
	bool VCM5 = 0, VCM4 = 0, VCM3 = 0, VCM2 = 0, VCM1 = 0, VCM0 = 0;
	bool FRS3 = 0, FRS2 = 0, FRS1 = 0, FRS0 = 0;
	bool KP12 = 0, KP11 = 0, KP10 = 0, KP02 = 0, KP01 = 0, KP00 = 0;
	bool HSA7 = 0, HSA6 = 0, HSA5 = 0, HSA4 = 0, HSA3 = 0, HSA2 = 0, HSA1 = 0, HSA0 = 0;
	bool HEA7 = 0, HEA6 = 0, HEA5 = 0, HEA4 = 0, HEA3 = 0, HEA2 = 0, HEA1 = 0, HEA0 = 0;
	bool VSA8 = 0, VSA7 = 0, VSA6 = 0, VSA5 = 0, VSA4 = 0, VSA3 = 0, VSA2 = 0, VSA1 = 0, VSA0 = 0;
	bool VEA8 = 0, VEA7 = 0, VEA6 = 0, VEA5 = 0, VEA4 = 0, VEA3 = 0, VEA2 = 0, VEA1 = 0, VEA0 = 0;
	bool GS = 0, NL5 = 0, NL4 = 0, NL3 = 0, NL2 = 0, NL1 = 0, NL0 = 0, SCN5 = 0, SCN4 = 0, SCN3 = 0, SCN2 = 0, SCN1 = 0, SCN0 = 0;
	bool NDL = 0, VLE = 0, REV = 0;
	bool PTDP08 = 0, PTDP07 = 0, PTDP06 = 0, PTDP05 = 0, PTDP04 = 0, PTDP03 = 0, PTDP02 = 0, PTDP01 = 0, PTDP00 = 0;
	bool PTSA08 = 0, PTSA07 = 0, PTSA06 = 0, PTSA05 = 0, PTSA04 = 0, PTSA03 = 0, PTSA02 = 0, PTSA01 = 0, PTSA00 = 0;
	bool PTEA08 = 0, PTEA07 = 0, PTEA06 = 0, PTEA05 = 0, PTEA04 = 0, PTEA03 = 0, PTEA02 = 0, PTEA01 = 0, PTEA00 = 0;
	bool PTDP18 = 0, PTDP17 = 0, PTDP16 = 0, PTDP15 = 0, PTDP14 = 0, PTDP13 = 0, PTDP12 = 0, PTDP11 = 0, PTDP10 = 0;
	bool PTSA18 = 0, PTSA17 = 0, PTSA16 = 0, PTSA15 = 0, PTSA14 = 0, PTSA13 = 0, PTSA12 = 0, PTSA11 = 0, PTSA10 = 0;
	bool PTEA18 = 0, PTEA17 = 0, PTEA16 = 0, PTEA15 = 0, PTEA14 = 0, PTEA13 = 0, PTEA12 = 0, PTEA11 = 0, PTEA10 = 0;
	bool DIVI1 = 0, DIVI0 = 0, RTNI6 = 0, RTNI5 = 0, RTNI4 = 0, RTNI3 = 0, RTNI2 = 0, RTNI1 = 0, RTNI0 = 0;
	bool NOWI2 = 0, NOWI1 = 0, NOWI0 = 0;
	bool ID6 = 0, ID5 = 0, ID4 = 0, ID3 = 0, ID2 = 0, RD2_ID1 = 0, RD2_ID0 = 0;
	bool ID_EN = 0, VCM_EN = 0;
	bool MTPROG = 0;
	bool VCMF4 = 0, VCMF3 = 0, VCMF2 = 0, VCMF1 = 0, VCMF0 = 0;
	bool FXEN = 0;

	uint16_t R00;	// ID register, treba bit 0111011110000011
	uint16_t R01 = (SM << 10) + (SS << 8);				// Driver Output Control
	uint16_t R02 = (1 << 10) + (BC0 << 9) + (EOR << 8);		// LCD Driving Wave Control
	uint16_t R03 = (TRI << 15) + (DFM << 14) + (BGR << 12) + (HWM << 9) + (R03_ID1 << 5) + (R03_ID0 << 4) + (AM << 3);	// Entry Mode
	uint16_t R04 = (RCV1 << 9) + (RCV0 << 8) + (RCH1 << 5) + (RCH0 << 4) + (RSZ1 << 1) + (RSZ0);			// Resize Control
	uint16_t R07 = (PTDE1 << 13) + (PTDE0 << 12) + (BASEE << 8) + (GON << 5) + (DTE << 4) + (CL << 3) + (D1 << 1) + D0;	// Display Control 1
	uint16_t R08 = (FP6 << 14) + (FP5 << 13) + (FP4 << 12) + (FP3 << 11) + (FP2 << 10) + (FP1 << 9) + (FP0 << 8) + \
		       (BP6 << 6) + (BP5 << 5) + (BP4 << 4) + (BP3 << 3) + (BP2 << 2) + (BP1 << 1) + BP0;			// Display Control 2
	uint16_t R09 = (PTS2 << 10) + (PTS1 << 9) + (PTS0 << 8) + (PTG1 << 5) + (PTG0 << 4) + (ISC3 << 3) + (ISC2 << 2) + (ISC1 << 1) + ISC0;	// Display Control 3
	uint16_t R0A = (FMARKOE << 3) + (FMI2 << 2) + (FMI1 << 1) + FMI0;									// Display Control 4
	uint16_t R0D = (FMP8 << 8) + (FMP7 << 7) + (FMP6 << 6) + (FMP5 << 5) + (FMP4 << 4) + (FMP3 << 3) + (FMP2 << 2) + (FMP1 << 1) + FMP0;	// Frame Marker Position
	uint16_t R10 = (SAP << 12) + (BT2 << 10) + (BT1 << 9) + (BT0 << 8) + (APE << 7) + (AP2 << 6) + (AP1 << 5) + (AP0 << 4) + (STB << 1);	// Power Control 1
	uint16_t R11 = (DC12 << 10) + (DC11 << 9) + (DC10 << 8) + (DC02 << 6) + (DC01 << 5) + (DC00 << 4) + (VC2 << 2) + (VC1 << 1) + VC0;	// Power Control 2
	uint16_t R12 = (VCIRE << 7) + (VRH3 << 3) + (VRH2 << 2) + (VRH1 << 1) + VRH0;								// Power Control 3
	uint16_t R13 = (VDV4 << 12) + (VDV3 << 11) + (VDV2 << 10) + (VDV1 << 9) + (VDV0 << 8);							// Power Control 4
	uint16_t R20 = (AD7 << 7) + (AD6 << 6) + (AD5 << 5) + (AD4 << 4) + (AD3 << 3) + (AD2 << 2) + (AD1 << 1) + AD0;				// DRAM Horizontal Address Set
	uint16_t R21 = (AD16 << 8) + (AD15 << 7) + (AD14 << 6) + (AD13 << 5) + (AD12 << 4) + (AD11 << 3) + (AD10 << 2) + (AD9 << 1) + AD8;	// DRAM Vertical Address Set
	uint16_t R22;	// Write Data to DRAM	(WD17-0)
			// Read Data from DRAM (RD17-0)
	uint16_t R29 = (VCM5 << 5) + (VCM4 << 4) + (VCM3 << 3) + (VCM2 << 2) + (VCM1 << 1) + VCM0;	// VCOMH Control
	uint16_t R2B = (FRS3 << 3) + (FRS2 << 2) + (FRS1 << 1) + FRS0;						// Frame Rate and Color Control
	uint16_t R30 = (KP12 << 10) + (KP11 << 9) + (KP10 << 8) + (KP02 << 2) + (KP01 << 1) + KP00;	// Gamma Control 1
	uint16_t R31;		// Gama Control 2
	uint16_t R32;		// Gama Control 3
	uint16_t R35;		// Gama Control 4
	uint16_t R36;		// Gama Control 5
	uint16_t R37;		// Gama Control 6
	uint16_t R38;		// Gama Control 7
	uint16_t R39;		// Gama Control 8
	uint16_t R3C;		// Gama Control 9
	uint16_t R3D;		// Gama Control 10
	uint16_t R50 = (HSA7 << 7) + (HSA6 << 6) + (HSA5 << 5) + (HSA4 << 4) + (HSA3 << 3) + (HSA2 << 2) + (HSA1 << 1) + HSA0;	// Horizontal Address Start Position
	uint16_t R51 = (HEA7 << 7) + (HEA6 << 6) + (HEA5 << 5) + (HEA4 << 4) + (HEA3 << 3) + (HEA2 << 2) + (HEA1 << 1) + HEA0;	// Horizontal Address End Position
	uint16_t R52 = (VSA8 << 8) + (VSA7 << 7) + (VSA6 << 6) + (VSA5 << 5) + (VSA4 << 4) + (VSA3 << 3) + (VSA2 << 2) + (VSA1 << 1) + VSA0;	// Vertical Address Start Position
	uint16_t R53 = (VEA8 << 8) + (VEA7 << 7) + (VEA6 << 6) + (VEA5 << 5) + (VEA4 << 4) + (VEA3 << 3) + (VEA2 << 2) + (VEA1 << 1) + VEA0;	// Vertical Address End Position
	uint16_t R60 = (GS << 15) + (NL5 << 13) + (NL4 << 12) + (NL3 << 11) + (NL2 << 10) + (NL1 << 9) + (NL0 << 8) + \
		(SCN5 << 5) + (SCN4 << 4) + (SCN3 << 3) + (SCN2 << 2) + (SCN1 << 1) + SCN0;		// Gate Scan Control 1
	uint16_t R61 = (NDL << 2) + (VLE << 1) + REV;							// Gate Scan Control 2
	uint16_t R80 = (PTDP08 << 8) + (PTDP07 << 7) + (PTDP06 << 6) + (PTDP05 << 5) + (PTDP04 << 4) + (PTDP03 << 3) + (PTDP02 << 2) + (PTDP01 << 1) + PTDP00;	// Partial Image 1 Display Position
	uint16_t R81 = (PTSA08 << 8) + (PTSA07 << 7) + (PTSA06 << 6) + (PTSA05 << 5) + (PTSA04 << 4) + (PTSA03 << 3) + (PTSA02 << 2) + (PTSA01 << 1) + PTSA00;	// Partial Image 1 Start Address
	uint16_t R82 = (PTEA08 << 8) + (PTEA07 << 7) + (PTEA06 << 6) + (PTEA05 << 5) + (PTEA04 << 4) + (PTEA03 << 3) + (PTEA02 << 2) + (PTEA01 << 1) + PTEA00;	// Partial Image 1 End Address
	uint16_t R83 = (PTDP18 << 8) + (PTDP17 << 7) + (PTDP16 << 6) + (PTDP15 << 5) + (PTDP14 << 4) + (PTDP13 << 3) + (PTDP12 << 2) + (PTDP11 << 1) + PTDP10;	// Partial Image 2 Display Position
	uint16_t R84 = (PTSA18 << 8) + (PTSA07 << 7) + (PTSA06 << 6) + (PTSA05 << 5) + (PTSA04 << 4) + (PTSA03 << 3) + (PTSA02 << 2) + (PTSA01 << 1) + PTSA00;	// Partial Image 2 Start Address
	uint16_t R85 = (PTEA18 << 8) + (PTEA17 << 7) + (PTEA16 << 6) + (PTEA15 << 5) + (PTEA14 << 4) + (PTEA13 << 3) + (PTEA12 << 2) + (PTEA11 << 1) + PTEA10;	// Partial Image 2 End Address
	uint16_t R90 = (DIVI1 << 9) + (DIVI0 << 8) + (RTNI6 << 6) + (RTNI5 << 5) + (RTNI4 << 4) + (RTNI3 << 3) + (RTNI2 << 2) + (RTNI1 << 1) + RTNI0;		// Panel Interface Control 1
	uint16_t R92 = (NOWI2 << 10) + (NOWI1 << 9) + (NOWI0 << 8);												// Panel Intreface Control 2
	uint16_t RD2 = (ID6 << 6) + (ID5 << 5) + (ID4 << 4) + (ID3 << 3) + (ID2 << 2) + (RD2_ID1 << 1) + RD2_ID0;	// EEPROM ID Code
	uint16_t RD9 = (ID_EN << 6) + (VCM_EN << 5);	// EEPROM Control Status
	//uint16_t RDF = XXX			// EEPROM Write Command
	uint16_t RFA = (MTPROG << 1);		// EEPROM Enable
	uint16_t RFE = (VCMF4 << 4) + (VCMF3 << 3) + (VCMF2 << 2) + (VCMF1 << 1) + VCMF0;	// EEPROM VCOM Offset
	uint16_t RFF = FXEN;	// FA/FE Enable

}
*/
