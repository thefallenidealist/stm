#include "wlan_hw.h"
// 3.3V, CH_PD ide u Vcc

#define WLAN_MAX_HW 	5	// koliko ce najvise bit odjednom ustekano WLAN modula
static wlan_modul_t wlan_moduls[WLAN_MAX_HW];

// privatni prototipi
static void hw_init(wlan_modul_t *wlan0);
static void scan(wlan_modul_t *wlan0);
static bool scan_done();

/*************************************************************************************************
  				wlan_new()
*************************************************************************************************/
wlan_modul_t *wlan_new(uint8_t uart, uint16_t speed)
{
	DEBUG_START;

	wlan_modul_t wlan0;

	wlan0.hw.uart_number = uart;
	wlan0.hw.uart_speed = speed;
	wlan0.buffer = (char *)&uart2_rx_string_arr[0];	// XXX hardcoded
			// casting da se umiri kompajler jer je array volatile
	wlan0.event = WLAN_SCAN_NOT_STARTED;
	wlan0.scan = scan;
	wlan0.scan_done = scan_done;

	static uint8_t wlan_hw_counter;

	if (wlan_hw_counter < WLAN_MAX_HW)
	{
		memcpy(&wlan_moduls[wlan_hw_counter], &wlan0, sizeof(wlan_moduls[wlan_hw_counter]));	// spremi u globalno polje
	}
	else
	{
		ERROR("Nije moguce kreirati jos WLAN modula");
		printf(", maksimalno modula je: %d\n", WLAN_MAX_HW);
		return NULL;
	}

	// napravi odmah i init
	hw_init(&wlan_moduls[wlan_hw_counter]);

	DEBUG_END;
	//printf("%s() ce vratit: %p\n", __func__, &wlan_moduls[wlan_hw_counter]);
	return &wlan_moduls[wlan_hw_counter++];
}

/*************************************************************************************************
  				hw_init()
*************************************************************************************************/
static void hw_init(wlan_modul_t *wlan0)
{
	DEBUG_START;

	uart_init(wlan0->hw.uart_number, wlan0->hw.uart_speed);

	DEBUG_END;
}

/*************************************************************************************************
  				scan()
*************************************************************************************************/
static void scan(wlan_modul_t *wlan0)
{
	DEBUG_START;

	uint8_t uart = wlan0->hw.uart_number;

	uart_puts(uart, "AT+CWLAP\r\n");	// OH, oh, ne zaboravi \r\n
	wlan0->event = WLAN_SCAN_IN_PROGRESS;

	DEBUG_END;
}

/*************************************************************************************************
  				scan_done()
*************************************************************************************************/
static bool scan_done(wlan_modul_t *wlan0)
{
	//DEBUG_START;

	//if ( (strstr((char *)uart2_rx_string_arr, "OK") != 0) && (wlan_event == WLAN_SCAN_IN_PROGRESS) )
	//if (strstr((char *)uart2_rx_string_arr, "OK"))	// TODO buffer
	if ( (strstr(wlan0->buffer, "OK")) && (wlan0->event == WLAN_SCAN_IN_PROGRESS) )
	{
		wlan0->event = WLAN_SCAN_DONE;
		DEBUG_INFO("WLAN scan done\n");

		//DEBUG_END;
		return 1;
	}
	else if (wlan0->event == WLAN_SCAN_IN_PROGRESS)
	{
		DEBUG_INFO("skeniranje u tijeku\n");
		//glcd_string("WLAN:", 0, 0, 4, white);
		//glcd_string("skeniranje u tijeku", 0, 40, 2, red);

		// ovdje stalno dolazi drugi puta

		//DEBUG_END;
		return 0;
	}
	else if (wlan0->event == WLAN_SCAN_PRINTED)
	{
		return 1;
	}
	else
	{
		//printf(".\n");
		//DEBUG_END;
		return 0;
	}
}

/*************************************************************************************************
  				get_event()
*************************************************************************************************/
/*
// drugacija verzija ovoga gore
static wlan_event_t get_event(wlan_modul_t *wlan0)
{
	//DEBUG_START;

	//if ( (strstr((char *)uart2_rx_string_arr, "OK") != 0) && (wlan_event == WLAN_SCAN_IN_PROGRESS) )
	//if (strstr((char *)uart2_rx_string_arr, "OK"))	// TODO buffer
	if ( (strstr(wlan0->buffer, "OK")) && (wlan0->event == WLAN_SCAN_IN_PROGRESS) )
	{
		wlan0->event = WLAN_SCAN_DONE;
		DEBUG_INFO("WLAN scan done\n");

		//DEBUG_END;
		return 1;
	}
	else if (wlan0->event == WLAN_SCAN_IN_PROGRESS)
	{
		DEBUG_INFO("skeniranje u tijeku\n");
		//glcd_string("WLAN:", 0, 0, 4, white);
		//glcd_string("skeniranje u tijeku", 0, 40, 2, red);

		//DEBUG_END;
		return 0;
	}
	else
	{
		//printf(".\n");
		//DEBUG_END;
		return 0;
	}
}
*/
