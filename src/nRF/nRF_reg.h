#ifndef NRF_REG_H
#define NRF_REG_H
// created 141228

/*************************************************************************************************
 			CMD
*************************************************************************************************/
#define CMD_R_REGISTER		0
#define CMD_W_REGISTER		32
#define CMD_R_RX_PAYLOAD	0b01100001
#define CMD_W_TX_PAYLOAD	0b10100000
#define	CMD_FLUSH_TX		0b11100001
#define CMD_FLUSH_RX		0b11100010
#define CMD_REUSE_TX_PL		0b11100011
#define CMD_ACTIVATE		0b01010000
#define CMD_R_RX_PL_WID		0b01100000
#define CMD_W_ACK_PAYLOAD	0b10101000	// 1010 1PPP
#define CMD_W_TX_PAYLOAD_NO_ACK	0b1011000
#define CMD_NOP				0b11111111

/*************************************************************************************************
 			registers
*************************************************************************************************/
#define	REG_CONFIG	0x00
#define	MASK_RX_DR	6	
#define MASK_TX_DS	5	
#define MASK_MAX_RT	4	
#define EN_CRC		3	
#define CRCO		2	
#define PWR_UP		1	
#define PRIM_RX		0	

#define REG_EN_AA	0x01	
#define ENAA_P5		5		
#define ENAA_P4		4		
#define ENAA_P3		3		
#define ENAA_P2		2		
#define ENAA_P1		1		
#define ENAA_P0		0		

#define REG_EN_RXADDR	0x02	
#define ERX_P5		5			
#define ERX_P4		4			
#define ERX_P3		3			
#define ERX_P2		2			
#define ERX_P1		1			
#define ERX_P0		0			

#define REG_SETUP_AW	0x03	
#define AW1		1				
#define AW0		0				

#define REG_SETUP_RETR	0x04	
#define ARD3		7			
#define ARD2		6			
#define ARD1		5			
#define ARD0		4			
#define ARC3		3			
#define ARC2		2			
#define ARC1		1			
#define ARC0		0			

#define REG_RF_CH	0x05	
#define RF_CH6		6		
#define RF_CH5		5		
#define RF_CH4		4
#define RF_CH3		3
#define RF_CH2		2
#define RF_CH1		1
#define RF_CH0		0

#define	REG_RF_SETUP	0x06	
#define	PLL_LOCK	4			
#define	RF_DR		3			
#define RF_PWR1		2			
#define RF_PWR0		1			


#define REG_STATUS	0x07
#define	RX_DR		6	
#define	TX_DS		5	
#define	MAX_RT		4	
#define	RX_P_NO2	3	
#define RX_P_NO1	2	
#define RX_P_NO0	1	
#define	TX_FULL		0	

#define REG_OBSERVE_TX	0x08	
#define	PLOS_CNT3	7	
#define	PLOS_CNT2	6	
#define	PLOS_CNT1	5	
#define	PLOS_CNT0	4	
#define ARC_CNT3	3	
#define ARC_CNT2	2	
#define ARC_CNT1	1	
#define ARC_CNT0	0	

#define REG_CD		0x09	
#define CD			0		

#define REG_RX_ADDR_P0	0x0A	
#define REG_RX_ADDR_P1	0x0B	
#define REG_RX_ADDR_P2	0x0C	
#define REG_RX_ADDR_P3	0x0D	
#define REG_RX_ADDR_P4	0x0E	
#define REG_RX_ADDR_P5	0x0F	
#define REG_TX_ADDR	0x10		

#define REG_RX_PW_P0	0x11	
#define RX_PW_P0_5	5			
#define RX_PW_P0_4	4			
#define RX_PW_P0_3	3			
#define RX_PW_P0_2	2	
#define RX_PW_P0_1	1	
#define RX_PW_P0_0	0	

#define REG_RX_PW_P1	0x12	
#define RX_PW_P1_5	5			
#define RX_PW_P1_4	4			
#define RX_PW_P1_3	3			
#define RX_PW_P1_2	2	
#define RX_PW_P1_1	1	
#define RX_PW_P1_0	0	

#define REG_RX_PW_P2	0x13	
#define RX_PW_P2_5	5			
#define RX_PW_P2_4	4			
#define RX_PW_P2_3	3			
#define RX_PW_P2_2	2	
#define RX_PW_P2_1	1	
#define RX_PW_P2_0	0	

#define REG_RX_PW_P3	0x14	
#define RX_PW_P3_5	5			
#define RX_PW_P3_4	4			
#define RX_PW_P3_3	3			
#define RX_PW_P3_2	2	
#define RX_PW_P3_1	1	
#define RX_PW_P3_0	0	

#define REG_RX_PW_P4	0x15	
#define RX_PW_P4_5	5			
#define RX_PW_P4_4	4			
#define RX_PW_P4_3	3			
#define RX_PW_P4_2	2	
#define RX_PW_P4_1	1	
#define RX_PW_P4_0	0	

#define REG_RX_PW_P5	0x16	
#define RX_PW_P5_5	5			
#define RX_PW_P5_4	4			
#define RX_PW_P5_3	3			
#define RX_PW_P5_2	2	
#define RX_PW_P5_1	1	
#define RX_PW_P5_0	0	

#define REG_FIFO_STATUS	0x17	
#define TX_REUSE	6			

#define TX_FULL2	5			
#define TX_EMPTY	4			
#define RX_FULL		1			
#define RX_EMPTY	0			

#define REG_DYNPD	0x1C	
#define DPL_P5		5		
#define DPL_P4		4		
#define DPL_P3		3		
#define DPL_P2		2		
#define DPL_P1		1		
#define DPL_P0		0		

#define REG_FEATURE	0x1D	
#define EN_DPL		2		
#define EN_ACK_PAY	1		
#define EN_DYN_ACK	0		

#endif
