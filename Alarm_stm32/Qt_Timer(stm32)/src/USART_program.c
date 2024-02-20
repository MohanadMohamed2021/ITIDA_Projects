/********************************************************************/
/*  Author	 : Mohamed Hamdy							 	        */
/*  Version	 : V01 													*/
/*	Date	 : 12 November 2020                                     */
/********************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

void MUSART1_voidInit(void)
{
	/* Baud rate */
	USART1 -> BRR = USART_BAUD_RATE ;
	/*
		1- Enable RX
		2- Enable TX
		3- Enable USART
		4- 8 Bits       */
	USART1 -> CR1 = (USART_EN | USART_WORD_LENGTH | USART_WAKE_UP | USART_PARITY_EN | USART_PARITY_SELECTION | USART_PE_INTERRUPT | USART_TXE_INTERRUPT | USART_TCIE_INTERRUPT
			| USART_RXNE_INTERRUPT | USART_IDLE_INTERRUPT | USART_TX_EN | USART_RX_EN | USART_RX_WAKEUP | USART_BREAK_SEND ) ;

	/* Clear Status Registers */
	USART1 -> SR = 0 ;

}

void MUSART1_voidTransmit(u8 arr[])
{
	u8 i = 0;
	while(arr[i] != '\0')
	{
		USART1 -> DR = arr[i];
		/* Wait till transmission complete */
		/* while (((USART1 -> SR) & 0x40) == 0 ) ;  */
		while(GIT_BIT( USART1 -> SR , 6) == 0);
		i++;
	}

}

u8   MUSART1_u8Receive(void)
{
	u16 TimeOut = 0 ;
	u8 Loc_u8ReceivedData = 0 ;
	while(GIT_BIT( USART1 -> SR , 5) == 0)
	{
		TimeOut++ ;
		if(TimeOut == 2100)
		{
			break;
		}
	}
	if (Loc_u8ReceivedData == 0)
	{
		/* Masking */
		Loc_u8ReceivedData = 0xFF & (USART1 -> DR) ;
	}
	return(Loc_u8ReceivedData) ;

}
