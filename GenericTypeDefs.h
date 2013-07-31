/**
   \version: 1.0

   
   \author Suky (Casanova Alejandro) 
   \web www.micros-designs.com.ar
   \date 16/08/10


///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2010 www.micros-designs.com.ar               ////
//// Este c�digo puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garant�a de ning�n tipo.        ////
////                                                                   ////
////                                                                   ////
/////////////////////////////////////////////////////////////////////////// 
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 16/08/10      Suky               Original (Rev 1.0)                        *
 * 20/08/10      Suky               Se incluye CodeVisionAVR                  *
 *----------------------------------------------------------------------------* */
#ifndef __GENERIC_TYPE_DEFS_H_
#define __GENERIC_TYPE_DEFS_H_

//#include <stddef.h>


#if defined(__PCH__) || defined(__PCM__)
typedef int1 BOOLEAN_;

typedef signed int SINT;
typedef signed char SINT8;
typedef signed long SINT16;
typedef signed long long SINT32;


typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned long UINT16;
typedef unsigned long long UINT32;
#endif

#if defined(__18CXX)

typedef enum _BOOLEAN
{
	FALSE = 0, TRUE
} BOOLEAN_;

typedef enum _BOOL
{
	FALSE = 0, TRUE
} BOOL;

#ifndef NULL
#define NULL    0//((void *)0)
#endif

#define	PUBLIC                                  // Function attributes
#define PROTECTED
#define PRIVATE   static

typedef unsigned char BYTE; // 8-bit unsigned
typedef unsigned short int WORD; // 16-bit unsigned
typedef unsigned long DWORD; // 32-bit unsigned
typedef unsigned long long QWORD; // 64-bit unsigned
typedef signed char CHAR; // 8-bit signed
typedef signed short int SHORT; // 16-bit signed
typedef signed long LONG; // 32-bit signed
typedef signed long long LONGLONG; // 64-bit signed

/* Alternate definitions */
typedef void VOID;

typedef char CHAR8;
typedef unsigned char UCHAR8;

typedef signed int SINT;
typedef signed char SINT8;
typedef signed short int SINT16;
typedef signed long int SINT32;


typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef unsigned short long UINT24;
typedef unsigned long int UINT32;

#elif defined(HI_TECH_C)
typedef unsigned char BYTE; // 8-bit unsigned
typedef unsigned short int WORD; // 16-bit unsigned
#endif

#if defined (__C30__)

typedef enum _BOOLEAN
{
	FALSE = 0, TRUE
} BOOLEAN_;

typedef signed int SINT;
typedef signed char SINT8;
typedef signed int SINT16;
typedef signed long SINT32;


typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;
#endif

#if defined(HI_TECH_C)
typedef bit BOOLEAN_;

typedef signed char SINT;
typedef signed char SINT8;
typedef signed int SINT16;
typedef signed long SINT32;


typedef unsigned char UINT;
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;
#endif

typedef union
{
	UINT8 Val;

	struct
	{
		UINT8 b0 : 1;
		UINT8 b1 : 1;
		UINT8 b2 : 1;
		UINT8 b3 : 1;
		UINT8 b4 : 1;
		UINT8 b5 : 1;
		UINT8 b6 : 1;
		UINT8 b7 : 1;
	};

	struct
	{
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
	} bits;
} UINT8_VAL, UINT8_BITS, BYTE_VAL, BYTE_BITS;

typedef union
{
	UINT16 Val;
	UINT8 v[2];

	struct
	{
		UINT8 LB;
		UINT8 HB;
	};

	struct
	{
		UINT8 b0 : 1;
		UINT8 b1 : 1;
		UINT8 b2 : 1;
		UINT8 b3 : 1;
		UINT8 b4 : 1;
		UINT8 b5 : 1;
		UINT8 b6 : 1;
		UINT8 b7 : 1;
		UINT8 b8 : 1;
		UINT8 b9 : 1;
		UINT8 b10 : 1;
		UINT8 b11 : 1;
		UINT8 b12 : 1;
		UINT8 b13 : 1;
		UINT8 b14 : 1;
		UINT8 b15 : 1;
	};

	struct
	{
		BYTE LB;
		BYTE HB;
	} byte;

	struct
	{
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
		unsigned char b8 : 1;
		unsigned char b9 : 1;
		unsigned char b10 : 1;
		unsigned char b11 : 1;
		unsigned char b12 : 1;
		unsigned char b13 : 1;
		unsigned char b14 : 1;
		unsigned char b15 : 1;
	} bits;
} UINT16_VAL, UINT16_BITS, WORD_VAL, WORD_BITS;

