/******* Author  : Mohamed Hamdy *******/
/******* Date    : 21/9/2022     *******/
/******* SWC     : KPD           *******/
/******* Version : 1             *******/

/* LIB Layer */
#include "type.h"
#include "bit.h"
#define  F_CPU 8000000UL
#include "util/delay.h"

/* MCAL Layer */
#include "interface.h"

/* HAL Layer */
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

static u8 KPD_Au8Keys[4][4] = KPD_Au8_KEY_VALUES;
static u8 KPD_Au8RowsPins[4]={KPD_u8_R1_PIN,KPD_u8_R2_PIN,KPD_u8_R3_PIN,KPD_u8_R4_PIN};
static u8 KPD_Au8ColsPins[4]={KPD_u8_C1_PIN,KPD_u8_C2_PIN,KPD_u8_C3_PIN,KPD_u8_C4_PIN};
/* Rows -> O/P --- Cols -> I/P */
u8 KPD_u8GetKey(u8 * Copy_pu8ReturnedKey)
{
	*Copy_pu8ReturnedKey = KPD_u8_KEY_NOT_PRESSED;
	u8 Local_u8ReturnedState =OK;
	u8 Local_u8RowsCounter ,Local_u8ColsCounter ,Local_u8ReturnedPinValue,Local_u8Flag=0;
	/* Check Pointer Validation */
	if(Copy_pu8ReturnedKey != NULL)
	{
		for(Local_u8RowsCounter=0 ; Local_u8RowsCounter<=3 ; ++Local_u8RowsCounter)
		{
			DIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8RowsCounter],DIO_u8_PIN_LOW);
			for(Local_u8ColsCounter=0 ; Local_u8ColsCounter<=3 ; ++Local_u8ColsCounter)
			{
				DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8ReturnedPinValue);
				/* Check If Switch Is Pressed */ 
				if(Local_u8ReturnedPinValue == 0)
				{
					/* Debouncing */
					_delay_ms(20);
					while(Local_u8ReturnedPinValue == 0)
					{
						DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],&Local_u8ReturnedPinValue);
					}
					*Copy_pu8ReturnedKey = KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					Local_u8Flag=1;
					/* To Terminate The Loop If The Switch Is Pressed */
					break;
				}
			}
			/* Deactivate Current Row */
			DIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8RowsCounter],DIO_u8_PIN_HIGH);
			if(Local_u8Flag == 1) break;
		}
	}
	else
	{
		Local_u8ReturnedState = NOT_OK;
	}
	return Local_u8ReturnedState;
}
