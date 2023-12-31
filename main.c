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
#include  "EXTI_interface.h"
#include  "GIE_interface.h"


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
void left_paddle(void);
void right_panddle(void);


void  main(void)
{

	PORT_voidInti();
	CLCD_voidInit(0);
	EXTI_voidInt0_pre();
	EXTI_voidInt1_pre();
	EXTI_u8Set_Callback_int0(left_paddle);
	EXTI_u8Set_Callback_int1(right_panddle);

	GIE_voidEnable();




	while(1){



		ball_position();
		displaygame();


	}
}
void left_paddle(void)
{

	if(leftPaddlePosition==0)
	{
		leftPaddlePosition=1;
	}
	else
	{
		leftPaddlePosition=0;

	}
	EXTI_voidclearflag(INT0);
}
void right_panddle(void)
{
	if(rightPaddlePosition==0)
	{
		rightPaddlePosition=1;
	}
	else
	{
		rightPaddlePosition=0;
	}
	EXTI_voidclearflag(INT1);
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
	CLCD_voidGOTOXY(0, ball);
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

		leftPlayerScore++;LCD_ClearScreen();
		CLCD_voidSendString("right score = ");
		CLCD_voidNumber(rightPlayerScore);
		CLCD_voidGOTOXY(1, 0);
		CLCD_voidSendString("left score = ");
		CLCD_voidNumber(leftPlayerScore);
		_delay_ms(2000);
	}
}
