#ifndef WLAN_LIST_H
#define WLAN_LIST_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "debug.h"
#include "uart.h"
#include "wlan_hw.h"

typedef struct
{
    const char  *encription;
    char    	SSID[33];   // SSID max 32 okteta
    int8_t		strength;
    char		BSSID[20];  // 17 + "" + NULL 
    uint8_t		channel;
} wlan_list_t;

wlan_list_t wlan_get_list(uint8_t number);
//void wlan_print();
int8_t wlan_print(wlan_modul_t *wlan0);
void wlan_list_init();

#define BUFFER_SIZE 68	// koliko ce maksimalno bit dugacak string za jednu mrezu (enc+SSID+strength+BSSID+channel)
						// 13 + 33 + 1 + 20 + 1 = 68
#define WLAN_LIST_MAX 20	// koliko max mreza odjednom cemo uspjet nac
#define WLAN_LIST 10	// koliko najjacih mreza ce isprintat

#endif
