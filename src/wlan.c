#include "wlan.h"
// 3.3V, CH_PD ide u Vcc

#include <string.h>
#include <stdlib.h>     // atoi
#include <stdbool.h>
// TODO zamijenit memcpy sa memmove FreeBSDov memcpy dopusta kopiranje stringova koji se preklapaju

#define BUFFER_SIZE 100 // koliko ce maksimalno bit dugacak string za jednu mrezu (enc+SSID+strength+BSSID+channel)

// HW
wlan_hw_t wlan_hw;

wlan_t wlan_list[MAX_WLAN]; // polje objekata
//volatile char *pbuffer = uart2_rx_string_arr;
char *pbuffer = (char *)uart2_rx_string_arr;
char encription[5][13];

wlan_event_t wlan_event = WLAN_SCAN_NOT_STARTED;

//void wlan_print(wlan_t wlan_list[])
void wlan_print()
{
	INFO_START;

	wlan_parse();
    // printaj sve dok ne naidjes na prazan SSID
    uint8_t i = 0;

    do
    {
            printf("%02d ", i);
            printf("encription: %s\t",  wlan_list[i].encription);
            printf("SSID: %s\t\t",      wlan_list[i].SSID);
            printf("\tstrength: %d\t",  wlan_list[i].strength);
            printf("BSSID: %s\t",       wlan_list[i].BSSID);
            printf("channel: %d\t",     wlan_list[i].channel);
            printf("\n");

            i++;
    } while (strlen(wlan_list[i].SSID));

	INFO_END;
}



/*
   poslozi listu WLANova po jacini signala, od najveceg, prema najmanjem
   mijenja dobiveni argument
   najlosiji signal je -95, bolji su oni blize 0
*/
static void poslozi(wlan_t wlan_list[])
{
	INFO_START;

    // bubble sort
    wlan_t tmp_copy;
    bool swapped = false;

    do
    {
        swapped = false;
        wlan_t *trenutni, *prethodni, *tmp;

        uint8_t i=0;

        // radi sve dok ne naidjes na prazni SSID
        while (strlen(wlan_list[i].SSID))
        {
            trenutni = &wlan_list[i];
            prethodni = &wlan_list[i-1];
            tmp = &tmp_copy;

            if (prethodni->strength < trenutni->strength)
            {
                // zamijeni
                //printf("mijenjam mjesta za pozicije: %d %d\n", i, i-1);

                memcpy(tmp, prethodni, sizeof(*tmp));   // prethodni ide u tmp
                memcpy(prethodni, trenutni, sizeof(*prethodni)); // trenutni ide u prethodni
                memcpy(trenutni, tmp, sizeof(*trenutni)); // tmp ide u prethodni
                swapped = true;
            }
            i++;
        }
    } while (swapped == true);
	INFO_END;
}

/*************************************************************************************************
  				wlan_init()
*************************************************************************************************/
void wlan_init()
{
	INFO_START;

    strcpy(encription[0], "OPEN");
    strcpy(encription[1], "WEP");
    strcpy(encription[2], "WPA_PSK");
    strcpy(encription[3], "WPA2_PSK");
    strcpy(encription[4], "WPA_WPA2_PSK");

	wlan_hw.uart_number = WLAN_UART_NUMBER;
	wlan_hw.uart_speed  = WLAN_UART_SPEED;

	// TODO napravit jednu funkciju za UARTe
	if (wlan_hw.uart_number == 1)
	{
		printf("%s(): pozivam uart1_init(%d)\n", __func__, wlan_hw.uart_speed);
		uart1_init(wlan_hw.uart_speed);
	}
	if (wlan_hw.uart_number == 2)
	{
		printf("%s(): pozivam uart2_init(%d)\n", __func__, wlan_hw.uart_speed);
		uart2_init(wlan_hw.uart_speed);
	}

	INFO_END;
}


