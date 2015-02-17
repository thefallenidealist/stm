// Ovaj modul se bavi samo sa WLAN listama, ne rukuje direktno sa WLAN hardverom
// TODO zamijenit memcpy sa memmove FreeBSDov memcpy dopusta kopiranje stringova koji se preklapaju

#include "wlan_list.h"
#include "glcd.h"

// globalne varijable
char encription[5][13];
wlan_list_t	 wlan_list[WLAN_LIST_MAX]; // polje objekata wlan lista
uint8_t wlan_number = 0;	// globalna, da se moze resetirat izmedju 2 skeniranja

uint8_t glcd_clean = 0;

/*************************************************************************************************
  				poslozi()
*************************************************************************************************/
/*
   poslozi listu WLANova po jacini signala, od najveceg, prema najmanjem
   mijenja dobiveni argument
   najlosiji signal je -95, bolji su oni blize 0
*/
static void poslozi(wlan_list_t wlan_list[])
{
	DEBUG_START;

    // bubble sort
    wlan_list_t tmp_copy;
    bool swapped = false;

    do
    {
        swapped = false;
        wlan_list_t *trenutni, *prethodni, *tmp;

		uint8_t i = 1;	// da ne dobije array index -1

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
  				parse()
*************************************************************************************************/
//static void parse(char *buffer)
static int8_t parse(char *buffer)
{
	DEBUG_START;

	if (buffer == NULL)
	{
		ERROR("dobili smo NULL objekt, izlazim\n");
		return -1;
	}

    // razdvoji na redove, delimiter su ()
    char * token;
    while ((token = strsep(&buffer, "()")) != NULL)
    {
        //printf("token: %s\n", token);

        //static uint8_t wlan_number = 0;	// prebaceno u globalnu varijablu

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
					strength = (100-strength)/10 + 1;
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
	return 0;
}

/*************************************************************************************************
  				restart
*************************************************************************************************/
// vrati UART buffer i wlan_list_t listu na pocetak, da bude spremno za ponovno skeniranje
//void restart(wlan_modul_t *wlan0)
static int8_t restart(wlan_modul_t *wlan0)
{
	if (wlan0 == NULL)
	{
		ERROR("dobili smo NULL objekt, izlazim\n");
		return -1;
	}

	//printf("\t\t\t\t%s(): cistim nakon printanja\n", __func__);
	wlan0->event = WLAN_SCAN_PRINTED;

	uart2_rx_position = 0;	// TODO ovo bi moglo bit per object
	wlan_number = 0;	// kreni od pocetka zapisivat u wlan_list_t
	glcd_clean = 0;

	// obrisi UART buffer
	for (uint16_t i=0; i<MAX_WLAN_BUFFER; i++)	
	{
		wlan0->buffer[i] = '\0';
	}

#ifdef GLCD_H
	glcd_bg(glcd_get_bgcolor());
#endif

	return 0;
}

/*************************************************************************************************
  				public functions
*************************************************************************************************/
/*************************************************************************************************
  				wlan_list_get()
*************************************************************************************************/
// vrati N-tu mrezu iz globalnog polja popisa WLANova
// vrati ERROR ako na N-tom mjestu nema mreze
wlan_list_t wlan_list_get(uint8_t number)
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
}

/*************************************************************************************************
  				wlan_list_print()
*************************************************************************************************/
// ovaj je zapravo samo kopirano iz main()
int8_t wlan_list_print(wlan_modul_t *wlan0)
{
	if (wlan0 == NULL)
	{
		ERROR("dobili smo NULL objekt, izlazim\n");
		return -1;
	}

	memset(wlan_list, 0, sizeof(wlan_list));	// ako se stavi u restart() ne radi

	int8_t ret = wlan_list_ready(wlan0);

	if (ret)	// ret je broj pronadjenih WLANova
	{
		restart(wlan0);	// mora bit ispred printanja, da ostanu rezultati vidilji sve dok ne dodju novi

		// isprintat
		printf("WLAN:\n");
#ifdef GLCD_H
		glcd_string("WLAN", 0, 0, 4, red);
#endif

		for (uint8_t i=0; i<ret; i++)	// ispisat ce samo onoliko mreza koliko je pronadjeno (ret)
		{
			wlan_list_t wlan_list0 = wlan_list_get(i);

			if (strncmp(wlan_list0.SSID, "ERROR", sizeof(wlan_list0.SSID)) != 0)	// nemoj ispisat ako nema WLANa
			{
				printf("%d) signal: %d %s enc: %s\n", i+1, wlan_list0.strength, wlan_list0.SSID, wlan_list0.encription);
			}

#ifdef GLCD_H
			if (i == 0)
			{
				glcd_clear_line(0, 40, 2);	// obrisi liniju gdje je pisalo da skeniranje jos traje
			}
			glcd_string(wlan_list0.SSID, 20, 40+(i*20), 2, white);	// 40 jer je gore WLAN size 4, 20 pixela za svaki iduci velicine 2
			glcd_number(wlan_list0.strength, 0, 40+(i*20), 2, cyan);
#endif
		}

		//restart(wlan0);

		return 0;
	}
	else if (wlan0->event == WLAN_SCAN_IN_PROGRESS)
	{
		//printf("%s(): WLAN skeniranje jos traje\n", __func__);
		printf("skeniranje jos traje\n");
#ifdef GLCD_H
		if (glcd_clean == 0)
		{
			glcd_bg(glcd_get_bgcolor());
		}
		glcd_string("WLAN", 0, 0, 4, red);
		glcd_string("Skeniranje jos traje", 0, 40, 2, red);
		glcd_clean = 1;
#endif
		return 0;
	}

	return 0;
}

/*************************************************************************************************
  				wlan_list_ready()
*************************************************************************************************/
// slicno print funkciji, ali ovo preko returna javi jel spremno printat i koliko ih ima za isprintat
int8_t wlan_list_ready(wlan_modul_t *wlan0)
{
	DEBUG_START;
	uint8_t counter = 0;

	if (wlan0 == NULL)
	{
		ERROR("dobili smo NULL objekt, izlazim\n");
		return -1;
	}

	if (wlan0->scan_done(wlan0) && (wlan0->event != WLAN_SCAN_PRINTED) )	// ako je gotovo skeniranje i nije jos isprintano
	{
		parse(wlan0->buffer);	// iz 1D stringa napravi listu tipa wlan_list_t i poslozi ju (poslozi())

		for (uint8_t i=0; i<WLAN_LIST; i++)		// pronadji koliko smo WLANova nasli
		{
			wlan_list_t wlan_list0 = wlan_list_get(i);

			if (strncmp(wlan_list0.SSID, "ERROR", sizeof(wlan_list0.SSID)) != 0)	// nemoj uracunat ako nema WLANa
			{
				counter++;
			}
		}

		return counter;
	}
	else
	{
		DEBUG_INFO("WLAN skeniranje jos nije gotovo\n");
		return 0;
	}

	return 0;

	DEBUG_END;
}

/*************************************************************************************************
  				wlan_list_init()
*************************************************************************************************/
void wlan_list_init()
{
	DEBUG_START; 

	/*
    strcpy(encription[0], "OPEN");
    strcpy(encription[1], "WEP");
    strcpy(encription[2], "WPA_PSK");
    strcpy(encription[3], "WPA2_PSK");
    strcpy(encription[4], "WPA_WPA2_PSK");
	*/
    strncpy(encription[0], "OPEN", 			sizeof(encription[0]));
    strncpy(encription[1], "WEP", 			sizeof(encription[1]));
    strncpy(encription[2], "WPA_PSK", 		sizeof(encription[2]));
    strncpy(encription[3], "WPA2_PSK", 		sizeof(encription[3]));
    strncpy(encription[4], "WPA_WPA2_PSK", 	sizeof(encription[4]));

	DEBUG_END;
}
