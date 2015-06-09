#include "oled.h"

#define OLED_ADDR_W		0x78

#define OLED_CMD			0x22
#define OLED_DATA			0x40

#define OLED_SET_CONTRAST	0x81	// after that send 8b contrast value
#define OLED_SUSPEND_ON		0xA4	// Output follows RAM content   default after reset
#define OLED_SUSPEND_OFF	0xA5
#define OLED_INVERSE_OFF	0xA6	// 0 is off, 1 is on		default after reset
#define OLED_INVERSE_ON		0xA7
#define OLED_DISPLAY_ON		0xAF
#define OLED_DISPLAY_OFF	0xAE	// sleep mode, default after reset
// scrolling commands TODO
// 0x00..0x0F
// 0x10..0x1F


/*************************************************************************************************
				oled_io_init()
*************************************************************************************************/
void oled_io_init(void)
{
	i2c_init(2,100000);
}

/*************************************************************************************************
				oled_write_cmd()
*************************************************************************************************/
void oled_write_cmd(uint8_t cmd)
{
	i2c_start(2);
	i2c_write(2, OLED_ADDR_W);
	i2c_write(2, OLED_CMD);
	i2c_write(2, cmd);
	i2c_stop(2);
}

/*************************************************************************************************
				oled_write_data()
*************************************************************************************************/
void oled_write_data(uint8_t data)
{
	i2c_start(2);
	i2c_write(2, OLED_ADDR_W);
	i2c_write(2, OLED_DATA);
	i2c_write(2, data);
	i2c_stop(2);
}
