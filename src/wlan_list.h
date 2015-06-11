#ifndef WLAN_LIST_H
#define WLAN_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "debug.h"
#include "uart.h"
#include "wlan_hw.h"

// new data types
// mora bit javno zbog returna funkcija
typedef struct
{
    const char  *encription;
    char    	SSID[33];   // SSID max 32 okteta
    int8_t		strength;
    char		BSSID[20];  // 17 + "" + NULL 
    uint8_t		channel;
} wlan_list_t;

// functions prototypes
wlan_list_t	wlan_list_get(uint8_t number);
int8_t		wlan_list_print(wlan_modul_t *wlan0);
void 		wlan_list_init(void);
int8_t		wlan_list_ready(wlan_modul_t *wlan0);

#define BUFFER_SIZE 68	// koliko ce maksimalno bit dugacak string za jednu mrezu (enc+SSID+strength+BSSID+channel)
						// 13 + 33 + 1 + 20 + 1 = 68
#define WLAN_LIST_MAX 20	// koliko max mreza odjednom cemo uspjet nac
#define WLAN_LIST 10	// koliko najjacih mreza ce isprintat

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// WLAN_LIST_H
