// Ovaj modul se bavi samo sa WLAN listama, ne rukuje direktno sa WLAN hardverom
// TODO zamijenit memcpy sa memmove FreeBSDov memcpy dopusta kopiranje stringova koji se preklapaju

#include "wlan_list.h"

wlan_list_t	 wlan_list[WLAN_LIST_MAX]; // polje objekata wlan lista

// globalne varijable
char encription[5][13];

/*
   poslozi listu WLANova po jacini signala, od najveceg, prema najmanjem
   mijenja dobiveni argument
   najlosiji signal je -95, bolji su oni blize 0
*/
static void poslozi(wlan_list_t wlan_list[])
//static void poslozi(char *buffer)
{
	DEBUG_START;

    // bubble sort
    wlan_list_t tmp_copy;
    //bool swapped = false;
    bool swapped;

    do
    {
        swapped = false;
        wlan_list_t *trenutni, *prethodni, *tmp;

		uint8_t i=1;	// da ne dobije array index -1

        // radi sve dok ne naidjes na prazni SSID
        while (strlen(wlan_list[i].SSID))
        {
            trenutni  = &wlan_list[i];
            prethodni = &wlan_list[i-1];
            tmp 	  = &tmp_copy;
			
			/*
			printf("trenutni:  %d\n", i);
			printf("prethodni: %d\n", i-1);
			printf("%s(): i: %d tre strength: %d, prethodni strength: %d\n", __func__, i, trenutni->strength, prethodni->strength);
			*/

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

	DEBUG_END;
}

/*************************************************************************************************
  				wlan_parse()
*************************************************************************************************/
//static void wlan_parse()
static void wlan_parse(char *buffer)
{
	DEBUG_START;

    // razdvoji na redove, delimiter su ()
    char * token;
    while ((token = strsep(&buffer, "()")) != NULL)
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
					//printf("atribute: %d) wlan_number: %d encription: %d\n", wlan_atribute_counter, wlan_number+1, atoi(token2));
                    wlan_list[wlan_number].encription = encription[atoi(token2)];
                }
                else if (wlan_atribute_counter == 1)
                {
                    // TODO maknit ""
					//printf("atribute: %d) wlan_number: %d SSID: %s\n", wlan_atribute_counter, wlan_number+1, token2);
                    strncpy(wlan_list[wlan_number].SSID, token2, sizeof(wlan_list[wlan_number].SSID));
                }
                else if (wlan_atribute_counter == 2)
                {
                    //wlan_list[wlan_number].strength = atoi(token2);	// XXX ovdje zaglavi na ARMu, na PCu radi kako treba
								// zaglavi negdje u _strtol_r() (newlib atoi() je implementiran kao strtol())
								// token2 ima \0 na kraju, dug je 3(strlen) 4(sizeof)
								// clang 3.6, newlib iz "gcc version 4.8.4 20140725 (release)"

					int8_t strength = atoi(&token2[1]);	// samo pozitivni dio, da se atoi ne zaglavi

					//printf("atribute: %d) wlan_number: %d strength: %d\n", wlan_atribute_counter, wlan_number+1, strength);

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

					//printf("atribute: %d) wlan_number: %d BSSID: %s\n", wlan_atribute_counter, wlan_number+1, token2);
                    strncpy(wlan_list[wlan_number].BSSID, token2, sizeof(wlan_list[wlan_number].BSSID));
                }
                else if (wlan_atribute_counter == 4)
                {
					//printf("atribute: %d) wlan_number: %d ch: %d\n", wlan_atribute_counter, wlan_number+1, atoi(token2));
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

    poslozi(wlan_list);

	DEBUG_END;
}


/*************************************************************************************************
  				wlan_get_list()
*************************************************************************************************/
// vrati N-tu mrezu iz globalnog polja popisa WLANova
// vrati ERROR ako na N-tom mjestu nema mreze
wlan_list_t wlan_get_list(uint8_t number)
{
	// TODO presaltat na pointere i da vrati NULL
	DEBUG_START; 

	if (strlen(wlan_list[number].SSID) != 0)
	{
		DEBUG_END;
		return wlan_list[number];
	}
	else
	{
		wlan_list_t failed = {"ERROR", "ERROR", -127, "ERROR", 0};
		//wlan_list_t failed = {NULL, NULL, -127, NULL, 0};	// nop, zajeb
		DEBUG_END;
		return failed;
	}

	DEBUG_END;
}

/*************************************************************************************************
  				wlan_print()
*************************************************************************************************/
//void wlan_print()
//void wlan_print(wlan_modul_t *wlan0)
int8_t wlan_print(wlan_modul_t *wlan0)
{
	DEBUG_START;

	if (wlan0 == NULL)
	{
		ERROR("dobili smo NULL objekt, izlazim\n");
		return -1;
	}

	//printf("%s(): %s\n", __func__, wlan0->buffer);

	//if (wlan0->scan_done(wlan0))
	if (wlan0->scan_done(wlan0) && (wlan0->event != WLAN_SCAN_PRINTED) )
	{
		wlan_parse(wlan0->buffer);
		//poslozi(wlan0->buffer);

		printf("WLAN:\n");
		//glcd_string("                    ", 0, 40, 2, red);	// obrisi "skeniranje u tijeku"

		for (uint8_t i=0; i<WLAN_LIST; i++)	// ispisat samo N najjacih mreza
		//for (uint8_t i=0; i<5; i++)
		{
			wlan_list_t wlan_list0 = wlan_get_list(i);

			if (strncmp(wlan_list0.SSID, "ERROR", sizeof(wlan_list0.SSID)) != 0)	// nemoj ispisat ako nema WLANa
			{
				//printf("%d) %s \t strength: %d \t %s\n", i+1, wlan.SSID, wlan.strength, wlan.BSSID);
				printf("%d) signal: %d %s enc: %s\n", i+1, wlan_list0.strength, wlan_list0.SSID, wlan_list0.encription);

				// zapisi i na GLCD
				//glcd_string("                ", 0, i+40, 2, glcd_get_bgcolor());	// obrisi ispod
				//glcd_string(wlan.SSID, 20, 40+(i*20), 2, white);	// 40 jer je gore WLAN size 4, 20 pixela za svaki iduci velicine 2
				//glcd_number(wlan.strength, 0, 40+(i*20), 2, cyan);
			}
		}
		wlan0->event = WLAN_SCAN_PRINTED;
	}
	else
	{
		DEBUG_INFO("WLAN skeniranje jos nije gotovo\n");
	}

	return 0;

	DEBUG_END;
}

void wlan_list_init()
{
	DEBUG_START; 

    strcpy(encription[0], "OPEN");
    strcpy(encription[1], "WEP");
    strcpy(encription[2], "WPA_PSK");
    strcpy(encription[3], "WPA2_PSK");
    strcpy(encription[4], "WPA_WPA2_PSK");

	DEBUG_END;
}
