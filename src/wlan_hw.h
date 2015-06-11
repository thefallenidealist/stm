#ifndef WLAN_HW_H
#define WLAN_HW_H

#ifdef __cplusplus
extern "C" {
#endif

// created 150129
#include "debug.h"
#include "uart.h"

// 3.3V
// CH_PD ide u Vcc      nemoj promasit pin
// 9600N1
// bas jako, jako ocekuje \n na kraju komande

// forward declaration
struct wlan_modul_t;
struct wlan_hw_t;		// neka se nadje
typedef struct wlan_modul_t wlan_modul_t;

// enum je nemoguce unaprijed deklarirat, mora bit ovdje
typedef enum
{
	WLAN_SCAN_NOT_STARTED = 0,
	WLAN_SCAN_IN_PROGRESS,
	WLAN_SCAN_DONE,
	WLAN_SCAN_PRINTED
} wlan_event_t;

typedef struct
{
	uint8_t  uart_number;
	uint16_t uart_speed;
} wlan_hw_t;

struct wlan_modul_t
{
	wlan_hw_t	 	hw;
	char			*buffer;	// pokazuje na UART buffer koji koristi
	wlan_event_t	event;
	void 			(*scan)		(wlan_modul_t *wlan0);
	bool			(*scan_done)(wlan_modul_t *wlan0);
};

// javni prototipi
wlan_modul_t	*wlan_new(uint8_t uart, uint32_t speed);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// WLAN_HW_H
