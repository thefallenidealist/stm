// created 150618
#ifndef SOBA_H
#define SOBA_H

#include "baro.h"
#include "nRF.h"
#include "gpio.h"

void soba_init(void);
void soba_main(void);

void soba_set_svjetlo(bool arg);
bool soba_get_svjetlo(void);
void soba_set_grijac(bool arg);
bool soba_get_grijac(void);
char *soba_get_status(void);
void soba_send_status(void);


#endif // SOBA_H
