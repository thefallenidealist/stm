// created 150618
#ifndef SAKUPLJAC_H
#define SAKUPLJAC_H

#include "nRF.h"
#include <stdint.h>
#include <string.h>		// strncmp()
#include <stdlib.h>		// atoi()

// prototipi
void sakupljac_init(void);
void sakupljac_main(void);
void sakupljac_parse(char *cmd, char *arg);


#endif	// SAKUPLJAC_H
