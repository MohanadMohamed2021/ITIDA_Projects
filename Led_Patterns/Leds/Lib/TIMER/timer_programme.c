#include "bit.h"
#include "type.h"
#include "interface.h"
#include "timer_private.h"
#include "timer_config.h"
#include "timer_interface.h"

static void (*TMR_pf)(void) = NULL;
static void (*TMR_pf2)(void) = NULL;
static void (*TMR_pf3)(void) = NULL;
volatile u16 TMR_u16ICUONPeriod;
volatile u16 TMR_u16ICUOFFPeriod;
void TMR0_voidInitial(void)
{
	//Select Mode Of Timer
	switch(TMR_u8_SELECT_MODE)
	{
		case(TMR_u8_NORMAL_MODE):
		{
			CLEAR_BIT(TCCR0_u8_REG,6);
			CLEAR_BIT(TCCR0_u8_REG,3);
			break;
		}
		case(TMR_u8_CTC_MODE):
		{
			CLEAR_BIT(TCCR0_u8_REG,6);
			SET_BIT(TCCR0_u8_REG,3);
			break;
		}
		case(TMR_u8_PWM_MODE):
		{
			CLEAR_BIT(TCCR0_u8_REG,3);
			SET_BIT(TCCR0_u8_REG,6);
			switch(TMR_u8_INVERTING_STATE)
			{
				case(TMR_u8_INVERTING):
				{
					SET_BIT(TCCR0_u8_REG,4);
			        SET_BIT(TCCR0_u8_REG,5);
					break;
				}
				case(TMR_u8_NON_INVERTING):
				{
					CLEAR_BIT(TCCR0_u8_REG,4);
			        SET_BIT(TCCR0_u8_REG,5);
					break;
				}
			}
			break;
		}
		case(TMR_u8_FAST_PWM_MODE):
		{
			SET_BIT(TCCR0_u8_REG,3);
			SET_BIT(TCCR0_u8_REG,6);
			switch(TMR_u8_INVERTING_STATE)
			{
				case(TMR_u8_INVERTING):
				{
					SET_BIT(TCCR0_u8_REG,4);
			        SET_BIT(TCCR0_u8_REG,5);
					break;
				}
				case(TMR_u8_NON_INVERTING):
				{
					CLEAR_BIT(TCCR0_u8_REG,4);
			        SET_BIT(TCCR0_u8_REG,5);
					break;
				}
			}
			break;
		}
	}
	// SET PRELOAD_VALUE
	if(TMR_u8_PRELOAD_VALUE)
	{
		TCNT_u8_REG = TMR_u8_PRELOAD_VALUE;
	}
	// SET CTC_VALUE
	if(TMR_u8_CTC_VALUE)
	{
		OCR0_u8_REG = TMR_u8_CTC_VALUE;
	}
	// SELECT CLOCK WITH PRESCALER 8
	CLEAR_BIT(TCCR0_u8_REG,2);
	CLEAR_BIT(TCCR0_u8_REG,0);
	SET_BIT(TCCR0_u8_REG,1);
}
void TMR0_voidControlPIE(u8 Copy_u8TimerPIEState,u8 Copy_u8ComparePIEState)
{
	//ENABLE PIE FOR TIMER&&COMPARE MATCH
	switch(Copy_u8TimerPIEState)
	{
		case(TMR_u8_TIMER_PIE_ON):
		{
			SET_BIT(TIMSK_u8_REG,0);
			break;
		}
		case(TMR_u8_TIMER_PIE_OFF):
		{
			CLEAR_BIT(TIMSK_u8_REG,0);
			break;
		}
	}
	//ENABLE PIE COMPARE MATCH
	switch(Copy_u8ComparePIEState)
	{
		case(TMR_u8_COMPARE_PIE_ON):
		{
			SET_BIT(TIMSK_u8_REG,1);
			break;
		}
		case(TMR_u8_COMPARE_PIE_OFF):
		{
			CLEAR_BIT(TIMSK_u8_REG,1);
			break;
		}
	}
}
u8 TMR_u8SetCallBack(u8 Copy_u8Mode,void (*Copy_pf)(void))
{
	u8 Local_u8ReturnedState=OK;
	if((Copy_u8Mode<=TMR_u8_CTC)&&(Copy_pf!=NULL))
	{
	switch(Copy_u8Mode)
	{
		case(TMR_u8_NORMAL_MODE):
		{
		   TMR_pf = Copy_pf;
		   break;
		}
	    case(TMR_u8_CTC_MODE):
		{
			TMR_pf2=Copy_pf;
			break;
		}
	}
	}
	else
	{
		Local_u8ReturnedState=NOT_OK;
	}	
	return Local_u8ReturnedState;
}
void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	switch(TMR_u8_CASE)
	{
		case(1):
		{
			if(TMR_pf != NULL)
		   {
		      TMR_pf();
		   }
			break;
		}
		case(2):
		{
			TCNT_u8_REG = TMR_u8_PRELOAD_VALUE;
			if(TMR_pf != NULL)
		   {
		      TMR_pf();
		   }
			break;
		}
		case(3):
		{
			static u16 Local_u16Counter=0;
	Local_u16Counter++;
	if(Local_u16Counter==TMR_u8_COUNTER_MAX_VALUE)
	{
		// SET PRELOAD_VALUE
		TCNT_u8_REG = TMR_u8_PRELOAD_VALUE;
		//reset counter
		Local_u16Counter=0;
		if(TMR_pf != NULL)
		{
		TMR_pf();
		}
	}
			break;
		}
	}
}
void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	if(TMR_pf != NULL)
	{
		TMR_pf2();
    }
}
void TMR1_voidInitial(void)
{
	/*Select mode 14*/
	CLEAR_BIT(TCCR1A_u8_REG,0);
	SET_BIT(TCCR1A_u8_REG,1);
	SET_BIT(TCCR1B_u8_REG,4);
	SET_BIT(TCCR1B_u8_REG,3);
	/*Select Non Inverting Mode*/
	CLEAR_BIT(TCCR1A_u8_REG,6);
	SET_BIT(TCCR1A_u8_REG,7);
	/*Set Value Of Overflow*/
	ICR1LH_u16_REG = TMR1_u16_OVER_FLOW_VALUE;
	/*Select ctc Value*/
	OCR1ALH_u16_REG=TMR1_u16_CTC_VALUE;
	/* Set 	Prescaler to 8*/
	CLEAR_BIT(TCCR1B_u8_REG,2);
	SET_BIT(TCCR1B_u8_REG,1);
	CLEAR_BIT(TCCR1B_u8_REG,0);
}
void TMR_voidSetOcr0Value(u8 *Copy_pu8Ocr0Value)
{
	OCR0_u8_REG = *Copy_pu8Ocr0Value;
}
void TMR_voidSetOcr1aValue(u8 *Copy_pu8Ocr1aValue)
{
	OCR1ALH_u16_REG = *Copy_pu8Ocr1aValue;
}
void TMR1_voidReadTMR1Reg(u16 *Copy_pu16TMR1Reg)
{
	*Copy_pu16TMR1Reg = TCNT1LH_u16_REG;
}
void TMR1_voidEnableICU(void)
{
	/*Select Edge*/
	SET_BIT(TCCR1B_u8_REG,6);
	/*Enable PIE*/
	SET_BIT(TIMSK_u8_REG,5);
}
void TMR1_voidDisableICU(void)
{
	/*Disable PIE*/
	CLEAR_BIT(TIMSK_u8_REG,5);
}
u8 TMR1_u8GetTotalPeriod(u32 *Copy_pu32TotalPeriod)
{
u8 Local_u8ReturnedState=OK;
	if(Copy_pu32TotalPeriod!=NULL)
	{
		*Copy_pu32TotalPeriod = TMR_u16ICUONPeriod + TMR_u16ICUOFFPeriod;
	}
	else
	{
		Local_u8ReturnedState = NOT_OK;
	}
	return Local_u8ReturnedState;
}
u8 TMR1_u8GetDutyCycle(u8 *Copy_pu8DutyCycle)
{
	u8 Local_u8ReturnedState=OK;
	if(Copy_pu8DutyCycle!=NULL)
	{
		*Copy_pu8DutyCycle = (u8)((TMR_u16ICUONPeriod*100UL)/(TMR_u16ICUONPeriod + TMR_u16ICUOFFPeriod));
	}
	else
	{
		Local_u8ReturnedState = NOT_OK;
	}
	return Local_u8ReturnedState;
}	
void __vector_6(void)  __attribute__((signal));
void __vector_6(void)
{
	u16 Local_u16TimerValue;
	Local_u16TimerValue = ICR1LH_u16_REG;
	static u16 Local_u16OldTimerValue = 0;
	static u8 Local_u8Flag=0;
	if(Local_u8Flag==0)
	{
		TMR_u16ICUOFFPeriod = Local_u16TimerValue - Local_u16OldTimerValue;
		CLEAR_BIT(TCCR1B_u8_REG,6);
		Local_u8Flag = 1;
	}
	else if(Local_u8Flag==0)
	{
		TMR_u16ICUONPeriod = Local_u16TimerValue - Local_u16OldTimerValue;
		SET_BIT(TCCR1B_u8_REG,6);
		Local_u8Flag = 0;
	}
	Local_u16OldTimerValue = Local_u16TimerValue;
}
