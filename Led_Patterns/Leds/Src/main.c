#include "bit.h"
#include "type.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "interface.h"
#include "KPD_interface.h"
#include "lcd_interface.h"
#include "timer_interface.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#define APP_HIGH_MODE 230
#define APP_MED_MODE 150
#define APP_LOW_MODE 100
//Global Array to present PIN_ID.........
u8 APP_au8PinId []= {
		DIO_u8_PIN0,
		DIO_u8_PIN1,
		DIO_u8_PIN2,
		DIO_u8_PIN3,
		DIO_u8_PIN4,
		DIO_u8_PIN5,
		DIO_u8_PIN6,
		DIO_u8_PIN7
};
//Creating Queue to hold pressed key.........
xQueueHandle APP_xBuffer;

//Prototypes of the two tasks............
void APP_KeypadTask(void *pvParameters);
void APP_voidLedPattern(void *pvParameters);

int main(void)
{
	//Initiate ........
	DIO_u8IntialDirection();
	DIO_u8IntialValue();
	LCD_voidInitial();
	TMR0_voidInitial();
	LCD_voidSendStr("Pattern : ");

	//Creating Queue to hold pressed key.........
	APP_xBuffer = xQueueCreate(1,sizeof(u8));
	if(APP_xBuffer == NULL)
	{
		LCD_voidClear();
		LCD_voidSendStr("QueueErr");
	}
	//Creating the two tasks.......
	xTaskCreate(&APP_KeypadTask,NULL,configMINIMAL_STACK_SIZE,NULL,1,NULL);
	xTaskCreate(&APP_voidLedPattern,NULL,configMINIMAL_STACK_SIZE,NULL,2,NULL);
	//Start Scheduler........
	vTaskStartScheduler();
	return 0;
}


