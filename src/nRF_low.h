// created 121228
// TODO prebacit poneki #define u enum, radi ljepseg debuggiranja
// TODO svi ovi silni registri bi trebali bit privatni

#include <stdio.h>
#include <stdbool.h>
#include "spi.h"
#include "delay.h"
#include "nRF_struct.h"

/**********************************************************************/
//			 CMD	page 46
/**********************************************************************/
#define CMD_R_REGISTER		0
/*
	Read command and status registers. AAAAA =
	5 bit Register Map Address
*/

//#define CMD_W_REGISTER		0b00100000	// 32 = 001A AAAA
#define CMD_W_REGISTER		32
/*
	Write command and status registers. AAAAA = 5 
	bit Register Map Address
	Executable in power down or standby modes 
	only.
*/

#define CMD_R_RX_PAYLOAD	0b01100001
/*
	Read RX-payload: 1 – 32 bytes. A read operation
	always starts at byte 0. Payload is deleted from 
	FIFO after it is read. Used in RX mode. 
*/

#define CMD_W_TX_PAYLOAD	0b10100000
/*
	Write TX-payload: 1 – 32 bytes. A write operation 
	always starts at byte 0 used in TX payload.
*/

#define	CMD_FLUSH_TX		0b11100001
// Flush TX FIFO, used in TX mode 

#define CMD_FLUSH_RX		0b11100010
/*
	Flush RX FIFO, used in RX mode
	Should not be executed during transmission of 
	acknowledge, that is, acknowledge package will 
	not be completed.
*/

#define CMD_REUSE_TX_PL		0b11100011
/*
	Used for a PTX device
	Reuse last transmitted payload. Packets are 
	repeatedly retransmitted as long as CE is high.
	TX payload reuse is active until 
	W_TX_PAYLOAD or FLUSH TX is executed. TX 
	payload reuse must not be activated or deacti-
	vated during package transmission
*/

#define CMD_ACTIVATE		0b01010000
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

#define CMD_R_RX_PL_WID		0b01100000
/*
	Read RX-payload width for the top 
	R_RX_PAYLOAD in the RX FIFO.
*/
#define CMD_W_ACK_PAYLOAD	0b10101000	// 1010 1PPP
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
#define CMD_W_TX_PAYLOAD_NO_ACK	0b1011000
//	Used in TX mode. Disables AUTOACK on this specific packet.

#define CMD_NOP			0b11111111
//	No Operation. Might be used to read the STATUS register


/****************************************************************************/
// 			registers
//			page 54
/****************************************************************************/
// defaultne vrijednosti su 0, osim ako nije spomenito drugacije
// defaultne vrijednosti RW, osim ako nije napisano drugacije

#define	REG_CONFIG	0x00
#define	MASK_RX_DR	6	// Mask interrupt caused by RX_DR
				// 1: Interrupt not reflected on the IRQ pin
				// 0: Reflect RX_DR as active low interrupt on the 
				// IRQ pin
#define MASK_TX_DS	5	//  Mask interrupt caused by TX_DS
				// 1: Interrupt not reflected on the IRQ pin
				// 0: Reflect TX_DS as active low interrupt on the 
				// IRQ pin
#define MASK_MAX_RT	4	// Mask interrupt caused by MAX_RT
				// 1: Interrupt not reflected on the IRQ pin
				// 0: Reflect MAX_RT as active low interrupt on the 
				// IRQ pin
#define EN_CRC		3	// Enable CRC. Forced high if one of the bits in 
				// the EN_AA is high		default: 1
#define CRCO		2	// CRC encoding scheme
				// '0' - 1 byte
				// '1' – 2 bytes 
#define PWR_UP		1	// 1: POWER UP, 0:POWER DOWN
#define PRIM_RX		0	// RX/TX control 
				// 1: PRX, 0: PTX 

#define REG_EN_AA	0x01	// Enable ‘Auto Acknowledgment’ Function Dis-
				// able this functionality to be compatible with nRF2401
#define ENAA_P5		5	// Enable auto ack data pipe 5	default: 1
#define ENAA_P4		4	// Enable auto ack data pipe 4	default: 1
#define ENAA_P3		3	// Enable auto ack data pipe 3	default: 1
#define ENAA_P2		2	// Enable auto ack data pipe 2	default: 1
#define ENAA_P1		1	// Enable auto ack data pipe 1	default: 1
#define ENAA_P0		0	// Enable auto ack data pipe 0	default: 1

