/************************************************************************/
/************************************************************************/
/*******************  Author : Mohamed shaban   *************************/
/*******************     layer : mcal            *************************/
/*******************     Version : 1.00         *************************/
/*******************     SWC : EXTI             *************************/
/************************************************************************/
/************************************************************************/

#include  "STD_types.h"
#include  "BIT_math.h"

#include  "GIE_interface.h"
#include  "GIE_register.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}

void GIE_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}