void APP_KeypadTask(void *pvParameters)
{
	    u8 Local_u8Key = KPD_u8_KEY_NOT_PRESSED;  //Create local key and initate it with any number
	    while(1)
	    {
	        KPD_u8GetKey(&Local_u8Key);
	        if (Local_u8Key != KPD_u8_KEY_NOT_PRESSED)  //Check if the key pressed
	        {
	            LCD_voidSendChar(Local_u8Key); //Write the key on LCD
	            LCD_voidGoToXY(LCD_u8_LINE0,10); //Go back with curser to prevent incrementation
		        if(xQueueSend(APP_xBuffer,&Local_u8Key,portMAX_DELAY)!=pdPASS) //send the pressed key to Queue
		        {
		        	LCD_voidClear();
		        	LCD_voidSendStr("QueueSendErr");
		        	while(1);
		        }
	        }
	        vTaskDelay(1);
	    }
}
void APP_voidLedPattern(void *pvParameters)
{
	u8 Local_u8Pattern = 0xff;
	while(1)
	{
		if(xQueueReceive(APP_xBuffer,&Local_u8Pattern,portMAX_DELAY)==pdPASS) //Recieve the Queue value
		{
			switch(Local_u8Pattern) // Switch on the Queue Value to choose pattern
			{
				case'1': //Flashing every 500ms
				{
					while(1)
					{
						DIO_u8SetPortValue(DIO_u8_PORTD,0xff);
						vTaskDelay(500);
						DIO_u8SetPortValue(DIO_u8_PORTD,0x00);
						vTaskDelay(500);
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '1')
					    {
							break;
					    }
					}
					break;
				}
				case'2'://Shiffting left every 250ms
				{
					while(1)
					{
						for(u8 Local_u8Iteration=0 ; Local_u8Iteration<8 ; Local_u8Iteration++)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_HIGH);
							vTaskDelay(250);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_LOW);
						}
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '2')
					    {
							break;
					    }
					}
						break;
				}
				case'3'://Shiffting right every 250ms
				{
					while(1)
					{
						for(s8 Local_s8Iteration=7 ; Local_s8Iteration>=0 ; Local_s8Iteration--)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8Iteration],DIO_u8_PIN_HIGH);
							vTaskDelay(250);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8Iteration],DIO_u8_PIN_LOW);
						}
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '3')
					    {
							break;
					    }
					}
						break;
				}
				case'4': //LEDs Shifting Left every 250 msec with varying brightness
				{
					u8 Local_u8OCR0=APP_LOW_MODE;
					DIO_u8SetPinDirection(DIO_u8_PORTB,DIO_u8_PIN3,DIO_u8_PIN_OUTPUT); //to configre generation of pwm
					DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN_HIGH); //to put pulse on the transistor base for the bypass
					DIO_u8SetPortDirection(DIO_u8_PORTD,DIO_u8_PORT_INPUT); //to switch between portA current and take current from pwm instead
					while(1)
					{
						TMR_voidSetOcr0Value(&Local_u8OCR0);
						for(u8 Local_u8Iteration=5 ; Local_u8Iteration<8 ; Local_u8Iteration++)
						{
							DIO_u8SetPinValue(DIO_u8_PORTB,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_LOW);
							vTaskDelay(100);
							DIO_u8SetPinValue(DIO_u8_PORTB,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_HIGH);
						}
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '4')
					    {
							DIO_u8SetPinDirection(DIO_u8_PORTB,DIO_u8_PIN3,DIO_u8_PIN_INPUT); /* to reverse all that is done in the beginning*/
							DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN_LOW);/* to reverse all that is done in the beginning*/
							DIO_u8SetPortDirection(DIO_u8_PORTD,DIO_u8_PORT_OUTPUT);/* to reverse all that is done in the beginning*/
							DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN5,DIO_u8_PIN_LOW);/* to reverse all that is done in the beginning*/
							DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN_LOW);/* to reverse all that is done in the beginning*/
							DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN7,DIO_u8_PIN_LOW);/* to reverse all that is done in the beginning*/
							break;
					    }
					}
						break;
				}
				case'5'://Diverging every 300ms
				{
					while(1)
					{
						for(s8 Local_s8FirstIteration=3,Local_s8SecondIteration=4; Local_s8FirstIteration>=0 && Local_s8SecondIteration<=7;
								Local_s8FirstIteration--,Local_s8SecondIteration++)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8FirstIteration],DIO_u8_PIN_HIGH);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8SecondIteration],DIO_u8_PIN_HIGH);
							vTaskDelay(300);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8FirstIteration],DIO_u8_PIN_LOW);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8SecondIteration],DIO_u8_PIN_LOW);
						}
						DIO_u8SetPortValue(DIO_u8_PORTD,0x00);
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '5')
					    {
							break;
					    }
					}
						break;
				}
				case'6'://Converging every 300ms
				{
					while(1)
					{
						for(s8 Local_s8FirstIteration=0,Local_s8SecondIteration=7; Local_s8FirstIteration<=3 && Local_s8SecondIteration>=4;
								Local_s8FirstIteration++,Local_s8SecondIteration--)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8FirstIteration],DIO_u8_PIN_HIGH);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8SecondIteration],DIO_u8_PIN_HIGH);
							vTaskDelay(300);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8FirstIteration],DIO_u8_PIN_LOW);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8SecondIteration],DIO_u8_PIN_LOW);
						}
						DIO_u8SetPortValue(DIO_u8_PORTD,0x00);
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '6')
					    {
							break;
					    }
					}
						break;
				}

				case'7'://PingPong effect every 250ms
				{
					while(1)
					{
						for(u8 Local_u8Iteration=0 ; Local_u8Iteration<8 ; Local_u8Iteration++)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_HIGH);
							vTaskDelay(250);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_LOW);
						}
						for(s8 Local_s8Iteration=7 ; Local_s8Iteration>=0 ; Local_s8Iteration--)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8Iteration],DIO_u8_PIN_HIGH);
							vTaskDelay(250);
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_s8Iteration],DIO_u8_PIN_LOW);
						}
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '7')
					    {
							break;
					    }
					}
						break;
				}
				case'8'://snake effect every 300ms
				{
					while(1)
					{
						for(u8 Local_u8Iteration=0 ; Local_u8Iteration<8 ; Local_u8Iteration++)
						{
							DIO_u8SetPinValue(DIO_u8_PORTD,APP_au8PinId[Local_u8Iteration],DIO_u8_PIN_HIGH);
							vTaskDelay(300);
						}
						DIO_u8SetPortValue(DIO_u8_PORTD,0x00);
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
						if (Local_u8Pattern > '8')
					    {
							break;
					    }
					}
						break;
				}
				case'9'://All LEDs pulsing from 1-5 volts, then from 5-1 volt every 1000 msec
				{
					DIO_u8SetPinDirection(DIO_u8_PORTB,DIO_u8_PIN3,DIO_u8_PIN_OUTPUT); //to configre generation of pwm
					DIO_u8SetPinDirection(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN_OUTPUT); //to put pulse on the transistor base for the bypass
					DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN_HIGH); //to put pulse on the transistor base for the bypass
					DIO_u8SetPortDirection(DIO_u8_PORTD,DIO_u8_PORT_INPUT); //to switch between portA current and take current from pwm instead
					while(1)
					{
						for(u8 Local_u8Iteration=0;Local_u8Iteration<255;Local_u8Iteration++)
						{
							TMR_voidSetOcr0Value(&Local_u8Iteration);
							vTaskDelay(4);
						}
						for(u8 Local_u8Iteration=255;Local_u8Iteration>0;Local_u8Iteration--)
						{
							TMR_voidSetOcr0Value(&Local_u8Iteration);
							vTaskDelay(4);
						}
						xQueueReceive(APP_xBuffer, &Local_u8Pattern,0);
					}
						break;
				}
		   }
		}
		else
		{
			LCD_voidSendStr("QueueRecieveErr");
		}
		vTaskDelay(1);
	}
}






