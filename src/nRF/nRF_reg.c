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

	uint8_t status = read_reg(nRF0, reg);

	printf("reading reg: 0x%02X: %3d = 0b%s\n", reg, status, dec2bin8_str(status));	

	DEBUG_END;
}

/*************************************************************************************************
				write_reg()
*************************************************************************************************/
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg)
{
	DEBUG_START;

	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	cs(nRF0, 0);
	status = spi_rw(spi_port, reg + CMD_W_REGISTER);
	spi_rw(spi_port, arg);
	cs(nRF0, 1);

	DEBUG_END;
	return status;
}
