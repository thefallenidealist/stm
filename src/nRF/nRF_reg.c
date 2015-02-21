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
	status = spi_rw(spi_port, 0x00);	// dummy write
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

	printf("reading reg: 0x%X: %3d = 0b%s\n", reg, status, dec2bin8_str(status));	

	DEBUG_END;
}

/*************************************************************************************************
				write_reg()
*************************************************************************************************/
static uint8_t write_reg(nRF_hw_t *nRF0, uint8_t reg, uint8_t arg, uint8_t bits)
{
	DEBUG_START;
	uint8_t old_value = read_reg(nRF0, reg);

	printf("register: 0x%X, old: %d, new: %d\n", reg, old_value, arg);
	printf("\t\t\t\tbits: %d\n", bits);

	//uint8_t new_value = old

	uint8_t status;
	uint8_t spi_port = nRF0->spi_port;

	//printf("SPI ce zapisat: %d %d\n", reg + CMD_W_REGISTER, (old_reg | arg));

	cs(nRF0, 0);
	status = spi_rw(spi_port, reg + CMD_W_REGISTER);
	//spi_rw(spi_port, (old_value & arg));
	spi_rw(spi_port, arg);
	cs(nRF0, 1);

	DEBUG_END;
	return status;
}
