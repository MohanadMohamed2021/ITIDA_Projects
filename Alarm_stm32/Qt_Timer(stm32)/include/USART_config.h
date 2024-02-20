/********************************************************************/
/*  Author	 : Mohamed Hamdy							 	        */
/*  Version	 : V01 													*/
/*	Date	 : 12 November 2020                                     */
/********************************************************************/

#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/******************************************************************************/
/* Write Port and pin in pairs -> port,pin */

/******************************************************************************/


/******************************************************************************/
/* Options : 
				USART_BAUD_RATE_9600_8MHZ
				USART_BAUD_RATE_115200_8MHZ
									*/

#define   USART_BAUD_RATE     	   USART_BAUD_RATE_115200_8MHZ

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_DISABLE
				USART_ENABLE
									*/
	
#define   USART_EN              		  USART_ENABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_8_DATA_BITS
				USART_9_DATA_BITS
									*/

#define   USART_WORD_LENGTH      	  USART_8_DATA_BITS

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_IDLE_LINE
				USART_ADDRESS_MARK
									*/

#define   USART_WAKE_UP            	  USART_IDLE_LINE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_PARITY_DISABLE
				USART_PARITY_ENABLE
									*/

#define   USART_PARITY_EN     		   USART_PARITY_DISABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_EVEN_PARITY
				USART_ODD_PARITY
									*/

#define   USART_PARITY_SELECTION        USART_EVEN_PARITY

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_PE_INTERRUPT_DISABLE
				USART_PE_INTERRUPT_ENABLE
									*/

#define   USART_PE_INTERRUPT     	  USART_PE_INTERRUPT_DISABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_TXE_INTERRUPT_DISABLE
				USART_TXE_INTERRUPT_ENABLE
									*/

#define   USART_TXE_INTERRUPT     	  USART_TXE_INTERRUPT_ENABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_TCIE_INTERRUPT_DISABLE
				USART_TCIE_INTERRUPT_ENABLE
									*/

#define   USART_TCIE_INTERRUPT     	  USART_TCIE_INTERRUPT_DISABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_RXNE_INTERRUPT_DISABLE
				USART_RXNE_INTERRUPT_ENABLE
									*/

#define   USART_RXNE_INTERRUPT     	  USART_RXNE_INTERRUPT_DISABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_IDLE_INTERRUPT_DISABLE
				USART_IDLE_INTERRUPT_ENABLE
									*/

#define   USART_IDLE_INTERRUPT     	  USART_IDLE_INTERRUPT_DISABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_TX_DISABLE
				USART_TX_ENABLE
									*/

#define   USART_TX_EN     	 		  USART_TX_ENABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_RX_DISABLE
				USART_RX_ENABLE
									*/

#define   USART_RX_EN     	 		  USART_RX_ENABLE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_RX_WAKEUP_ACTIVE
				USART_RX_WAKEUP_MUTE
									*/

#define   USART_RX_WAKEUP     	 	 USART_RX_WAKEUP_MUTE

/******************************************************************************/

/******************************************************************************/
/* Options : 
				USART_NO_BREAK_TRANSMITTED
				USART_SEND_BREAK
									*/

#define   USART_BREAK_SEND     	 	 USART_NO_BREAK_TRANSMITTED

/******************************************************************************/

#endif
