#ifndef THOR_H
#define THOR_H

#define __16F1937
#define _XTAL_FREQ	16000000UL

//#define DEBUG
//#define MEASURE_TIME

#define BAUD 9600
#define BAUD_GEN ((int)(_XTAL_FREQ/(4UL * BAUD) - 1))

#include <xc.h>
#include <stdio.h>
#if defined __16F1937
#include "usart.h"
#include "adc.h"
#include "GenericTypeDefs.h"
#elif defined __18F4550
#include <plib.h>
#include <delays.h>
#endif

#if defined __18F4550
// CONFIG1L @ 0x300000
#pragma config CPUDIV = OSC1_PLL2	// CPU System Clock Selection bits
#pragma config PLLDIV = 1		// PLL Prescaler Selection bits
#pragma config USBDIV = 1		// USB Clock Selection bit
// CONFIG1H @ 0x300001
#pragma config IESO = OFF		// Internal/External Oscillator Switchover bit
#pragma config FOSC = HS		// Oscillator Selection bits
#pragma config FCMEN = OFF		// Fail-Safe Clock Monitor Enable
// CONFIG2L @ 0x300002
#pragma config VREGEN = OFF		// USB Voltage Regulator Enable bit
#pragma config BOR = OFF		// Brown-out Reset Enable bits
#pragma config BORV = 0			// Brown-out Reset Voltage bits
#pragma config PWRT = OFF		// Power-up Timer Enable bit
// CONFIG2H @ 0x300003
#pragma config WDTPS = 32768		// Watchdog Timer Postscale Select bits
#pragma config WDT = OFF		// Watchdog Timer Enable bit
// CONFIG3H @ 0x300005
#pragma config CCP2MX = OFF		// CCP2 MUX bit
#pragma config PBADEN = OFF		// PORTB A/D Enable bit
#pragma config LPT1OSC = OFF		// Low-Power Timer 1 Oscillator Enable bit
#pragma config MCLRE = ON		// MCLR Pin Enable bit
// CONFIG4L @ 0x300006
#pragma config DEBUG = OFF		// Background Debugger Enable bit
#pragma config STVREN = ON		// Stack Full/Underflow Reset Enable bit
#pragma config ICPRT = OFF		// Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit
#pragma config XINST = OFF		// Extended Instruction Set Enable bit
#pragma config LVP = OFF		// Single-Supply ICSP Enable bit
// CONFIG5L @ 0x300008
#pragma config CP0 = OFF		// Code Protection bit
#pragma config CP1 = OFF		// Code Protection bit
#pragma config CP2 = OFF		// Code Protection bit
#pragma config CP3 = OFF		// Code Protection bit
// CONFIG5H @ 0x300009
#pragma config CPD = OFF		// Data EEPROM Code Protection bit
#pragma config CPB = OFF		// Boot Block Code Protection bit
// CONFIG6L @ 0x30000A
#pragma config WRT0 = OFF		// Table Write Protection bit
#pragma config WRT1 = OFF		// Table Write Protection bit
#pragma config WRT2 = OFF		// Table Write Protection bit
#pragma config WRT3 = OFF		// Table Write Protection bit
// CONFIG6H @ 0x30000B
#pragma config WRTB = OFF		// Boot Block Write Protection bit
#pragma config WRTC = OFF		// Configuration Register Write Protection bit
#pragma config WRTD = OFF		// Data EEPROM Write Protection bit
// CONFIG7L @ 0x30000C
#pragma config EBTR0 = OFF		// Table Read Protection bit
#pragma config EBTR1 = OFF		// Table Read Protection bit
#pragma config EBTR2 = OFF		// Table Read Protection bit
#pragma config EBTR3 = OFF		// Table Read Protection bit
// CONFIG7H @ 0x30000D
#pragma config EBTRB = OFF		// Boot Block Table Read Protection bit
#elif defined __16F1937
//__CONFIG ( FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF );
//__CONFIG ( WRT_OFF & VCAPEN_OFF & PLLEN_OFF & STVREN_OFF & DEBUG_OFF & LVP_OFF );

// CONFIG1
#pragma config FOSC = INTOSC	// Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF	// Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF	// Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON	// MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF		// Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF	// Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF	// Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF	// Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF	// Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF	// Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF	// Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF	// Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF	// PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF	// Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO	// Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF	// Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
#endif

#define string		const MEM_MODEL rom char*

