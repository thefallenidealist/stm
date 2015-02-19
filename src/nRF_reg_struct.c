#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// includea se samo .h i ovo sve dolje su privatni struct-ovi
 
/**********************************************************************/
//			 CMD	page 46
/**********************************************************************/
typedef enum
{
	CMD_R_REGISTER	= 0,
	/*
	Read command and status registers. AAAAA =
	5 bit Register Map Address
	*/

	CMD_W_REGISTER = 32,
	/*
	Write command and status registers. AAAAA = 5 
	bit Register Map Address
	Executable in power down or standby modes 
	only.
	*/

	CMD_R_RX_PAYLOAD = 0b01100001,	
	/*
	Read RX-payload: 1 – 32 bytes. A read operation
	always starts at byte 0. Payload is deleted from 
	FIFO after it is read. Used in RX mode. 
	*/
	CMD_W_TX_PAYLOAD = 0b10100000,
	/*
	Write TX-payload: 1 – 32 bytes. A write operation 
	always starts at byte 0 used in TX payload.
	*/
	CMD_FLUSH_TX	= 0b11100001,
	// Flush TX FIFO, used in TX mode 

	CMD_FLUSH_RX = 0b11100010,
	/*
	Flush RX FIFO, used in RX mode
	Should not be executed during transmission of 
	acknowledge, that is, acknowledge package will 
	not be completed.
	*/

	CMD_REUSE_TX_PL	= 0b11100011,
	/*
	Used for a PTX device
	Reuse last transmitted payload. Packets are 
	repeatedly retransmitted as long as CE is high.
	TX payload reuse is active until 
	W_TX_PAYLOAD or FLUSH TX is executed. TX 
	payload reuse must not be activated or deacti-
	vated during package transmission
	*/

	CMD_ACTIVATE = 0b01010000,
	/*
	This write command followed by data 0x73 acti-
	vates the following features:
	•R_RX_PL_WID
	•W_ACK_PAYLOAD
	•W_TX_PAYLOAD_NOACK
	A new ACTIVATE command with the same data 
	deactivates them again. This is executable in 
	power down or stand by modes only.
	The R_RX_PL_WID, W_ACK_PAYLOAD, and 
	W_TX_PAYLOAD_NOACK features registers are 
	initially in a deactivated state; a write has no 
	effect, a read only results in zeros on MISO. To 
	activate these registers, use the ACTIVATE com
	mand followed by data 0x73. Then they can be 
	accessed as any other register in nRF24L01. Use
	the same command and data to deactivate the 
	registers again.
	*/

	CMD_R_RX_PL_WID	= 0b01100000,
	/*
	Read RX-payload width for the top 
	R_RX_PAYLOAD in the RX FIFO.
	*/

	CMD_W_ACK_PAYLOAD = 0b10101000,
	// 1010 1PPP
	/*
	Used in RX mode.
	Write Payload to be transmitted together with 
	ACK packet on PIPE PPP. (PPP valid in the 
	range from 000 to 101). Maximum three ACK 
	packet payloads can be pending. Payloads with 
	same PPP are handled using first in - first out 
	principle. Write payload: 1– 32 bytes. A write 
	operation always starts at byte 0.
	*/
	CMD_W_TX_PAYLOAD_NO_ACK = 0b1011000,
	//	Used in TX mode. Disables AUTOACK on this specific packet.

	CMD_NOP = 0b11111111
	//	No Operation. Might be used to read the STATUS register
} commands;


/****************************************************************************/
// 			registers
//			page 54
/****************************************************************************/
// defaultne vrijednosti su 0, osim ako nije spomenito drugacije
// defaultne vrijednosti RW, osim ako nije napisano drugacije