#define REG_EN_RXADDR	0x02	// Enabled RX Addresses
#define ERX_P5		5	// Enable data pipe 5
#define ERX_P4		4	// Enable data pipe 4
#define ERX_P3		3	// Enable data pipe 3
#define ERX_P2		2	// Enable data pipe 2
#define ERX_P1		1	// Enable data pipe 1	default: 1
#define ERX_P0		0	// Enable data pipe 0	default: 1

#define REG_SETUP_AW	0x03	// Setup of Address Widths (common for all data pipes)
				// vise bajtova adrese - sporiji prijenos
#define AW1		1	// 00 - illegal		01 - 3 bytes	
#define AW0		0	// 10 - 4 bytes		11 - 5 bytes

#define REG_SETUP_RETR	0x04	// Setup of Automatic Retransmission
#define ARD3		7	// Auto Retransmit Delay
#define ARD2		6	// 0000 – Wait 250µs
#define ARD1		5	// 0001 - 500 us
#define ARD0		4	// 0010 - 750 us		// 1111 4000 us
#define ARC3		3	// Auto Retransmit Count
#define ARC2		2	// 0000 retransmit disabled
#define ARC1		1	// 0001	up to 1 retransmit
#define ARC0		0	// 1111 up to 15 retransmit

#define REG_RF_CH	0x05	// RF Channel
#define RF_CH6		6	// Sets the frequency channel nRF24L01 operates on
#define RF_CH5		5	// default [6..0]: 0000010
#define RF_CH4		4
#define RF_CH3		3
#define RF_CH2		2
#define RF_CH1		1
#define RF_CH0		0

#define	REG_RF_SETUP	0x06	// RF Setup Register
#define	PLL_LOCK	4	// Force PLL lock signal. Only used in test
#define	RF_DR		3	// Air Data Rate
				// ‘0’ – 1Mbps
				// ‘1’ – 2Mbps		default
#define RF_PWR1		2
#define RF_PWR0		1	// Set RF output power in TX mode
				// '00' –  -18dBm
				// '01' –  -12dBm
				// '10' –   -6dBm
				// '11' –     0dBm	default
#define	LNA_HCURR	0	// Setup LNA gain	default: 1

#define REG_STATUS	0x07
#define	RX_DR		6	// Data Ready RX FIFO interrupt. Asserted when 
				// new data arrives RX FIFOb.
				// Write 1 to clear bit.
#define	TX_DS		5	// Data Sent TX FIFO interrupt. Asserted when 
				// packet transmitted on TX. If AUTO_ACK is acti-
				// vated, this bit is set high only when ACK is 
				// received.
				// Write 1 to clear bit.
#define	MAX_RT		4	// Maximum number of TX retransmits interrupt
				// Write 1 to clear bit. If MAX_RT is asserted it must 
				// be cleared to enable further communication.
				// default: 0
#define	RX_P_NO2	3	// Data pipe number for the payload available 			RO
				// reading from RX_FIFO
				// 000-101: Data Pipe Number 
#define RX_P_NO1	2	// 110: Not Used						RO
#define RX_P_NO0	1	// 111: RX FIFO Empty			default: 111		RO
#define	TX_FULL		0	// 1: TX FIFO full.

#define REG_OBSERVE_TX	0x08	// Transmit observe register
#define	PLOS_CNT3	7	// Count lost packets. The counter is overflow pro-		RO
#define	PLOS_CNT2	6	// tected to 15, and discontinues at max until 			RO
#define	PLOS_CNT1	5	// reset. The counter is reset by writing to RF_CH. 		RO
#define	PLOS_CNT0	4	// See page 65 and page 74[]					RO
#define ARC_CNT3	3	//								RO
#define ARC_CNT2	2	// Count retransmitted packets. 				RO
#define ARC_CNT1	1	// Count retransmitted packets. The counter is 			RO
#define ARC_CNT0	0	// reset when transmission of a new packet starts. 		RO

#define REG_CD		0x09	// carrier detect
#define CD		0	// default: 0							RO

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
#define REG_RX_PW_P0	0x11	// Number of bytes in RX payload in data pipe 0
#define RX_PW_P0_5	5	// 	1 to 32 bytes
#define RX_PW_P0_4	4	// 1 - 1 byte
#define RX_PW_P0_3	3	// 32 - 32 bytes
#define RX_PW_P0_2	2	
#define RX_PW_P0_1	1	
#define RX_PW_P0_0	0	

