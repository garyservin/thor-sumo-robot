#include "thor.h"

void main ( void )
{
	init_sumo();

	#ifdef MEASURE_TIME
	test = 0;
	T1CONbits.TMR1CS = 0; // Timer1 Clock Sourceis instruction clock
	T1CONbits.T1CKPS = 0; // 1:8 Prescaler value
	T1CONbits.nT1SYNC = 1; // Disable Sync
	PIE1bits.TMR1IE = 1;
	PIR1bits.TMR1IF = 0;
	contador.Val = 0;
	TMR1H = TMR1L = 0x00;
	T1CONbits.TMR1ON = 1; //Turn on Timer1 Module
	#else

	if ( !isDebug )
	{
		for ( i = 0; i < 4; i++ )
		{
			LED_TX = !DIR_SPIN;
			LED_RX = DIR_SPIN;
			delay_ms(100);
			LED_TX = LED_RX = 1;
			delay_ms(100);
		}
		LED_TX = !DIR_SPIN;
		LED_RX = DIR_SPIN;
	}
	while ( !START );
	#endif

	delay_s(5); // wait_5s();

	#ifdef MEASURE_TIME
	contador.HB = TMR1H;
	contador.LB = TMR1L;
	resultado = ((float) test * 65535.0 + (float) contador.Val) * (4.0 / 16000000.0);
	printf("Tiempo de inicio Sumo ->(0xFFFF x %u segundos) + %u * TCY = %f\r\n", test, contador.Val, resultado);
	#endif

	for (;; )
	{
		get_sensors(); // Sensor sampling code

		if ( !isDebug )
		{
			if ( Sumo.atFrontLeftEdge || Sumo.atFrontRightEdge || Sumo.atBackLeftEdge || Sumo.atBackRightEdge )
				Sumo.state = SURVIVE;
			switch ( Sumo.state )
			{
				case SURVIVE:
					if ( Sumo.atFrontLeftEdge && Sumo.atFrontRightEdge )
					{
						sumo_move(BACKWARD);
						delay_ms(300); //delay_ms(300);//Delay10KTCYx(125);
						Sumo.searchClockwise = TRUE;
					}
					else if ( Sumo.atFrontLeftEdge )
					{
						sumo_move(BACKWARD);
						delay_ms(300); //Delay10KTCYx(125);
						Sumo.searchClockwise = TRUE;
					}
					else if ( Sumo.atFrontRightEdge )
					{
						sumo_move(BACKWARD);
						delay_ms(300); //Delay10KTCYx(125);
						Sumo.searchClockwise = FALSE;
					}
					else if ( Sumo.atBackLeftEdge && Sumo.atBackRightEdge )
					{
						sumo_move(FORWARD);
					}
					else if ( Sumo.atBackLeftEdge || Sumo.atBackRightEdge )
					{
						sumo_move(RIGHT);
						delay_ms(185); //Delay10KTCYx(75);
					}
					else if ( Sumo.atBackRightEdge )
					{
						sumo_move(LEFT);
						delay_ms(185); //Delay10KTCYx(75);
					}
					Sumo.state = HUNT;
					break;
				case HUNT:
					if ( rangeAverage > mAttackThreshold )
					{
						Sumo.state = ATTACK;
					}
					if ( Sumo.first_time )
					{
						if ( DIR_SPIN )
							Sumo.searchClockwise = 1;
						else
							Sumo.searchClockwise = 0;
						Sumo.first_time = 0;
					}
					if ( Sumo.searchClockwise )
						sumo_move(RIGHT);
					else
						sumo_move(LEFT);
					break;
				case ATTACK:
					sumo_move(FORWARD);
					if ( rangeAverage < mTargetThreshold )
					{
						Sumo.state = HUNT;
					}
					break;
				default:
					Sumo.state = SURVIVE;
			}
		}
	}
}

