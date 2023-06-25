/************************************************************************/
/************************************************************************/
/*******************  Author : Mohamed shaban   *************************/
/*******************     layer : hal            *************************/
/*******************     Version : 1.00         *************************/
/*******************        SWC : CLCD          *************************/
/************************************************************************/
/************************************************************************/

#include "util/delay.h"

#include "STD_types.h"

#include  "DIO_interface.h"

#include  "CLCD_config.h"
#include  "CLCD_interface.h"
#include  "CLCD_pravite.h"

void CLCD_voidSendCommand(u8 copy_u8command)
{
	/*set rs low for command*/
	setbitvalue(CLCD_CLR_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);
	/* set rw PIN to write*/
	setbitvalue(CLCD_CLR_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);
	/*set data value*/
	setportvalue(CLCD_DATA_PORT, copy_u8command);
	/*set the enable pulse..*/
	setbitvalue(CLCD_CLR_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	setbitvalue(CLCD_CLR_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
}
void CLCD_voidSendData(u8 copy_u8Data)
{
	/*set rs high for data*/
	setbitvalue(CLCD_CLR_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);
	/* set rw PIN to write*/
	setbitvalue(CLCD_CLR_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);
	/*set data value*/
	setportvalue(CLCD_DATA_PORT, copy_u8Data);
	/*set the enable pulse..*/
	setbitvalue(CLCD_CLR_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	setbitvalue(CLCD_CLR_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
}
void CLCD_voidInit(u8 mode)
{
	if(mode==mode_1){
	/*wait for more than 40 ms*/
	_delay_ms(41);

	/*function set command : 2line ,5*8 front size*/
	CLCD_voidSendCommand(0b00111000);

	/*diplaly on off control,display enable,cursor enable,blink enable*/
	CLCD_voidSendCommand(0b00001100);

	/*clear display*/
	CLCD_voidSendCommand(1);
	}
	else if(mode==mode_2)
	{
		/*wait for more than 40 ms*/
		_delay_ms(41);

		CLCD_voidSendCommand(0b00110000);
		_delay_us(100);						// 4 bit sequence for LCD 4-bits initializing
		CLCD_voidSendCommand(0b00110000);
		_delay_us(100);
		CLCD_voidSendCommand(0b00110000);
		_delay_us(100);							// 4 bit sequence for LCD 4-bits initializing
		CLCD_voidSendCommand(0b00100000);
		_delay_us(100);							// mode:4 bit , display:2Lines , font:5x7 dots

		/*function set command : 2line ,5*8 front size*/
		CLCD_voidSendCommand(0b00111000);

		/*diplaly on off control,display enable,cursor enable,blink enable*/
		CLCD_voidSendCommand(0b00001100);

		/*clear display*/
		CLCD_voidSendCommand(1);
	}

}
void CLCD_voidSendString(const char* copy_string)
{
	while(*copy_string !='\0')
	{
		CLCD_voidSendData(*copy_string);
		copy_string++;

	}

}
void CLCD_voidGOTOXY(u8 copy_u8xpostion,u8 copy_u8ypostion)
{
	u8 Local_u8Address;
	if(copy_u8xpostion==0)
	{
		/*the location at the frist line */
		Local_u8Address=copy_u8ypostion;
	}
	else if(copy_u8xpostion==1)
	{
		/*the location at the second line*/
		Local_u8Address=0x40+copy_u8ypostion;
	}
	/*set bit 7 in DDRAM address and send command*/
	CLCD_voidSendCommand(Local_u8Address+128);
}

void CLCD_voidWrite_SpacialC(u8* copy_pu8Arr,u8 copy_u8Blocknum,u8 copy_u8xpos,u8 copy_u8ypos)
{
	/* write into the CGRAM*/
	u8 address=8*copy_u8Blocknum;
	CLCD_voidSendCommand(address+64);
	for(u8 i=0;i<8;i++)
	{
		CLCD_voidSendData(copy_pu8Arr[i]);
	}
	/*return to dd ram*/
	CLCD_voidGOTOXY(copy_u8xpos	, copy_u8ypos);

	CLCD_voidSendData(copy_u8Blocknum);

}
void CLCD_voidNumber(u32 copy_u32Number)
{

	/*create arr of char from 11 element*/
	char buf[12];  // max 10 digits + null terminator
	uint8_t i = 10;
	buf[i--] = '\0';
	do {
		buf[i--] = copy_u32Number % 10 + '0';
		copy_u32Number /= 10;
	} while (copy_u32Number > 0 && i > 0);
	CLCD_voidSendString(&buf[i+1]);
	void CLCD_voidWritename(u8* copy_pu8Name,u8 copy_numberofchar)
	{

		for( u8 Local_u8var=0 ; Local_u8var<copy_numberofchar;Local_u8var++)
		{
			CLCD_voidWrite_SpacialC(copy_pu8Name[Local_u8var], Local_u8var, 0, Local_u8var);
		}
	}



}
void LCD_ClearScreen()
{
	CLCD_voidSendCommand(CLEAR_COMMAND);
}


void CLCD_voidCursorShift(u8 dircation)
{
	if(dircation==Right)
		CLCD_voidSendCommand(0x14);
	else if(dircation==Left)
		CLCD_voidSendCommand(0x10);
}

void CLCD_voidDataShift(u8 dircation)
{
	if(dircation==Right)
		CLCD_voidSendCommand(0x1c);
	else if(dircation==Left)
		CLCD_voidSendCommand(0x18);

}




