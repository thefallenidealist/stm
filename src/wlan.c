#include "wlan.h"
// 3.3V, CH_PD ide u Vcc

#include <string.h>
#include <stdlib.h>     // atoi
#include <stdbool.h>
// TODO zamijenit memcpy sa memmove FreeBSDov memcpy dopusta kopiranje stringova koji se preklapaju
#include "glcd.h"

#define BUFFER_SIZE 68	// koliko ce maksimalno bit dugacak string za jednu mrezu (enc+SSID+strength+BSSID+channel)
						// 13 + 33 + 1 + 20 + 1 = 68

// globalni objekti
//wlan_hw_t wlan_hw;
wlan_hw_t	 wlan_modul1;
wlan_list_t	 wlan_list[MAX_WLAN]; // polje objekata
wlan_event_t wlan_event = WLAN_SCAN_NOT_STARTED;	// TODO ubacit u objekt, da ih moze bit vise

// globalne varijable
char *pbuffer = (char *)uart2_rx_string_arr;
char encription[5][13];

/*
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
*/

/*
   poslozi listu WLANova po jacini signala, od najveceg, prema najmanjem
   mijenja dobiveni argument
   najlosiji signal je -95, bolji su oni blize 0
*/
static void poslozi(wlan_list_t wlan_list[])
{
	INFO_START;

    // bubble sort
    wlan_list_t tmp_copy;
    bool swapped = false;

    do
    {
        swapped = false;
        wlan_list_t *trenutni, *prethodni, *tmp;

        uint8_t i=0;

        // radi sve dok ne naidjes na prazni SSID
        while (strlen(wlan_list[i].SSID))
        {
            trenutni  = &wlan_list[i];
            prethodni = &wlan_list[i-1];
            tmp 	  = &tmp_copy;

            if (prethodni->strength < trenutni->strength)
            {
                // zamijeni
                //printf("mijenjam mjesta za pozicije: %d %d\n", i, i-1);
                memcpy(tmp,			prethodni,	sizeof(*tmp));   	 // prethodni ide u tmp
                memcpy(prethodni,	trenutni,	sizeof(*prethodni)); // trenutni ide u prethodni
                memcpy(trenutni,	tmp, 		sizeof(*trenutni));  // tmp ide u prethodni
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

	// wlan_hw objekt je vec kreiran 
	wlan_modul1.uart_number = WLAN_UART_NUMBER;
	wlan_modul1.uart_speed  = WLAN_UART_SPEED;

	//printf("UART number: %d\n", WLAN_UART_NUMBER);
	//printf("UART speed: %d\n", WLAN_UART_SPEED);

	//printf("%s(): pozivam uart%d_init(%d)\n", __func__, wlan_hw.uart_number, wlan_hw.uart_speed);
	uart_init(wlan_modul1.uart_number, wlan_modul1.uart_speed);

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

                if (wlan_atribute_counter == 0)
                {
                    wlan_list[wlan_number].encription = encription[atoi(token2)];
                }
                else if (wlan_atribute_counter == 1)
                {
					/*
                    // TODO maknit ""
					char *token3;
    				while ((token3 = strsep(&token2, "\"\"")) != NULL)	// maknimo ""
					{
						//printf("\t\t\t\ttoken3: %s\n", token3);
					}
                    strncpy(wlan_list[wlan_number].SSID, token3, sizeof(wlan_list[wlan_number].SSID));
					*/

                    strncpy(wlan_list[wlan_number].SSID, token2, sizeof(wlan_list[wlan_number].SSID));
                }
                else if (wlan_atribute_counter == 2)
                {
                    //wlan_list[wlan_number].strength = atoi(token2);	// XXX ovdje zaglavi na ARMu, na PCu radi kako treba
								// zaglavi negdje u _strtol_r() (newlib atoi() je implementiran kao strtol())
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
                    // TODO maknit ""

					/*
					char *token3;
					//printf("pbuffer prije token3: %s\n", pbuffer);
					//printf("token2 prije token3: %s\n", token2);
					
    				while ((token3 = strsep(&token2, "\"\"")) != NULL)	// maknimo ""
					{
						//printf("\t\t\t\ttoken3: %s\n", token3);
					}
                    strncpy(wlan_list[wlan_number].BSSID, token3, sizeof(wlan_list[wlan_number].BSSID));
					*/

                    strncpy(wlan_list[wlan_number].BSSID, token2, sizeof(wlan_list[wlan_number].BSSID));
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
	INFO_START;

	uart_puts(2, "AT+CWLAP\r\n");	// OH, oh, ne zaboravi \r\n
	wlan_event = WLAN_SCAN_IN_PROGRESS;

	INFO_END;
}

/*************************************************************************************************
  				wlan_get_list()
*************************************************************************************************/
// vrati N-tu mrezu iz globalnog polja popisa WLANova
// vrati ERROR ako na N-tom mjestu nema mreze
wlan_list_t wlan_get_list(uint8_t number)
{
	if (strlen(wlan_list[number].SSID) != 0)
	{
		return wlan_list[number];
	}
	else
	{
		wlan_list_t failed = {"ERROR", "ERROR", -127, "ERROR", 0};
		return failed;
	}
}

/*************************************************************************************************
  				wlan_is_scan_done()
*************************************************************************************************/
bool wlan_is_scan_done()
{
	//if ( (strstr((char *)uart2_rx_string_arr, "OK") != 0) && (wlan_event == WLAN_SCAN_IN_PROGRESS) )
	if (strstr((char *)uart2_rx_string_arr, "OK"))
	{
		wlan_event = WLAN_SCAN_DONE;
		printf("%s(): WLAN scan done\n", __func__);
		return 1;
	}
	else if (wlan_event == WLAN_SCAN_IN_PROGRESS)
	{
		printf("skeniranje u tijeku\n");
		//glcd_string("WLAN:", 0, 0, 4, white);
		//glcd_string("skeniranje u tijeku", 0, 40, 2, red);
		return 0;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************************************
  				wlan_print()
*************************************************************************************************/
void wlan_print()
{
	//if (wlan_event == WLAN_SCAN_DONE)
	if (wlan_is_scan_done())
	{
		wlan_parse();

		printf("WLAN:\n");
		//glcd_string("                    ", 0, 40, 2, red);	// obrisi "skeniranje u tijeku"

		for (uint8_t i=0; i<10; i++)	// ispisat samo N najjacih mreza
		{
			//wlan_t wlan = wlan_get(i);
			wlan_list_t wlan = wlan_get_list(i);

			if (strncmp(wlan.SSID, "ERROR", sizeof(wlan.SSID)) != 0)	// nemoj ispisat ako nema WLANa
			{
				printf("%s \t strength: %d\n", wlan.SSID, wlan.strength);

				// zapisi i na GLCD
				//glcd_string("                ", 0, i+40, 2, glcd_get_bgcolor());	// obrisi ispod
				//glcd_string(wlan.SSID, 20, 40+(i*20), 2, white);	// 40 jer je gore WLAN size 4, 20 pixela za svaki iduci velicine 2
				//glcd_number(wlan.strength, 0, 40+(i*20), 2, cyan);
			}
		}
		wlan_event = WLAN_PRINTED;
	}
}
