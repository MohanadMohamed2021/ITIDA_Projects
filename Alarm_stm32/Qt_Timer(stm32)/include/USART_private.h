/********************************************************************/
/*  Author	 : Mohamed Hamdy							 	        */
/*  Version	 : V01 													*/
/*	Date	 : 12 November 2020                                     */
/********************************************************************/

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

typedef struct
{
	volatile u32 SR   ;
	volatile u32 DR   ;
	volatile u32 BRR  ;
	volatile u32 CR1  ;
	volatile u32 CR2  ;
	volatile u32 CR3  ;
	volatile u32 GTPR ;
}USART_t;


/*  Base Address  */
#define USART1     ((volatile USART_t*) 0x40013800 )   



/*******************************************************/
#define USART_BAUD_RATE_9600_8MHZ		0x341
#define USART_BAUD_RATE_115200_8MHZ      0x45
/*******************************************************/
/*******************************************************/
/*************         USART_CR1            ************/
/*******************************************************/
#define USART_DISABLE                    0x00000000
#define USART_ENABLE						0x00002000
/*******************************************************/
#define USART_8_DATA_BITS 				0x00000000
#define USART_9_DATA_BITS				0x00001000
/*******************************************************/
#define USART_IDLE_LINE 					0x00000000
#define USART_ADDRESS_MARK				0x00000800
/*******************************************************/
#define USART_PARITY_DISABLE				0x00000000
#define USART_PARITY_ENABLE  		  	0x00000400
/*******************************************************/
#define USART_EVEN_PARITY      			0x00000000
#define USART_ODD_PARITY					0x00000200
/*******************************************************/
#define USART_PE_INTERRUPT_DISABLE 		0x00000000
#define USART_PE_INTERRUPT_ENABLE  		0x00000100
/*******************************************************/
#define USART_TXE_INTERRUPT_DISABLE 		0x00000000
#define USART_TXE_INTERRUPT_ENABLE  		0x00000080
/*******************************************************/
#define USART_TCIE_INTERRUPT_DISABLE 	0x00000000
#define USART_TCIE_INTERRUPT_ENABLE  	0x00000040
/*******************************************************/
#define USART_RXNE_INTERRUPT_DISABLE 	0x00000000
#define USART_RXNE_INTERRUPT_ENABLE  	0x00000020
/*******************************************************/
#define USART_IDLE_INTERRUPT_DISABLE 	0x00000000
#define USART_IDLE_INTERRUPT_ENABLE 		0x00000010
/*******************************************************/
#define USART_TX_DISABLE 				0x00000000
#define USART_TX_ENABLE 					0x00000008
/*******************************************************/
#define USART_RX_DISABLE   				0x00000000
#define USART_RX_ENABLE 					0x00000004
/*******************************************************/
#define USART_RX_WAKEUP_ACTIVE   		0x00000000
#define USART_RX_WAKEUP_MUTE 			0x00000002
/*******************************************************/
#define USART_NO_BREAK_TRANSMITTED   	0x00000000
#define USART_SEND_BREAK					0x00000001
/*******************************************************/
/*************         USART_CR2            ************/
/*******************************************************/

#endif