struct REG_CONFIG
{
	uint8_t addr;
	uint8_t MASK_RX_DR;	// Mask interrupt caused by RX_DR
				// 1: Interrupt not reflected on the IRQ pin
				// 0: Reflect RX_DR as active low interrupt on the 
				// IRQ pin
	uint8_t MASK_TX_DS;	//  Mask interrupt caused by TX_DS
				// 1: Interrupt not reflected on the IRQ pin
				// 0: Reflect TX_DS as active low interrupt on the 
				// IRQ pin
	uint8_t MASK_MAX_RT;	// Mask interrupt caused by MAX_RT
				// 1: Interrupt not reflected on the IRQ pin
				// 0: Reflect MAX_RT as active low interrupt on the 
				// IRQ pin
	uint8_t EN_CRC;		// Enable CRC. Forced high if one of the bits in 
				// the EN_AA is high		default: 1
	uint8_t CRCO;		// CRC encoding scheme
				// '0' - 1 byte
				// '1' – 2 bytes 
	uint8_t PWR_UP;		// 1: POWER UP, 0:POWER DOWN
	uint8_t PRIM_RX;	// RX/TX control 
				// 1: PRX, 0: PTX 
};
struct REG_CONFIG CONFIG = {0x00, 6,5,4,3,2,1,0};

// Enable ‘Auto Acknowledgment’ Function Dis-
// able this functionality to be compatible with nRF2401
struct REG_EN_AA
{
	uint8_t addr;
	uint8_t ENAA_P5;	// Enable auto ack data pipe 5	default: 1
	uint8_t ENAA_P4;	// Enable auto ack data pipe 4	default: 1
	uint8_t ENAA_P3;	// Enable auto ack data pipe 3	default: 1
	uint8_t ENAA_P2;	// Enable auto ack data pipe 2	default: 1
	uint8_t ENAA_P1;	// Enable auto ack data pipe 1	default: 1
	uint8_t ENAA_P0;	// Enable auto ack data pipe 0	default: 1
};
struct REG_EN_AA EN_AA = {0x01, 5,4,3,2,1,0};

// Enabled RX Addresses
struct REG_EN_RXADDR
{
	uint8_t addr;
	uint8_t ERX_P5;		// Enable data pipe 5
	uint8_t ERX_P4;		// Enable data pipe 4
	uint8_t ERX_P3;		// Enable data pipe 3
	uint8_t ERX_P2;		// Enable data pipe 2
	uint8_t ERX_P1;		// Enable data pipe 1	default: 1
	uint8_t ERX_P0;		// Enable data pipe 0	default: 1
};
struct REG_EN_RXADDR EN_RXADDR = {0x02, 5,4,3,2,1,0};

// Setup of Address Widths (common for all data pipes)
// vise bajtova adrese - sporiji prijenos
struct REG_SETUP_AW
{
	uint8_t addr;
	uint8_t AW1;		// 00 - illegal		01 - 3 bytes	
	uint8_t AW0;		// 10 - 4 bytes		11 - 5 bytes
	//uint8_t AW[2];
};
struct REG_SETUP_AW SETUP_AW = {0x03, 1,0};

// Setup of Automatic Retransmission
struct REG_SETUP_RETR	
{
	uint8_t addr;
	uint8_t ARD3;		// Auto Retransmit Delay
	uint8_t ARD2;		// 0000 – Wait 250µs
	uint8_t ARD1;		// 0001 - 500 us
	uint8_t ARD0;		// 0010 - 750 us		// 1111 4000 us
	uint8_t ARC3;		// Auto Retransmit Count
	uint8_t ARC2;		// 0000 retransmit disabled
	uint8_t ARC1;		// 0001	up to 1 retransmit
	uint8_t ARC0;		// 1111 up to 15 retransmit
};
struct REG_SETUP_RETR SETUP_RETR = {0x04, 7,6,5,4,3,2,1,0};

// RF Channel
struct REG_RF_CH
{
	uint8_t addr;
	uint8_t RF_CH6;		// Sets the frequency channel nRF24L01 operates on
	uint8_t RF_CH5;		// default [6..0]: 0000010
	uint8_t RF_CH4;
	uint8_t RF_CH3;
	uint8_t RF_CH2;
	uint8_t RF_CH1;
	uint8_t RF_CH0;
};
struct REG_RF_CH RF_CH = {0x05, 6,5,4,3,2,1,0};

// RF Setup Register
struct REG_RF_SETUP
{
	uint8_t addr;
	uint8_t	PLL_LOCK;	// Force PLL lock signal. Only used in test
	uint8_t	RF_DR;		// Air Data Rate
				// ‘0’ – 1Mbps
				// ‘1’ – 2Mbps		default
	uint8_t RF_PWR1;
	uint8_t RF_PWR0;	// Set RF output power in TX mode
				// '00' –  -18dBm
				// '01' –  -12dBm
				// '10' –   -6dBm
				// '11' –     0dBm	default
	uint8_t	LNA_HCURR;	// Setup LNA gain	default: 1
};
struct REG_RF_SETUP RF_SETUP = {0x06, 4,3,2,1,0};

