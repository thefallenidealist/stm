#include "cmd.h"
//#include "rtc2.h"
#include "colors_ansi.h"
#include "debug.h"

void uart_cmd(char *cmd, char *arg)
{
    DEBUG_START;
	//printf("uart_cmd() cmd: %s\n", cmd);
	//printf("uart_cmd() arg: %s\n", arg);
    // TODO strncmp

	int r;
	r = strcmp(cmd, "wlan");
	if (r == 0)
	{
		// dobivenom argumentu cemo dodar CR i NL
		char arg_copy[UART_MAX_LENGTH] = {};	// 

		strncpy(arg_copy, arg, UART_MAX_LENGTH-1);
		strncat(arg_copy, "\r\n", 3);	// CR NL i null

        if (debug_level > 1)
        {
		    printf("na UART2 saljem: %s\n", arg_copy);
        }
		uart_puts(2, arg_copy);
	}

    r = strcmp(cmd, "print");
	if (r == 0)
	{
		if (uart2_rx_event == RX_IN_PROGRESS)
		{
			printf("RX is not done yet\n");
		}
		else
		{
			printf("Printam WLAN buffer:\n");
			//wlan_main();
		}
	}

	r = strcmp(cmd, "led");
	if (r == 0)
	{
		printf("LED PA1 toggle\n");
		uint8_t state = (uint8_t) atoi(&arg[0]);
		gpio_write("PA1", state);
		//glcd_test();
	}

	r = strcmp(cmd, "nrf");
	if (r == 0)
	{
		//uint8_t arg1 = 
	}


	//r = strcmp(cmd, "set date");
	r = strcmp(cmd, "set time");
	if (r == 0)
	{
		printf("Na serijski smo dobili \"set time\"\n");
		printf("arg: %s\n", arg);
		// format argumenta: hh:mm:ss
		uart_parse_rtc(arg);

	}
    DEBUG_END;
}

/************************************************************************************************
*  				uart1_parse()							*
*************************************************************************************************/
// ovo poziva USART interrupt
//void uart1_parse(void)
void uart_parse(void)
	// TODO da radi za sve USARTe
{
	// ono sto dobije razbije na dva komada. 

    DEBUG_START;


	// inicijaliziraj za slucaj da treba ispisat prazni string
	char  rx_string_copy_arr[UART_MAX_LENGTH] = {};
	char *rx_string_copy = rx_string_copy_arr;

	//char *rx_string 	= uart1_rx_string_arr;          // XXX ne smije bit volatile char jer se smrzne program
	char *rx_string 	= (char *)&uart1_rx_string_arr[0];  // cast da se kompjajler ne buni
	char cmd[UART_MAX_LENGTH] = {};
	char arg[UART_MAX_LENGTH] = {};
	int cmd_delimiter = ':';		// TODO const

	// kopiraj, da ne razjebemo originalni string
	strncpy(rx_string_copy, rx_string, UART_MAX_LENGTH-1);

	char *delimiter_position = strchr(rx_string_copy, cmd_delimiter);		// nadji mjesto gdje je delimiter

	if (delimiter_position != NULL)
	{
		*delimiter_position = '\0';	// na mjesto gdje pokazuje tmp (gdje je delimiter) ubaci null i skrati glavni string
		strncpy(cmd, rx_string_copy, sizeof(cmd));
		strncpy(arg, delimiter_position+1, sizeof(arg));

		//printf("cmd: %s\n", cmd);
		//printf("arg: %s\n", arg);

		uart_cmd(cmd, arg);	// provjeri sto smo to dobili
	}
	else
	{
		printf("u stringu nije nadjen delimiter\n");
		//uart_puts(2, "u stringu nije nadjen delimiter\n");
	}
    DEBUG_END;
}

void uart_parse_rtc(const char* arg)
{
	// dobije string formata hh:mm:ss
	char arg_copy[10];	// 9 mu je zapravo dosta, al ajde

	// kopiraj da ne razjebes original
	strncpy(arg_copy, arg, sizeof(arg_copy));

	printf("original string: %s\n", arg);
	printf("kopirani string: %s\n", arg_copy);

	// vrati nazad uint8_t {h, m, s}	XXX

	// postavi vrijeme koje je zadano
	//rtc_set_time(hours, minutes, seconds);
}
