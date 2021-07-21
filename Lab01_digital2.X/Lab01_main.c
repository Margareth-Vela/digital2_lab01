/*
 * Archivo:   Lab01_main.c
 * Dispositivo: PIC16F887
 * Autor: Margareth Vela 
 * 
 * Programa: Interrupciones y librerías
 * Hardware: Leds en PORTA, Display en PORTC, transistores en PORTD, Led y 
 *           Potenciómetro en PORTE, & push buttons en PORTB.
 * 
 * Creado: Julio 19, 2021
 * Última modificación: Julio 21, 2021
 */

//------------------------------------------------------------------------------
//                          Importación de librerías
//------------------------------------------------------------------------------    
 #include <xc.h>
 #include <stdint.h>
 #include "ADC.h"
 #include "Display.h"

//------------------------------------------------------------------------------
//                          Directivas del compilador
//------------------------------------------------------------------------------
#define _XTAL_FREQ 4000000 //Para delay

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
#pragma config LVP = ON         //Low Voltage Programming Enable bit(RB3/PGM pin 
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
uint8_t primer_display = 0; //variables para displays
uint8_t segundo_display = 0;
uint8_t var_temp; 
uint8_t primer_temp = 0;
uint8_t segundo_temp = 0;

//------------------------------------------------------------------------------
//                          Prototipos
//------------------------------------------------------------------------------
void setup(void);  //Configuración

//------------------------------------------------------------------------------
//                          Código Principal
//------------------------------------------------------------------------------
void main(void) {
    setup(); //Configuración
    ADCON0bits.GO = 1; //La conversión ADC se ejecuta
    while(1)
    {
        ADC(); //Se hace la conversión del canal y se obtiene el valor del ADC
        
        PORTEbits.RE0 = 0; //Led de alarma apagado
        primer_temp = var_temp & 0x0F; //Se obtiene el valor para el primer 
        segundo_temp = (var_temp >> 4) & 0x0F; // y segundo display
        primer_display = number(primer_temp); //Se obtiene el valor a desplegar
        segundo_display = number(segundo_temp);
        
        if(var_temp > PORTA){ //Verifica si sobrepasó el valor de referencia
            PORTEbits.RE0 = 1; //Se enciende la alarma
            __delay_ms(40);
        }
        }
    return;
}

//------------------------------------------------------------------------------
//                          Interrupciones
//------------------------------------------------------------------------------
void __interrupt() isr(void){

    if (INTCONbits.T0IF){ //Int TMR0
        PORTD = 0x00;
        if(PORTEbits.RE2 == 0){
            PORTC = primer_display; //Se muestra el valor en hex para el primer display
            PORTDbits.RD0 = 1; //Se enciende el transistor para el primer display
            PORTEbits.RE2 = 1; //Se hace el cambio de display
        }
        else if(PORTEbits.RE2 == 1){
            PORTC = segundo_display; //Se muestra el valor en hex para el segundo display
            PORTDbits.RD1 = 1; //Se enciende el transistor para el segundo display
            PORTEbits.RE2 = 0; //Se hace el cambio de display
        }        
        TMR0 = 235; //Se reinicia el TMR0
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
    if (PIR1bits.ADIF){
        var_temp = ADRESH; //Se obtiene el valor del ADC
        PIR1bits.ADIF = 0; //Se limpia la bandera de ADC
    }
    
    return;
}

//------------------------------------------------------------------------------
//                          Configuración
//------------------------------------------------------------------------------
void setup(){
    
    //Configuracion reloj
    OSCCONbits.IRCF2 = 1; //Frecuencia a 4MHZ
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS = 1;
    
    //Configurar entradas y salidas
    ANSELH = 0x00;//Pines digitales
    ANSEL = 0x40; //Pin analógico para POT
    
    TRISA = 0x00; //Para salida del contador
    TRISB = 0x03; //Para push buttons
    TRISC = 0x00; //Para salida del display
    TRISD = 0x00; //Para transistores
    TRISE = 0x02; //Para led de alarma y potenciometro
               
    //Habilitar pullups
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0x03;
    
    PORTA = 0x00; //Se limpian los puertos
    PORTD = 0x00;
    PORTB = 0x03; //Para condición de mismatch     
    PORTC = 0x00;
    PORTE = 0x00;
    
    //Configurar ADC
    ADCON1bits.ADFM = 0; //Justificar a la izquierda
    ADCON1bits.VCFG0 = 0; //Vss
    ADCON1bits.VCFG1 = 0; //VDD
    
    ADCON0bits.ADCS = 0b10; //ADC oscilador -> Fosc/32
    ADCON0bits.CHS = 6;     //Comenzar en canal 6
    __delay_us(50);        
    ADCON0bits.ADON = 1;    //Habilitar la conversión ADC
    
    //Configurar la interrupcion
    INTCONbits.GIE = 1;  //Enable interrupciones globales
    INTCONbits.T0IE = 1; //Enable TMR0
    INTCONbits.T0IF = 0; //Se limpia la bandera de interrupción TMR0
    INTCONbits.PEIE = 1; //Enable interrupciones periféricas
    PIE1bits.ADIE = 1;   //Enable interrupción ADC
    PIR1bits.ADIF = 0;   //Se limpia bandera de interrupción ADC
    
    
    //Interrupcion PORTB
    INTCONbits.RBIE = 1; //Enable Interrupt on change
    IOCB = 0x03;
    INTCONbits.RBIF = 0; //Se limpia la bandera de Interrupt on change	
   
    //Configurar TMR0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1; //Prescaler 1:256
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    TMR0 = 236;  //Se reinicia el TMR0
    return;
 }  