struct REG_STATUS
{
	uint8_t addr;
	uint8_t	RX_DR;		// Data Ready RX FIFO interrupt. Asserted when 
				// new data arrives RX FIFOb.
				// Write 1 to clear bit.
	uint8_t	TX_DS;		// Data Sent TX FIFO interrupt. Asserted when 
				// packet transmitted on TX. If AUTO_ACK is acti-
				// vated, this bit is set high only when ACK is 
				// received.
				// Write 1 to clear bit.
	uint8_t	MAX_RT;		// Maximum number of TX retransmits interrupt
				// Write 1 to clear bit. If MAX_RT is asserted it must 
				// be cleared to enable further communication.
				// default: 0
	uint8_t	RX_P_NO2;	// Data pipe number for the payload available 			RO
				// reading from RX_FIFO
				// 000-101: Data Pipe Number 
	uint8_t RX_P_NO1;	// 110: Not Used						RO
	uint8_t RX_P_NO0;	// 111: RX FIFO Empty			default: 111		RO
	uint8_t	TX_FULL;	// 1: TX FIFO full.
};
struct REG_STATUS STATUS = {0x07, 6,5,4,3,2,1,0};

// Transmit observe register
struct REG_OBSERVE_TX
{
	uint8_t addr;
	uint8_t	PLOS_CNT3;	// Count lost packets. The counter is overflow pro-		RO
	uint8_t	PLOS_CNT2;	// tected to 15, and discontinues at max until 			RO
	uint8_t	PLOS_CNT1;	// reset. The counter is reset by writing to RF_CH. 		RO
	uint8_t	PLOS_CNT0;	// See page 65 and page 74[]					RO
	uint8_t ARC_CNT3;	//								RO
	uint8_t ARC_CNT2;	// Count retransmitted packets. 				RO
	uint8_t ARC_CNT1;	// Count retransmitted packets. The counter is 			RO
	uint8_t ARC_CNT0;	// reset when transmission of a new packet starts. 		RO
};
struct REG_OBSERVE_TX OBSERVE_TX = {0x08, 7,6,5,4,3,2,1,0};

// carrier detect
struct REG_CD
{
	uint8_t addr;
	uint8_t CD;	// default 0
};
struct REG_CD CD = {0x09, 0};

#define REG_RX_ADDR_P0	0x0A	// Receive address data pipe 0. 5 Bytes maximum 
				// length. (LSByte is written first. Write the number 
				// of bytes defined by SETUP_AW)
				//[39..0] 	default: 0xE7E7E7E7E7

#define REG_RX_ADDR_P1	0x0B	// Receive address data pipe 1. 5 Bytes maximum
				// length. (LSByte is written first. Write the number
				// of bytes defined by SETUP_AW)
				// [39..0] 	default: 0xC2C2C2C2C2
#define REG_RX_ADDR_P2	0x0C	// Receive address data pipe 2. Only LSB. MSBy-
				// tes is equal to RX_ADDR_P1[39:8]
				// [7..0] 	default: 0xC3
#define REG_RX_ADDR_P3	0x0D	// Receive address data pipe 3. Only LSB. MSBy-
				// tes is equal to RX_ADDR_P1[39:8]
				// [7..0] 	default: 0xC4
#define REG_RX_ADDR_P4	0x0E	// Receive address data pipe 4. Only LSB. MSBy-
				// tes is equal to RX_ADDR_P1[39:8]
				// [7..0] 	default: 0xC5
#define REG_RX_ADDR_P5	0x0F	// Receive address data pipe 5. Only LSB. MSBy-
				// tes is equal to RX_ADDR_P1[39:8]
				// [7..0] 	default: 0xC6
#define REG_TX_ADDR	0x10	// Transmit address. Used for a PTX device only. 
				// (LSByte is written first)
				// Set RX_ADDR_P0 equal to this address to han
				// dle automatic acknowledge if this is a PTX 
				// device with Enhanced ShockBurst™ enabled. 
				// [39..0] 	default: 0xE7E7E7E7E7

