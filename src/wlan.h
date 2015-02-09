#ifndef WLAN_H
#define WLAN_H
// created 150129
#include "debug.h"
#include "uart.h"

// 3.3V
// CH_PD ide u Vcc      nemoj promasit pin
// 9600N1
// bas jako, jako ocekuje \n na kraju komande

//typedef struct wlan_t wlan_t;
#define MAX_WLAN    50  // koliko mreza mozemo pronac odjednom
#define WLAN_UART_NUMBER	2
#define WLAN_UART_SPEED		9600

typedef struct
{
	uint8_t  uart_number;
	uint16_t uart_speed;
} wlan_hw_t;

//extern wlan_hw_t wlan_hw;
//extern wlan_hw_t wlan_hw;

typedef struct
{
    const char  *encription;
    char    	SSID[33];   // SSID max 32 okteta
    int8_t		strength;
    char		BSSID[20];  // 17 + "" + NULL 
    uint8_t		channel;
} wlan_list_t;

typedef enum
{
	WLAN_SCAN_NOT_STARTED = 0,
	WLAN_SCAN_IN_PROGRESS,
	WLAN_SCAN_DONE,
	WLAN_PRINTED
} wlan_event_t;

extern wlan_event_t wlan_event;

void wlan_parse(void);
wlan_list_t wlan_get_list(uint8_t number);
void wlan_scan();
bool wlan_is_scan_done();
void wlan_init();
void wlan_print();
//void wlan_main(void);
//void wlan_loop(void);

#endif
