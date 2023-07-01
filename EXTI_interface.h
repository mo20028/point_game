/************************************************************************/
/************************************************************************/
/*******************  Author : Mohamed shaban   *************************/
/*******************     layer : mcal            *************************/
/*******************     Version : 1.00         *************************/
/*******************     SWC : EXTI             *************************/
/************************************************************************/
/************************************************************************/


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_
/*choose mode:
 * 				1: for rising edge
 * 				2: for falling edge
 * 				3: for any_logic
 * 				4: for level_low
 * 				*/
#define level_low 		1
#define any_logic 		2
#define falling_edge 	3
#define rising_edge 	4

/* choose int_num :
 * 				1: for INT0
 * 				2: for INT1
 * 				3: for INT2
 * 								*/
#define	INT0	5
#define INT1	6
#define INT2	7


u8 	 EXTI_u8Int0_Pos(u8 copy_u8mode);
void EXTI_voidInt0_pre(void);

u8   EXTI_u8Int1_pos(u8 copy_u8mode);
void EXTI_voidInt1_pre(void);

u8 EXTI_u8Int2_pos(u8 copy_u8mode);
void EXTI_voidINT2_pre(void);

u8 EXTI_u8sense(u8 copy_u8mode,u8 copy_u8int_num);

/* function : clear interrupt flag
 * input    : the number of the int source
 * 			: choose :
 * 						1: int0
 * 						2: int1
 * 						3: int2
 * 	output  :error if the input in invalid
 * 	*/
u8 EXTI_voidclearflag(u8 copy_u8num);
u8 EXTI_u8ReadFlag(u8 copy_u8num);

u8 EXTI_u8Set_Callback_int0(void (*copy_pvInt0)(void));
u8 EXTI_u8Set_Callback_int1(void (*copy_pvInt1)(void));
u8 EXTI_u8Set_Callback_int2(void (*copy_pvInt2)(void));



#endif