// Number of bytes in RX payload in data pipe 0
struct REG_RX_PW_P0
{
	uint8_t addr;
	uint8_t RX_PW_P0_5;	// 1 to 32 bytes
	uint8_t RX_PW_P0_4;	// 1 - 1 byte
	uint8_t RX_PW_P0_3;	// 32 - 32 bytes
	uint8_t RX_PW_P0_2;
	uint8_t RX_PW_P0_1;
	uint8_t RX_PW_P0_0;
};
struct REG_RX_PW_P0 RX_PW_P0 = {0x11, 5,4,3,2,1,0};

// Number of bytes in RX payload in data pipe 1
struct REG_RX_PW_P1
{
	uint8_t addr;
	uint8_t RX_PW_P1_5;	// 1 to 32 bytes
	uint8_t RX_PW_P1_4;	// 1 - 1 byte
	uint8_t RX_PW_P1_3;	// 32 - 32 bytes
	uint8_t RX_PW_P1_2;
	uint8_t RX_PW_P1_1;
	uint8_t RX_PW_P1_0;
};
struct REG_RX_PW_P1 RX_PW_P1 = {0x12, 5,4,3,2,1,0};

// Number of bytes in RX payload in data pipe 2
struct REG_RX_PW_P2
{
	uint8_t addr;
	uint8_t RX_PW_P2_5;	// 1 to 32 bytes
	uint8_t RX_PW_P2_4;	// 1 - 1 byte
	uint8_t RX_PW_P2_3;	// 32 - 32 bytes
	uint8_t RX_PW_P2_2;
	uint8_t RX_PW_P2_1;
	uint8_t RX_PW_P2_0;
};
struct REG_RX_PW_P2 RX_PW_P2 = {0x13, 5,4,3,2,1,0};

// Number of bytes in RX payload in data pipe 3
struct REG_RX_PW_P3
{
	uint8_t addr;
	uint8_t RX_PW_P3_5;	// 1 to 32 bytes
	uint8_t RX_PW_P3_4;	// 1 - 1 byte
	uint8_t RX_PW_P3_3;	// 32 - 32 bytes
	uint8_t RX_PW_P3_2;
	uint8_t RX_PW_P3_1;
	uint8_t RX_PW_P3_0;
};
struct REG_RX_PW_P3 RX_PW_P3 = {0x14, 5,4,3,2,1,0};

// Number of bytes in RX payload in data pipe 4
struct REG_RX_PW_P4
{
	uint8_t addr;
	uint8_t RX_PW_P4_5;	// 1 to 32 bytes
	uint8_t RX_PW_P4_4;	// 1 - 1 byte
	uint8_t RX_PW_P4_3;	// 32 - 32 bytes
	uint8_t RX_PW_P4_2;
	uint8_t RX_PW_P4_1;
	uint8_t RX_PW_P4_0;
};
struct REG_RX_PW_P4 RX_PW_P4 = {0x15, 5,4,3,2,1,0};

// Number of bytes in RX payload in data pipe 5
struct REG_RX_PW_P5
{
	uint8_t addr;
	uint8_t RX_PW_P5_5;	// 1 to 32 bytes
	uint8_t RX_PW_P5_4;	// 1 - 1 byte
	uint8_t RX_PW_P5_3;	// 32 - 32 bytes
	uint8_t RX_PW_P5_2;
	uint8_t RX_PW_P5_1;
	uint8_t RX_PW_P5_0;
};
struct REG_RX_PW_P5 RX_PW_P5 = {0x16, 5,4,3,2,1,0};


// FIFO Status Register
struct REG_FIFO_STATUS
{
	uint8_t addr;
	uint8_t TX_REUSE;	// Reuse last transmitted data packet if set high. 	RO
				// The packet is repeatedly retransmitted as long 
				// as CE is high. TX_REUSE is set by the SPI com
				// mand REUSE_TX_PL, and is reset by the SPI 
				// commands W_TX_PAYLOAD or FLUSH TX
	// zove se TX_FULL2 jer gore vec ima TX_FULL
	//uint8_t TX_FULL2;	// TX FIFO full flag. 1: TX FIFO full. 0: Available 	RO
	uint8_t TX_FULL;	// TX FIFO full flag. 1: TX FIFO full. 0: Available 	RO
				// locations in TX FIFO.
	uint8_t TX_EMPTY;	// TX FIFO empty flag. 					RO
				// 1: TX FIFO empty. 
				// 0: Data in TX FIFO.
	uint8_t RX_FULL	;	// RO
	uint8_t RX_EMPTY;	// RO
};
struct REG_FIFO_STATUS FIFO_STATUS = {0x17, 6,5,4,1,0};