/*************************************************************************************************
  				wlan_parse()
*************************************************************************************************/
void wlan_parse()
{
	INFO_START;

    // razdvoji na redove, delimiter su ()
    char * token;
    while ((token = strsep(&pbuffer, "()")) != NULL)
    {
        //printf("token: %s\n", token);

        static uint8_t wlan_number = 0;
        // ako nema CWLAN nit ~ u liniji, zapisi ga u polje
        if (strstr(token, "CWLAP") == NULL) 
        {

            static uint8_t wlan_atribute_counter;

            char *token2;
            // razbij string na redove, zared je delimiter
            while ((token2 = strsep(&token, ",")) != NULL)
            {
                //printf("wlan_number: %d\t wlan_atribute_counter: %d\ttoken2: %s\n", wlan_number, wlan_atribute_counter, token2);

                // TODO napravit manje retardirano
                if (wlan_atribute_counter == 0)
                {
                    wlan_list[wlan_number].encription = encription[atoi(token2)];
                }
                else if (wlan_atribute_counter == 1)
                {
                    strncpy(wlan_list[wlan_number].SSID, token2, sizeof(wlan_list[wlan_number].SSID));
                    // TODO maknit ""
                }
                else if (wlan_atribute_counter == 2)
                {
                    //wlan_list[wlan_number].strength = atoi(token2);	// XXX ovdje zaglavi na ARMu, na PCu radi kako treba
								// zaglavi negdje u _strtol_r() (newlib atoi je implementiran kao strtol)
								// token2 ima \0 na kraju, dug je 3(strlen) 4(sizeof)
								// clang 3.6, newlib iz "gcc version 4.8.4 20140725 (release)"

					int8_t strength = atoi(&token2[1]);	// samo pozitivni dio, da se atoi ne zaglavi

					// pretvori u 1-5
					strength = (100-strength)/10 +1;
					if (strength >= 5)
					{
						strength = 5;
					}
					if (strength < 0)
					{
						strength = 0;
					}

                    wlan_list[wlan_number].strength = strength;
                }
                else if (wlan_atribute_counter == 3)
                {
                    strncpy(wlan_list[wlan_number].BSSID, token2, sizeof(wlan_list[wlan_number].BSSID));
                    // TODO maknit ""
                }
                else if (wlan_atribute_counter == 4)
                {
                    wlan_list[wlan_number].channel = atoi(token2);
                }

                wlan_atribute_counter++;
            }
            wlan_atribute_counter=0;    // 0..4
            wlan_number++;
        }
        // TODO 0,1,1,2,2,3,3... moglo bi se optimizirat
        // ili ce ic tako ili ce ic dobro pa nece zapisat kako treba
        //printf("zapisanih linija: %d\n", zapisanih_linija);
    }


	/*
    printf("\nPronadjene mreze: \n");
    wlan_print(wlan_list);
	*/
	//printf("idem sortirat\n");
    poslozi(wlan_list);

    //printf("\nPoslozene po jacini signala:\n");
    //wlan_print(wlan_list);
	INFO_END;
}


/*************************************************************************************************
  				wlan_scan()
*************************************************************************************************/
void wlan_scan()
{
	printf("%s() start\n", __func__);
	uart_puts(2, "AT+CWLAP\r\n");	// OH, oh, ne zaboravi \r\n
	printf("%s() end\n", __func__);
}

/*************************************************************************************************
  				wlan_get()
*************************************************************************************************/
wlan_t wlan_get(uint8_t number)
{
	if (strlen(wlan_list[number].SSID) != 0)
	{
		return wlan_list[number];
	}
	else
	{
		wlan_t failed = {"ERROR", "ERROR", -127, "ERROR", 0};
		return failed;
	}
}

/*************************************************************************************************
  				wlan_is_scan_done()
*************************************************************************************************/
bool wlan_is_scan_done()
{
	if (wlan_event == WLAN_SCAN_DONE)
		return 1;
	else
		return 0;
}


uint16_t uart2_rx_position = 0;
/*************************************************************************************************
  				USART2 IRQ
*************************************************************************************************/
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		//uart2_rx_event = RX_IN_PROGRESS;
		wlan_event = WLAN_SCAN_IN_PROGRESS;

		uint16_t rx_char = USART_ReceiveData(USART2);
        {
        	uart2_rx_string_arr[uart2_rx_position++] = rx_char;
        }


		/*
        if (uart2_rx_position >= MAX_WLAN_BUFFER)
        {
            // XXX nikad ne dodje do ovoga, zbog ostalih RX evenata u ISRu
            uart2_rx_event = RX_OVERFLOW;
            uart2_rx_position = 0;
        }
		*/
		// main() provjerava jel dosao do kraja buffera i tamo postavlja ispravni wlan_event
	}
}