#define REG_RX_PW_P1	0x12	// Number of bytes in RX payload in data pipe 1
#define RX_PW_P1_5	5	// 	1 to 32 bytes
#define RX_PW_P1_4	4	// 1 - 1 byte
#define RX_PW_P1_3	3	// 32 - 32 bytes
#define RX_PW_P1_2	2	
#define RX_PW_P1_1	1	
#define RX_PW_P1_0	0	

#define REG_RX_PW_P2	0x13	// Number of bytes in RX payload in data pipe 2
#define RX_PW_P2_5	5	// 	1 to 32 bytes
#define RX_PW_P2_4	4	// 1 - 1 byte
#define RX_PW_P2_3	3	// 32 - 32 bytes
#define RX_PW_P2_2	2	
#define RX_PW_P2_1	1	
#define RX_PW_P2_0	0	

#define REG_RX_PW_P3	0x14	// Number of bytes in RX payload in data pipe 3
#define RX_PW_P3_5	5	// 	1 to 32 bytes
#define RX_PW_P3_4	4	// 1 - 1 byte
#define RX_PW_P3_3	3	// 32 - 32 bytes
#define RX_PW_P3_2	2	
#define RX_PW_P3_1	1	
#define RX_PW_P3_0	0	

#define REG_RX_PW_P4	0x15	// Number of bytes in RX payload in data pipe 4
#define RX_PW_P4_5	5	// 	1 to 32 bytes
#define RX_PW_P4_4	4	// 1 - 1 byte
#define RX_PW_P4_3	3	// 32 - 32 bytes
#define RX_PW_P4_2	2	
#define RX_PW_P4_1	1	
#define RX_PW_P4_0	0	

#define REG_RX_PW_P5	0x16	// Number of bytes in RX payload in data pipe 5
#define RX_PW_P5_5	5	// 	1 to 32 bytes
#define RX_PW_P5_4	4	// 1 - 1 byte
#define RX_PW_P5_3	3	// 32 - 32 bytes
#define RX_PW_P5_2	2	
#define RX_PW_P5_1	1	
#define RX_PW_P5_0	0	

#define REG_FIFO_STATUS	0x17	// FIFO Status Register
#define TX_REUSE	6	// Reuse last transmitted data packet if set high. 	RO
				// The packet is repeatedly retransmitted as long 
				// as CE is high. TX_REUSE is set by the SPI com
				// mand REUSE_TX_PL, and is reset by the SPI 
				// commands W_TX_PAYLOAD or FLUSH TX
// zove se TX_FULL2 jer gore vec ima TX_FULL
#define TX_FULL2		5	// TX FIFO full flag. 1: TX FIFO full. 0: Available 	RO
				// locations in TX FIFO.
#define TX_EMPTY	4	// TX FIFO empty flag. 					RO
				// 1: TX FIFO empty. 
				// 0: Data in TX FIFO.
#define RX_FULL		1	// RO
#define RX_EMPTY	0	// RO

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

#define REG_DYNPD	0x1C	// Enable dynamic payload length
#define DPL_P5		5	// Enable dyn. payload length  data pipe 5. 
				// (Requires EN_DPL and ENAA_P5)
#define DPL_P4		4	// Enable dyn. payload length  data pipe 4. 
				// (Requires EN_DPL and ENAA_P5)
#define DPL_P3		3	// Enable dyn. payload length  data pipe 3. 
				// (Requires EN_DPL and ENAA_P5)
#define DPL_P2		2	// Enable dyn. payload length  data pipe 2. 
				// (Requires EN_DPL and ENAA_P5)
#define DPL_P1		1	// Enable dyn. payload length  data pipe 1. 
				// (Requires EN_DPL and ENAA_P5)
#define DPL_P0		0	// Enable dyn. payload length  data pipe 0. 
				// (Requires EN_DPL and ENAA_P5)

#define REG_FEATURE	0x1D	// Feature Register
#define EN_DPL		2	// Enables Dynamic Payload Length
#define EN_ACK_PAY	1	// Enables Payload with ACK
#define EN_DYN_ACK	0	// Enables the W_TX_PAYLOAD_NOACK command

void nRF1_main(void);
