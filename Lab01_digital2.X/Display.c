/* 
 * Archivo:   Lab01_main.c
 * Dispositivo: PIC16F887
 * Autor: Margareth Vela 
 */

#include <xc.h>
#include <stdint.h>
uint8_t tab7seg[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0X79,0X71}; //Tabla

uint8_t number(uint8_t digito){
    uint8_t data = tab7seg[digito];; 
    return data;
}