#if defined(__18CXX)

typedef union
{
	UINT24 Val;
	UINT8 v[3];

	struct
	{
		UINT8 LB;
		UINT8 HB;
		UINT8 UB;
	};

	struct
	{
		UINT8 b0 : 1;
		UINT8 b1 : 1;
		UINT8 b2 : 1;
		UINT8 b3 : 1;
		UINT8 b4 : 1;
		UINT8 b5 : 1;
		UINT8 b6 : 1;
		UINT8 b7 : 1;
		UINT8 b8 : 1;
		UINT8 b9 : 1;
		UINT8 b10 : 1;
		UINT8 b11 : 1;
		UINT8 b12 : 1;
		UINT8 b13 : 1;
		UINT8 b14 : 1;
		UINT8 b15 : 1;
		UINT8 b16 : 1;
		UINT8 b17 : 1;
		UINT8 b18 : 1;
		UINT8 b19 : 1;
		UINT8 b20 : 1;
		UINT8 b21 : 1;
		UINT8 b22 : 1;
		UINT8 b23 : 1;
	};
} UINT24_VAL, UINT24_BITS;
#endif

typedef union
{
	UINT32 Val;
	UINT16 w[2];
	UINT8 v[4];

	struct
	{
		UINT16 LW;
		UINT16 HW;
	};

	struct
	{
		UINT8 LB;
		UINT8 HB;
		UINT8 UB;
		UINT8 MB;
	};

	struct
	{
		UINT16_VAL low;
		UINT16_VAL high;
	};

	struct
	{
		UINT8 b0 : 1;
		UINT8 b1 : 1;
		UINT8 b2 : 1;
		UINT8 b3 : 1;
		UINT8 b4 : 1;
		UINT8 b5 : 1;
		UINT8 b6 : 1;
		UINT8 b7 : 1;
		UINT8 b8 : 1;
		UINT8 b9 : 1;
		UINT8 b10 : 1;
		UINT8 b11 : 1;
		UINT8 b12 : 1;
		UINT8 b13 : 1;
		UINT8 b14 : 1;
		UINT8 b15 : 1;
		UINT8 b16 : 1;
		UINT8 b17 : 1;
		UINT8 b18 : 1;
		UINT8 b19 : 1;
		UINT8 b20 : 1;
		UINT8 b21 : 1;
		UINT8 b22 : 1;
		UINT8 b23 : 1;
		UINT8 b24 : 1;
		UINT8 b25 : 1;
		UINT8 b26 : 1;
		UINT8 b27 : 1;
		UINT8 b28 : 1;
		UINT8 b29 : 1;
		UINT8 b30 : 1;
		UINT8 b31 : 1;
	};

	struct
	{
		WORD LW;
		WORD HW;
	} word;

	struct
	{
		BYTE LB;
		BYTE HB;
		BYTE UB;
		BYTE MB;
	} byte;

	struct
	{
		WORD_VAL low;
		WORD_VAL high;
	} wordUnion;

	struct
	{
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
		unsigned char b8 : 1;
		unsigned char b9 : 1;
		unsigned char b10 : 1;
		unsigned char b11 : 1;
		unsigned char b12 : 1;
		unsigned char b13 : 1;
		unsigned char b14 : 1;
		unsigned char b15 : 1;
		unsigned char b16 : 1;
		unsigned char b17 : 1;
		unsigned char b18 : 1;
		unsigned char b19 : 1;
		unsigned char b20 : 1;
		unsigned char b21 : 1;
		unsigned char b22 : 1;
		unsigned char b23 : 1;
		unsigned char b24 : 1;
		unsigned char b25 : 1;
		unsigned char b26 : 1;
		unsigned char b27 : 1;
		unsigned char b28 : 1;
		unsigned char b29 : 1;
		unsigned char b30 : 1;
		unsigned char b31 : 1;
	} bits;
} UINT32_VAL, DWORD_VAL;
#endif 
