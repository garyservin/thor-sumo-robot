/*
 * \archivo:		adc.c
 * \version: 		1.0
 * 
 * \descripcion:	Este fichero contiene libreria para manejo del ADC
 * 
 * \autor:			Gary Servin 
 * \web:			www.garyservin.wordpress.com
 * \fecha:			07/10/12			
 */

#include "adc.h"

void OpenADC ( void )
{
	// 1. Configurar Puertos
	// 1.1. Deshabilitamos el driver de salida de los pines
	// TRISA |= 0x2F; // Todos los pines del puerto A como entradas
	// TRISE |= 0x03; // Todos los pines del puerto E como entradas
	// 1.2. Configuramos los pines como analógicos
	// ANSELA |= 0x2F; // Todos los pines del puerto A como analógicos
	// ANSELE |= 0x03; // Todos los pines del puerto E como analógicos

	// 2. Configurar el modulo ADC
	// 2.0. Seleccionamos el formato del resultado
	ADCON1bits.ADFM = 1; // Justificación a la derecha.
	// 2.1. Select ADC conversion clock
	ADCON1bits.ADCS = 0b101; // Seleccionamos Fosc/32
	// 2.2. Configure voltage reference
	ADCON1bits.ADNREF = 0; // Referencia Negativa a VSS
	ADCON1bits.ADPREF = 0; // Referencia Positiva a VDD
	// 2.3. Select ADC input channel
	ADCON0bits.CHS = 0; // Seleccionamos el canal 0
	// 2.4. Turn on ADC module
	ADCON0bits.ADON = 1; // Encendemos el módulo

	/* No utilizado
	// 3. Configurar interrupciones por ADC (Opcional)
	// 3.1. Clear ADC interrupt flag
	// 3.2. Enable ADC interrupt
	// 3.3. Enable peripheral interrupt
	// 3.4. Enable global interrupt(1)*/
}

UINT16_VAL ReadADC ( char channel )
{
	UINT16_VAL result;
	result.Val = 0;
	// 2.3. Select ADC input channel
	ADCON0bits.CHS = channel & 0x07; // Seleccionamos el canal
	// 4. Esperar el tiempo de adquisición requerido
	__delay_us(10);

	// 5. Empezar la conversion seteando el bit GO/DONE
	ADCON0bits.GO = 1; // Iniciamos la conversión

	// 6. Esperar a que se complete la conversion
	// 6.1. Polling the GO/DONE bit
	while ( !ADCON0bits.nDONE ) continue; // Mientras no este completa
	// 6.2. Waiting for the ADC interrupt (interrupts enabled)
	// No utilizado

	// 7. Leemos el resultado
	result.HB = ADRESH;
	result.LB = ADRESL;
	return result;

	// 8. Limpiamos el flag de interrupcion (Opcional)
}
