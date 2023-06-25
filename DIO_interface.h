/************************************************************************/
/************************************************************************/
/*******************  Author : Mohamed shaban   *************************/
/*******************     layer : mcal           *************************/
/*******************     Version : 1.00         *************************/
/*******************        SWC : DIO           *************************/
/************************************************************************/
/************************************************************************/

/*--------------------------------------------------------------------------------
 * --- 					macros used with DIO								------
 * -------------------------------------------------------------------------------
 */

/*	 define status of pin	*/
#define DIO_u8PIN_HIGH      1
#define DIO_u8PIN_LOW       0


/*	define status of port	*/
#define DIO_u8PORT_HIGH     0xff
#define DIO_u8PORT_LOW      0

/* define PORTS	*/
#define DIO_u8PORTA         0
#define DIO_u8PORTB         1
#define DIO_u8PORTC         2
#define DIO_u8PORTD         3

/* define PINS	*/
#define DIO_u8PIN0          0
#define DIO_u8PIN1          1
#define DIO_u8PIN2          2
#define DIO_u8PIN3          3
#define DIO_u8PIN4          4
#define DIO_u8PIN5          5
#define DIO_u8PIN6          6
#define DIO_u8PIN7          7

/*	define pull up res	*/
#define source    1
#define sink      0

#define active_high 1
#define active_low  0


#ifndef _DIO_INTERFACE_h
#define _DIO_INTERFACE_h

/*
 * Prototype   : u8 setbitvalue(u8 copy_U8port,u8 copy_u8pin,u8 copy_u8value);
 *
 * Description : write value on one bit of register
 *
 * Arguments   : Register: takes  DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD
 * 			   : BITS	 : takes DIO_u8PIN0 , DIO_u8PIN1 , DIO_u8PIN2 , DIO_u8PIN3 , DIO_u8PIN4
								 DIO_u8PIN5 , DIO_u8PIN6 , DIO_u8PIN7
 *               Value  : takes HIGH sets whole reg high,LOW sets whole reg low, or Custom -(0-255)values- PORTx values
 * return      : u8 number used for error handling
 *			     (0) means no error,(1) means Undefined Argument
 */
u8 setbitvalue(u8 copy_U8port,u8 copy_u8pin,u8 copy_u8value);


u8 setportvalue (u8 copy_u8port,u8 copy_u8value);

u8 getbit (u8 copy_port ,u8 copy_pin,u8* copy_value);

u8 togglebit(u8 copy_u8Port, u8 copy_u8Pin);


#endif
