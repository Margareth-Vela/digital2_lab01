/* 
 * Archivo:   Lab01_main.c
 * Dispositivo: PIC16F887
 * Autor: Margareth Vela 
 */

#include <xc.h>
#include "ADC.h"

//------------------------------------------------------------------------------
//                          Directivas del compilador
//------------------------------------------------------------------------------
#define _XTAL_FREQ 8000000 //Para delay

void ADC(uint8_t channel) {
    switch (channel){
        case 0:
            ADCON0bits.CHS = 0;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 1:
            ADCON0bits.CHS = 1;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 2:
            ADCON0bits.CHS = 2;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 3:
            ADCON0bits.CHS = 3;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 4:
            ADCON0bits.CHS = 4;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 5:
            ADCON0bits.CHS = 5;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 6:
            ADCON0bits.CHS = 6;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 7:
            ADCON0bits.CHS = 7;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 8:
            ADCON0bits.CHS = 8;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 9:
            ADCON0bits.CHS = 9;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 10:
            ADCON0bits.CHS = 10;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 11:
            ADCON0bits.CHS = 11;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        case 12:
            ADCON0bits.CHS = 12;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;
        default:
            ADCON0bits.CHS = 13;  //pasa al segundo canal            
            __delay_us(50); //Delay para el capacitor sample/hold
            break;       
    } 
    return;
}
