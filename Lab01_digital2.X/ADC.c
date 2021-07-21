/* 
 * Archivo:   Lab01_main.c
 * Dispositivo: PIC16F887
 * Autor: Margareth Vela 
 */

#include <xc.h>
#include <stdint.h>
#include "ADC.h"

//------------------------------------------------------------------------------
//                          Directivas del compilador
//------------------------------------------------------------------------------
#define _XTAL_FREQ 4000000 //Para delay

void ADC() {
        if(ADCON0bits.GO == 0){ //Si la conversión ya está terminada
            ADCON0bits.CHS = 6;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            ADCON0bits.GO = 1; //Se vuelve a ejecutar la conversión ADC
        }              
    return;
}
