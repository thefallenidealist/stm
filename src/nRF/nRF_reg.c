/*************************************************************************************************
				read_reg()
*************************************************************************************************/
static uint8_t read_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	DEBUG_START;
	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	spi_rw(spi_port, CMD_R_REGISTER + reg);
	status = spi_rw(spi_port, CMD_NOP);	// dummy write
	cs(nRF0, 1);

	DEBUG_END;
	return status;
}
/*************************************************************************************************
				print_reg()
*************************************************************************************************/
static void print_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	DEBUG_START;

	if ( (reg < 0x00) || (reg > 0x1D) )
	{
		printf("%s(): Zajeb, wrong register 0x%X, exiting\n", __func__, reg);
		return;
	}

	const char *registers[] = { "CONFIG", "EN_AA", "EN_RXADDR", "SETUP_AW", "SETUP_RETR", "RF_CH",
								"RF_SETUP", "STATUS", "OBSERVE_TX", "CD", "RX_ADDR_P0",
								"RX_ADDR_P1", "RX_ADDR_P2", "RX_ADDR_P3", "RX_ADDR_P4",
								"RX_ADDR_P5", "TX_ADDR", "RX_PW_P0", "RX_PW_P1", "RX_PW_P2",
								"RX_PW_P3", "RX_PW_P4", "RX_PW_P5", "FIFO_STATUS", "0x18", "0x19",
								"0x1A", "0x1B", "REG_DYNPD", "REG_FEATURE"};

	uint8_t status = read_reg(nRF0, reg);

	printf("Reading reg: 0x%02X: %3d = 0b%s \t %s\n", reg, status, dec2bin8_str(status), registers[reg]);	

	DEBUG_END;
}

#define REG_T_EMPTY 		2	// bilo sto sto nije 0 ili 1
#define BITS_IN_REGISTER	8	// nRF ima 8-bitne registre
uint8_t reg_tmp[BITS_IN_REGISTER] = { [0 ... (BITS_IN_REGISTER-1)] = REG_T_EMPTY};	// popuni registar sa EMPTY vrijednostima
/*************************************************************************************************
				write_reg()
*************************************************************************************************/
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg)
{
	// zapisuje odredjeni bit u odredjeni registar
	// koristi globalnu varijablu reg_tmp[] za tu namjenu
	DEBUG_START;

	uint8_t old_value = read_reg(nRF0, reg);
	uint8_t bits = 0;
	uint8_t mask = 0;

	for (uint8_t i=0; i<BITS_IN_REGISTER; i++)
	{
		if (reg_tmp[i] != REG_T_EMPTY)
		{
			bits += reg_tmp[i] << i;	// pretvori u 8b vrijednost
		}
		else
		{
			mask += 1 << i;		// zapisi 1 na mjesto koje se ne treba mijenjat
		}
	}

	uint8_t new_value = (old_value & mask) | bits;

	write_reg_full(nRF0, reg, new_value);

	memset(reg_tmp, REG_T_EMPTY, BITS_IN_REGISTER);	// pocisti

	DEBUG_END;
	return 0;
}

/*************************************************************************************************
				write_reg_full()
*************************************************************************************************/
static uint8_t write_reg_full(nRF_hw_t *nRF0, uint8_t reg, uint8_t value)
{
	DEBUG_START;

	// TODO maknit ovo vracanje statusa?
	// TODO stavit da nakon zapisivanja procita taj registar i usporedi jel jednak onome sto je trebalo zapisat
	// 		ako jest, vrati 0, inace -1

	uint8_t spi_port = nRF0->spi_port;

	//printf("%s(): reg: 0x%X, value: %d\n", __func__, reg, value);

	cs(nRF0, 0);
	spi_rw(spi_port, reg + CMD_W_REGISTER);	// select register
	spi_rw(spi_port, value);				// write value
	cs(nRF0, 1);

	DEBUG_END;
	//return status;
	return 0;
}
