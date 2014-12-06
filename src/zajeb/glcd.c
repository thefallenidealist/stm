//glcd.c STM32

void glcd_cs_low()
{
	GPIO_ResetBits(GLCD_CS_PORT, GLCD_CS_PIN);
}

void glcd_cs_high()
{
	GPIO_SetBits(GLCD_CS_PORT, GLCD_CS_PIN);
}

void glcd_dc_low()
{
	GPIO_ResetBits(GLCD_DC_PORT, GLCD_DC_PIN);
}

void glcd_dc_high()
{
	GPIO_SetBits(GLCD_DC_PORT, GLCD_DC_PIN);
}

void glcd_led_off()
{
	GPIO_ResetBits(GLCD_LED_PORT, GLCD_LED_PIN);
}

void glcd_led_on()
{
	GPIO_SetBits(GLCD_LED_PORT, GLCD_LED_PIN);
}

void glcd_rst_off()
{
	// RESET = 1
	GPIO_SetBits(GLCD_RESET_PORT, GLCD_RESET_PIN);
}

void glcd_rst_on()
{
	// RESET = 0
	GPIO_ResetBits(GLCD_RESET_PORT, GLCD_RESET_PIN);
}
