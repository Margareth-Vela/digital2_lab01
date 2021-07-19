/*
 * Archivo:   Lab09.c
 * Dispositivo: PIC16F887
 * Autor: Margareth Vela 
 * 
 * Programa: Interrupciones y librerías
 * Hardware:
 * 
 * Creado: Julio 19, 2021
 * Última modificación: Julio, 2021
 */

//------------------------------------------------------------------------------
//                          Importación de librerías
//------------------------------------------------------------------------------    
 #include <xc.h>
 #include <stdint.h>

//------------------------------------------------------------------------------
//                          Palabras de configuración
//------------------------------------------------------------------------------    
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT//Oscillator Selection bits(INTOSCIO 
                              //oscillator: I/O function on RA6/OSC2/CLKOUT pin, 
                              //I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled and 
                          //can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR  
                                //pin function is digital input, MCLR internally 
                                //tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
                                //protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
                                //protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit 
                                //Internal/External Switchover mode is disabled
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
                                //(Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF         //Low Voltage Programming Enable bit(RB3/PGM pin 
                                //has PGM function, low voltage programming 
                                //enabled)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out 
                                //Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
                                //(Write protection off)

//------------------------------------------------------------------------------
//                          Variables
//------------------------------------------------------------------------------
uint8_t unidad_display = 0; //variables para displays
uint8_t decena_display = 0;

//------------------------------------------------------------------------------
//                          Código Principal
//------------------------------------------------------------------------------
void main(void) {
    return;
}

//------------------------------------------------------------------------------
//                          Interrupciones
//------------------------------------------------------------------------------
void __interrupt() isr(void){

    if (INTCONbits.T0IF){ //Int TMR0
        if(PORTD == 2){
            PORTC = unidad_display; //Se muestra el valor de unidades
            PORTDbits.RD0 = 1; //Se enciende el transistor con el display de unidades
            PORTDbits.RD1 = 0; //Se enciende el transistor con el display de unidades
        }
        else {
            PORTC = decena_display; //Se muestra el valor de decenas
            PORTDbits.RD1 = 1; //Se enciende el transistor con el display de decenas
            PORTDbits.RD0 = 0; //Se enciende el transistor con el display de unidades
        }        
        TMR0 = 236; //Se reinicia el TMR0
        INTCONbits.T0IF = 0; //Se limpia la bandera
    }
    if(INTCONbits.RBIF){
        if (PORTBbits.RB0 == 0){ //Si el botón de incremento está presionado,
            PORTA++; //se incrementa PORTA
        }
        if(PORTBbits.RB1 == 0) {//Si el botón de decremento está presionado,
            PORTA--; //se decrementa PORTA
        }

        INTCONbits.RBIF = 0; //Se limpia la bandera
    }
    return;
}