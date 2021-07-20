/* 
 * Archivo:   Lab01_main.c
 * Dispositivo: PIC16F887
 * Autor: Margareth Vela 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __Display_H_
#define	__Display_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

uint8_t number(uint8_t digito);

#endif	/* XC_HEADER_TEMPLATE_H */