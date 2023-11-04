#include "bit.h"
#include "type.h"
#include "interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#define APP_u8_PIN_NUMBERS 8
int main()
{
    u8 Local_u8Iterator;
    DIO_u8IntialDirection();
    u8 Local_au8PinId[APP_u8_PIN_NUMBERS] = {DIO_u8_PIN0,DIO_u8_PIN1,DIO_u8_PIN2,DIO_u8_PIN3,DIO_u8_PIN4,DIO_u8_PIN5,DIO_u8_PIN6,DIO_u8_PIN7};
    while(1)
    {
        for (Local_u8Iterator=0 ; Local_u8Iterator < APP_u8_PIN_NUMBERS ; Local_u8Iterator++)
        {
            DIO_u8SetPinValue(DIO_u8_PORTA,Local_au8PinId[Local_u8Iterator],DIO_u8_PIN_HIGH);
            _delay_ms(500);
        }
        DIO_u8SetPortValue(DIO_u8_PORTA,DIO_u8_PORT_LOW);
    }
    return 0;
}