// MOTORS
#define ML_IN1		LATDbits.LATD0
#define ML_IN2		LATDbits.LATD1
#define ML_IN1_TRIS	TRISDbits.TRISD0
#define ML_IN2_TRIS	TRISDbits.TRISD1

#define MR_IN1		LATDbits.LATD3
#define MR_IN2		LATDbits.LATD2
#define MR_IN1_TRIS	TRISDbits.TRISD3
#define MR_IN2_TRIS	TRISDbits.TRISD2

#define M_ENB		LATCbits.LATC2
#define M_ENB_TRIS	TRISCbits.TRISC2

// LINE SENSORS
#define FL_LINE		1
#define FR_LINE		9
#define BL_LINE		2
#define BR_LINE		8

//#define BATTERY		2

// LEDS
//#define mInitAllLEDs()		LATC &= 0xF8; TRISC &= 0xF8; LATD &= 0xF0; TRISD &= 0xF0;
#define mInitUARTLEDs()	LATC |= 0xC0; TRISC &= 0x3F;

#define LED_TX		LATCbits.LATC6
#define LED_RX		LATCbits.LATC7

#define LED_TX_TRIS	TRISCbits.TRISC6
#define LED_RX_TRIS	TRISCbits.TRISC7

// BUTTONS
#define START		PORTDbits.RD4
#define START_TRIS	TRISDbits.TRISD4
#define START_ANSEL	ANSELDbits.ANSD4
#define DIR_SPIN	PORTDbits.RD5
#define DIR_SPIN_TRIS	TRISDbits.TRISD5
#define DIR_SPIN_ANSEL	ANSELDbits.ANSD5
//#define ENABLE		PORTDbits.RD5
//#define ENABLE_TRIS	TRISDbits.TRISD5

// DIRECTIONS
#define	FORWARD		'f'
#define	BACKWARD	'b'
#define	LEFT		'l'
#define	RIGHT		'r'
#define	STOP		's'

#define OL_SENSOR	0
#define OR_SENSOR	1
#define FL_SENSOR	2
#define FR_SENSOR	3
#define BL_SENSOR	4
#define BR_SENSOR	5
#define DISCHARGE	6

#define OL_TRIS		TRISAbits.TRISA0
#define OR_TRIS		TRISAbits.TRISA1
#define FL_TRIS		TRISAbits.TRISA2
#define BL_TRIS		TRISAbits.TRISA3
#define FR_TRIS		TRISAbits.TRISA5
#define BR_TRIS		TRISEbits.TRISE0
#define DS_TRIS		TRISEbits.TRISE1

#define OL_ANSEL	ANSELAbits.ANSA0
#define OR_ANSEL	ANSELAbits.ANSA1
#define FL_ANSEL	ANSELAbits.ANSA2
#define BL_ANSEL	ANSELAbits.ANSA3
#define FR_ANSEL	ANSELAbits.ANSA5
#define BR_ANSEL	ANSELEbits.ANSE0
#define DS_ANSEL	ANSELEbits.ANSE1


// Modes for the State Machine
#define SURVIVE		0
#define HUNT		1
#define TARGET		2
#define ATTACK		3

//#define TEST_LINE_SENSORS
//#define TEST_OPPONENT
//#define CALIBRATE

#define FALSE		0
#define TRUE		1

volatile struct
{
	unsigned atFrontLeftEdge : 1;
	unsigned atFrontRightEdge : 1;
	unsigned atBackLeftEdge : 1;
	unsigned atBackRightEdge : 1;
	unsigned state : 2;
	unsigned first_time : 1;
	unsigned searchClockwise : 1;
} Sumo = {0, 0, 0, 0, 0, 1, 1};

int mEdgeFrontLeftThreshold = 512;
int mEdgeFrontRightThreshold = 512;
int mEdgeBackLeftThreshold = 512;
int mEdgeBackRightThreshold = 512;
int mTargetThreshold = 50;
int mAttackThreshold = 50;
int rangeDifference;
int rangeAverage;

char i;
bit isDebug = FALSE;

#if defined MEASURE_TIME
volatile int test = 0;
UINT16_VAL contador;
char str[8];
float resultado = 0.0;
#endif

void init_sumo ( void );
void sumo_move ( char direction );
void get_sensors ( void );

#if defined __18F4550
void wait_5s ( void );
int read_a2d ( char channel );

#elif defined __16F1937
void delay_ms ( UINT16 miliseconds );
void delay_s ( UINT16 seconds );
#endif

#endif