void init_sumo ( void )
{
	#if defined __16F1937
	OSCCONbits.SCS = 0;
	OSCCONbits.IRCF = 0b1111; // INTOSC to 16MHz
	OSCCONbits.SPLLEN = 0; // Enable PLL
	#endif

	ML_IN1 = ML_IN2 = MR_IN1 = MR_IN2 = M_ENB = 1; // Motor Break
	ML_IN1_TRIS = ML_IN2_TRIS = MR_IN1_TRIS = MR_IN2_TRIS = M_ENB_TRIS = 0; // Motor Control pins as outputs

	DIR_SPIN_TRIS = 1;
	DIR_SPIN_ANSEL = 0;
	START_TRIS = 1;
	START_ANSEL = 0;

	if ( START )
	{
		isDebug = TRUE;
	}

	//ENABLE_TRIS = 1;

	#if defined __18F4550
	OpenADC(ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_4_TAD,
		ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS, ADC_11ANA);
	#elif defined __16F1937
	OL_TRIS = FL_TRIS = BL_TRIS = OR_TRIS = FR_TRIS = BR_TRIS = 1;
	OL_ANSEL = FL_ANSEL = BL_ANSEL = OR_ANSEL = FR_ANSEL = BR_ANSEL = 1;
	OpenADC();
	#endif

	if ( isDebug )
	{
		#if defined __18F4550
		CloseUSART(); // Turn off usart if was previously on
		OpenUSART(USART_TX_INT_OFF & USART_RX_INT_OFF & // 9600,8,n,1: 129 - 20 MHz; 1249 - 48MHz; 1666 - 64MHz
			USART_ASYNCH_MODE & USART_EIGHT_BIT & // 19200,8,n,1: 832 - 64MHz
			USART_CONT_RX & USART_BRGH_HIGH, BAUD_GEN); // 115200,8,n,1: 138 - 64MHz

		baudUSART(BAUD_16_BIT_RATE & BAUD_IDLE_CLK_LOW &
			BAUD_WAKEUP_OFF & BAUD_AUTO_OFF & 0x48); // 16 bit BRG
		#elif defined __16F1937
		init_comms();
		#endif
		printf("Robot de Sumo Thor - Gary Servin 2012\r\n");
		#ifdef MEASURE_TIME
		printf("Iniciando medicion de duracion de tiempo reglamentario...\r\n");
		#endif
	}
	else
	{
		mInitUARTLEDs();
	}

	//	RCONbits.IPEN = 0; // Interruption Priority Disabled
	INTCONbits.PEIE = 1; // Peripherial Interrupt Enabled
	INTCONbits.GIE = 1; // Global Interrupt Enable

	return;
}

void sumo_move ( char direction )
{
	//L_IN1 = L_IN2 = R_IN1 = R_IN2 = 1; // Motor Break
	if ( !isDebug )
	{
		switch ( direction )
		{
			case FORWARD:
				ML_IN1 = MR_IN1 = 1;
				ML_IN2 = MR_IN2 = 0;
				break;
			case BACKWARD:
				ML_IN1 = MR_IN1 = 0;
				ML_IN2 = MR_IN2 = 1;
				break;
			case LEFT:
				ML_IN2 = MR_IN1 = 1;
				ML_IN1 = MR_IN2 = 0;
				break;
			case RIGHT:
				ML_IN1 = MR_IN2 = 1;
				ML_IN2 = MR_IN1 = 0;
				break;
			case STOP:
				ML_IN1 = ML_IN2 = MR_IN1 = MR_IN2 = 1;
				break;
			default:
				ML_IN1 = ML_IN2 = MR_IN1 = MR_IN2 = 1;
				break;
		}
	}
	return;
}

