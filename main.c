/*
 * sorce.c
 *
 *  Created on: Jun 23, 2023
 *      Author: Mohamed Shaban
 */
#include "BIT_math.h"
#include "STD_types.h"
#include "util/delay.h"

#include  "DIO_interface.h"
#include  "PORT_interface.h"
#include  "LCD_interface.h"
#include  "CLCD_interface.h"
u8 arr[8]={
		0b00000000,0b00000000,0b00000000,0b00011100,0b00011100,0b00011100,0b00000000,0
};
u8 arr_1[8]={
		0b00000000,0b00000000,0b00000000,0b00011101,0b00011101,0b00011101,0b00000001,1
};

#define FIELD_WIDTH  16
#define FIELD_HEIGHT  2

#define LEFT_PADDLE_START_POSITION  0
#define RIGHT_PADDLE_START_POSITION  0

#define BALL_START (FIELD_WIDTH / 2)

u8 leftPaddlePosition = LEFT_PADDLE_START_POSITION;
u8 rightPaddlePosition = RIGHT_PADDLE_START_POSITION;
u8 ball = BALL_START;
u8 ball_po;
u8 dir  ;

u8 leftPlayerScore = 0;
u8 rightPlayerScore = 0;

u8 left_value;
u8 right_value;

void movePaddles();
void ball_position();
void displaygame();


void  main(void)
{

	PORT_voidInti();
	CLCD_voidInit(0);



	while(1){


		movePaddles();
		ball_position();
		displaygame();


//		for(u8 iterator=1;iterator<15;iterator++)
//		{
//			CLCD_voidDataShift(Right);
//			_delay_ms(100);
//
//		}
//		for(u8 iterator=15;iterator>1;iterator--)
//		{
//			CLCD_voidDataShift(lift);
//			_delay_ms(100);
//		}

	}
}

void movePaddles() {
  // Move the left paddle

	getbit(DIO_u8PORTC, DIO_u8PIN0, &left_value);
	if(left_value==0)
	{
		if(leftPaddlePosition==0)
		{
			leftPaddlePosition=1;
					}
		else
		{
			leftPaddlePosition=0;

		}

	}
	/* move right paddle*/
	getbit(DIO_u8PORTC, DIO_u8PIN1, &right_value);
	if(right_value==0)
	{
		if(rightPaddlePosition==0)
		{
			rightPaddlePosition=1;
		}
		else
		{
			rightPaddlePosition=0;

		}

	}


  }
void ball_position()
{
	if(dir==0)
	{
		ball++;
	}
	else ball--;

	if(ball==1||ball==14)
		dir= ~dir;

}
void displaygame()
{
	LCD_ClearScreen();

	/* set postion of left paddle*/
	CLCD_voidGOTOXY(leftPaddlePosition	, 0);
	CLCD_voidSendData('|');
	while(!left_value)
	{
		getbit(DIO_u8PORTC, DIO_u8PIN0, &left_value);
	}
	/* set postion of right paddle*/
	CLCD_voidGOTOXY(rightPaddlePosition	, 15);
	CLCD_voidSendData('|');
	while(!right_value)
	{
		getbit(DIO_u8PORTC, DIO_u8PIN1, &right_value);
	}

	/* set postion of ball 	*/
	CLCD_voidGOTOXY(1, ball);
	CLCD_voidSendData('0');
	_delay_ms(100);

	/* right score */
	if(ball ==1&&leftPaddlePosition==1)
		{
			rightPlayerScore++;
			LCD_ClearScreen();
			CLCD_voidSendString("right score = ");
			CLCD_voidNumber(rightPlayerScore);
			CLCD_voidGOTOXY(1, 0);
			CLCD_voidSendString("left score = ");
			CLCD_voidNumber(leftPlayerScore);
			_delay_ms(2000);

		}
	/* left score */
	if(ball == 14 && rightPaddlePosition==1)
	{
		ball_po=~ball_po;
		leftPlayerScore++;LCD_ClearScreen();
		CLCD_voidSendString("right score = ");
		CLCD_voidNumber(rightPlayerScore);
		CLCD_voidGOTOXY(1, 0);
		CLCD_voidSendString("left score = ");
		CLCD_voidNumber(leftPlayerScore);
		_delay_ms(2000);
	}
}