/*
   nisu registri
   ACK_PLD		[255..0] 	WO
   	Written by separate SPI command
	ACK packet payload to data pipe number PPP 
	given in SPI command
	Used in RX mode only
	Maximum three ACK packet payloads can be 
	pending. Payloads with same PPP are handled
	first in first out.

   TX_PLD		[255..0] 	WO
	Written by separate SPI command TX data pay-
	load register 1 - 32 bytes.
	This register is implemented as a FIFO with 
	three levels. 
	Used in TX  mode only

   RX_PLD		[255..0] 	RO
	Read by separate SPI command
	RX data payload register. 1 - 32 bytes.
	This register is implemented as a FIFO with 
	three levels.
	All RX channels share the same FIFO
*/

// Enable dynamic payload length
struct REG_DYNPD
{
	uint8_t addr;
	uint8_t DPL_P5;		// Enable dyn. payload length  data pipe 5. 
				// (Requires EN_DPL and ENAA_P5)
	uint8_t DPL_P4;		// Enable dyn. payload length  data pipe 4. 
				// (Requires EN_DPL and ENAA_P5)
	uint8_t DPL_P3;		// Enable dyn. payload length  data pipe 3. 
				// (Requires EN_DPL and ENAA_P5)
	uint8_t DPL_P2;		// Enable dyn. payload length  data pipe 2. 
				// (Requires EN_DPL and ENAA_P5)
	uint8_t DPL_P1;		// Enable dyn. payload length  data pipe 1. 
				// (Requires EN_DPL and ENAA_P5)
	uint8_t DPL_P0;		// Enable dyn. payload length  data pipe 0. 
				// (Requires EN_DPL and ENAA_P5)
};
struct REG_DYNPD DYNPD = {0x1C, 5,4,3,2,1,0};

// Feature Register
struct REG_FEATURE
{
	uint8_t addr;
	uint8_t EN_DPL;		// Enables Dynamic Payload Length
	uint8_t EN_ACK_PAY;	// Enables Payload with ACK
	uint8_t EN_DYN_ACK;	// Enables the W_TX_PAYLOAD_NOACK command
};
struct REG_FEATURE FEATURE = {0x1D, 2,1,0};



int main2()
//int main()
{
	printf("ovdje reg.c\n");
	// staro
	//write_reg(REG_SETUP_RETR, (1 << ARD3));
	/*
		write reg: reg: 0x4, value: 128
		SPI sending: 4 + 32
		SPI sending: 128
	*/

	// novo
	//write_reg(SETUP_RETR.addr, (1 << SETUP_RETR.ARD3));
	/*
		write reg: reg: 0x4, value: 128
		SPI sending: 4 + 32
		SPI sending: 128
	*/

	/*
	printf("CRCO: %d\n", 1 << CONFIG.CRCO);
	printf("PWR_UP: %d\n", 1 << CONFIG.PWR_UP);
	printf("PRIM_RX: %d\n", 1 << CONFIG.PRIM_RX);

	printf("CONFIG: 0x%X\n", CONFIG.addr);
	printf("CONFIG: PWR_UP | CRC0 =  %d\n", (1 << CONFIG.PWR_UP) | (1 << CONFIG.CRCO)); // uint8_t
	printf("CONFIG: PWR_UP + CRC0 =  %d\n", (1 << CONFIG.PWR_UP) + (1 << CONFIG.CRCO)); // uint8_t
	*/

	/*
	printf("SETUP_AW:\n");
	printf("\taddr: 0x%X\n", SETUP_AW.addr);
	printf("\tAW1: %d\n", SETUP_AW.AW[1]);
	printf("\tAW0: %d\n", SETUP_AW.AW[0]);
	*/

	return 0;
}