void get_sensors ( void )
{
	char i;
	UINT16_VAL mFrontLeftLine, mFrontRightLine, mBackLeftLine, mBackRightLine, mLeftRange, mCenterRange, mRightRange;
	mFrontLeftLine.Val = 0;
	mFrontRightLine.Val = 0;
	mBackLeftLine.Val = 0;
	mBackRightLine.Val = 0;
	mLeftRange.Val = 0;
	mRightRange.Val = 0;

	Sumo.atFrontLeftEdge = 0;
	Sumo.atFrontRightEdge = 0;
	Sumo.atBackLeftEdge = 0;
	Sumo.atBackRightEdge = 0;

	for ( i = 0; i < 6; i++ )
	{
		mLeftRange = ReadADC(OL_SENSOR);
	}

	for ( i = 0; i < 6; i++ )
	{
		mRightRange = ReadADC(OR_SENSOR);
	}

	for ( i = 0; i < 6; i++ )
	{
		mFrontLeftLine = ReadADC(FL_SENSOR);
	}

	for ( i = 0; i < 6; i++ )
	{
		mFrontRightLine = ReadADC(FR_SENSOR);
	}

	for ( i = 0; i < 6; i++ )
	{
		mBackLeftLine = ReadADC(BL_SENSOR);
	}

	for ( i = 0; i < 6; i++ )
	{
		mBackRightLine = ReadADC(BR_SENSOR);
	}

	//	for ( i = 0; i < 4; i++ )
	//	{
	//		mLeftRange.Val += read_a2d(OL_SENSOR).Val;
	//		//		__delay_ms(1);
	//		mRightRange.Val += read_a2d(OR_SENSOR).Val;
	//		//		__delay_ms(1);
	//		mFrontLeftLine.Val += read_a2d(FL_SENSOR).Val;
	//		//		__delay_ms(1);
	//		mFrontRightLine.Val += read_a2d(FR_SENSOR).Val;
	//		//		__delay_ms(1);
	//		mBackLeftLine.Val += read_a2d(BL_SENSOR).Val;
	//		//		__delay_ms(1);
	//		mBackRightLine.Val += read_a2d(BR_SENSOR).Val;
	//		//		__delay_ms(1);
	//	}

	//	mLeftRange.Val >>= 2;
	//	mRightRange.Val >>= 2;
	//	mFrontLeftLine.Val >>= 2;
	//	mFrontRightLine.Val >>= 2;
	//	mBackLeftLine.Val >>= 2;
	//	mBackRightLine.Val >>= 2;

	Sumo.atFrontLeftEdge = (mFrontLeftLine.Val < mEdgeFrontLeftThreshold);
	Sumo.atFrontRightEdge = (mFrontRightLine.Val < mEdgeFrontRightThreshold);

	Sumo.atBackLeftEdge = (mBackLeftLine.Val < mEdgeBackLeftThreshold);
	Sumo.atBackRightEdge = (mBackRightLine.Val < mEdgeBackRightThreshold);

	rangeDifference = mLeftRange.Val - mRightRange.Val;
	rangeAverage = (mLeftRange.Val + mRightRange.Val) >> 1;

	if ( isDebug )
	{
		//printf((string) "S%2.2X,T%2.2X,U00,V00,W00,X00,Y00,Z00\r\n", mLeftLine >> 2, mRightLine >> 2);
		//printf((string) "L=%4d  LR=%4d  R=%4d  RR=%4d  OP=%4d  OPR=%4d\r", mBackLeftLine, mEdgeBackLeftThreshold, mBackRightLine, mEdgeBackRightThreshold, mCenterRange, mTargetThreshold);
		printf("FL= %4d  FR= %4d  BL= %4d  BR= %4d  OP_FL= %4d  OP_FR= %4d\r\n", mFrontLeftLine.Val, mFrontRightLine.Val, mBackLeftLine.Val, mBackRightLine.Val, mLeftRange.Val, mRightRange.Val);
		//printf("%d,%d,%d,%d,%d,%d\r\n", mFrontLeftLine, mFrontRightLine, mBackLeftLine, mBackRightLine, mLeftRange, mRightRange);
		//printf((string) "OPPONENT = %u\r\n", mCenterRange);
		//	Delay1KTCYx(10);
	}

	return;
}

#if defined __18F4550

void wait_5s ( void )
{
	//char i;

	/*OpenTimer1(TIMER_INT_ON & T1_16BIT_RW & T1_SOURCE_INT & T1_PS_1_8 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);

	for ( i = 1; i <= 50; i++ )
	{
		WriteTimer1(0x7E9A);
		while ( !Sumo.timeout );
		Sumo.timeout = 0;

		if ( i == 10 || i == 20 || i == 30 || i == 40 )
		{
			LED_TX = !LED_TX;
		}
		else if ( i == 50 )
		{
			LED_TX = 1;
		}
	}
	CloseTimer1();*/
	//return;
	int t;
	for ( t = 0; t < 9; t++ )
	{
		Delay10KTCYx(230);
	}
	return;
}

void putch ( char data )
{
	while ( !PIR1bits.TXIF )
		continue;
	TXREG = data;
}

int read_a2d ( unsigned char channel )
{
	ADCON0 = (ADCON0 & 0b11000011) | ((channel << 2) & 0b00111100);
	ADCON0bits.GO = 1; // Start conversion
	Delay10TCYx(3);
	while ( BusyADC() == 1 ); // While conversion is not finished
	return ReadADC(); // Return 10 bit value
}

#elif defined __16F1937

void delay_ms ( UINT16 miliseconds )
{
	UINT8 temp;
	for ( temp = miliseconds; temp >= 1; temp-- )
		__delay_ms(1);
}

void delay_s ( UINT16 seconds )
{
	UINT8 temp;
	for ( temp = seconds; temp >= 1; temp-- )
	{
		LED_TX = LED_RX = 1;
		__delay_ms(250);
		__delay_ms(250);
		__delay_ms(250);
		LED_TX = LED_RX = 0;
		__delay_ms(240);
	}
}
#endif

void interrupt IRS ( void )
{
	#if defined MEASURE_TIME
	if ( PIE1bits.TMR1IE && PIR1bits.TMR1IF )
	{
		test++;
		PIR1bits.TMR1IF = 0;
	}
	#endif
}
