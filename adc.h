/*
 * \archivo:		adc.h
 * \version: 		1.0
 * 
 * \descripcion:	Este fichero contiene libreria para manejo del ADC
 * 
 * \autor:			Gary Servin 
 * \web:			www.garyservin.wordpress.com
 * \fecha:			07/10/12			
 */

#ifndef ADC_H
#define ADC_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#include <xc.h>		// Incluimos la libreria para definicion de Registros y configuraciones
#include "GenericTypeDefs.h"

#define IniciarSensores()	OpenADC()
#define LeerSensor(a)		ReadADC(a)
#define read_a2d(a)		ReadADC(a)

void OpenADC ( void );
UINT16_VAL ReadADC ( char channel );
#endif
