#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DELAY.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"
#include "TFT_interface.h"

int main()
{
	u8 str,str_old=0;
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,IOPA_PERIPHERAL);
	RCC_voidEnableClock(RCC_APB2,IOPB_PERIPHERAL);
	RCC_voidEnableClock(RCC_APB2,USART1_PERIPHERAL);
	RCC_voidEnableClock(RCC_APB2,SPI1_PERIPHERAL);

	GPIO_voidSetPinMode(PORTB,PIN6,GPIO_OUTPUT_2MHZ_PP);
	GPIO_voidSetPinMode(PORTB,PIN7,GPIO_OUTPUT_2MHZ_PP);
	GPIO_voidSetPinMode(PORTB,PIN8,GPIO_OUTPUT_2MHZ_PP);

	GPIO_voidSetPinMode(PORTA,PIN11,GPIO_OUTPUT_2MHZ_PP);
	GPIO_voidSetPinMode(PORTA,PIN8,GPIO_OUTPUT_2MHZ_PP);
	//PIN 9 TX
	GPIO_voidSetPinMode(PORTA,PIN9,GPIO_OUTPUT_50MHZ_AFPP);
	//PIN 10 RX
	GPIO_voidSetPinMode(PORTA,PIN10,GPIO_INPUT_FLOATING);

	GPIO_voidSetPinMode(PORTA,1,0b0010);  /* A0   */
	GPIO_voidSetPinMode(PORTA,2,0b0010);  /* RST  */
	GPIO_voidSetPinMode(PORTA,5,0b1001);  /* CLK  */
	GPIO_voidSetPinMode(PORTA,7,0b1001);  /* MOSI */

	STK_voidInit();
	MSPI1_voidInit();
	HTFT_voidInitialize();
	MUSART1_voidInit();

	TFT_voidFillDisplay(TFT_WHITE);
	GPIO_voidsetPinValue(PORTA,PIN8,LOW);
	GPIO_voidsetPinValue(PORTA,PIN0,LOW);

	while(1)
	{
		str = MUSART1_u8Receive();
		if((str == '1'))
		{
			TFT_voidFillDisplay(TFT_WHITE);
			GPIO_voidsetPinValue(PORTA,PIN8,HIGH);
			TFT_voidPrintText("TIME",30,30,4,TFT_BLACK,TFT_WHITE);
			TFT_voidPrintText("OUT",30,60,4,TFT_RED,TFT_WHITE);
			break;
		}
	}
	while(1);
	return 0;
}
