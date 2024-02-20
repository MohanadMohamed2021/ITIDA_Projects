/***********************************************************/
/* Author    : Ahmed Assaf                                 */
/* Date      : 21 Sep 2020                                 */
/* Version   : V01                                         */
/***********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

void HTFT_voidInitialize   (void)
{
	/* Reset Pulse */
	GPIO_voidsetPinValue(TFT_RST_PIN,HIGH);
	STK_voidSetBusyWait(100,TIME_US);
	GPIO_voidsetPinValue(TFT_RST_PIN,LOW);
	STK_voidSetBusyWait(1,TIME_US);
	GPIO_voidsetPinValue(TFT_RST_PIN,HIGH);
	STK_voidSetBusyWait(100,TIME_US);
	GPIO_voidsetPinValue(TFT_RST_PIN,LOW);
	STK_voidSetBusyWait(100,TIME_US);
	GPIO_voidsetPinValue(TFT_RST_PIN,HIGH);
	STK_voidSetBusyWait(120000,TIME_US);
	
	/* Sleep Out Command */
	voidWriteCommand(0x11);
	
	/* Wait 150 ms */
	STK_voidSetBusyWait(150000,TIME_US);
	
	/* Color Mode Command */
	voidWriteCommand(0x3A);
	voidWriteData   (0x05);
	
	/* Display On Command */
	voidWriteCommand(0x29);
}


void HTFT_voidDisplayImage (const u16* Copy_Image)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);
	
	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_Image[counter] >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_Image[counter] & 0x00ff;
		voidWriteData(Data);
	}


}

static void voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp;
	
	/* Set A0 Pin to Low */
	GPIO_voidsetPinValue(TFT_A0_PIN,LOW);
	
	/* Send Command over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Command,&Local_u8Temp);
}

static void voidWriteData   (u8 Copy_u8Data)
{
	u8 Local_u8Temp;
	
	/* Set A0 Pin to High */
	GPIO_voidsetPinValue(TFT_A0_PIN,HIGH);
	
	/* Send data over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Data,&Local_u8Temp);
}

void TFT_voidDrawRectangle (u16 copy_u16X ,u16 copy_u16Y , u16 copy_u16Width , u16 copy_u16Hight , u16 copy_u16Color ){
	u16 loacal_u16EndX = copy_u16X + copy_u16Width - 1;
	u16 loacal_u16EndY = copy_u16Y + copy_u16Hight - 1;

	/* Set area of addresses */
	voidSetAddress(copy_u16X ,loacal_u16EndX,copy_u16Y ,loacal_u16EndY );

	/* Draw the Rectangle*/
	for (u16 i = 0 ; i < (copy_u16Width *copy_u16Hight ) ; i++){
		voidSetColour(copy_u16Color);
	}
}


void TFT_voidFillDisplay (u16 copy_u16Colour){
	TFT_voidDrawRectangle(0 , 0 ,TFT_MAX_X , TFT_MAX_Y , copy_u16Colour);
}

static void voidSetColour(u16 copy_u16Colour)
{

	/* Write pixel */
	u8 high_byte = (copy_u16Colour >> 8);
	u8 low_byte = (copy_u16Colour & 0xff);
	voidWriteData(high_byte);
	voidWriteData(low_byte);
}
static void voidSetAddress (u16 copy_u16StartX ,u16 copy_u16EndX , u16 copy_u16StartY , u16 copy_u16EndY)
{
	if ( (copy_u16StartX < TFT_MAX_X ) && (copy_u16StartY < TFT_MAX_Y )){
		/* Set x Address */
		voidWriteCommand(0x2A);
		/* Start byte */
		voidWriteData((copy_u16StartX >> 8));  // MS byte
		voidWriteData(copy_u16StartX);

		/* Stop byte */
		voidWriteData((copy_u16EndX >> 8));
		voidWriteData(copy_u16EndX);

		/* Set x Address */
		voidWriteCommand(0x2B);
		/* Start byte */
		voidWriteData((copy_u16StartY >> 8));  // MS byte
		voidWriteData(copy_u16StartY);
		/* Stop byte */
		voidWriteData((copy_u16EndY >> 8));
		voidWriteData(copy_u16EndY);

		/* RAM write */
		voidWriteCommand(0x2C);
	}
}
static void voidDrawPixel (u16 copy_u16X , u16 copy_u16Y , u16 copy_u16Colour)
{
	if ( (copy_u16X < TFT_MAX_X ) && (copy_u16Y < TFT_MAX_Y )){

		/* Set address of the pixel */
		voidSetAddress(copy_u16X  , copy_u16X+1 , copy_u16Y , copy_u16Y+1);

		/* Write pixel colour */
		voidSetColour(copy_u16Colour);
	}
}
void TFT_voidPrintText(s8 *copy_s8Text , u16 copy_u16X , u16 copy_u16Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor)
{
	while (*copy_s8Text){
		TFT_voidPrintChar(*copy_s8Text , copy_u16X ,copy_u16Y ,copy_u8Size ,copy_u16Color,copy_u16BackColor );
		copy_u16X += (copy_u8Size *TFT_CHARACTER_WIDTH)  ;
		copy_s8Text++;
	}
}
void TFT_voidPrintChar(s8 copy_s8Char , u16 copy_u16X , u16 copy_u16Y, u8 copy_u8Size , u16 copy_u16Color , u16 copy_u16BackColor)
{
	/* Get array index */
	u8 local_u8CharIndex = 0 ;
	if (( copy_s8Char >= ' ' )){
		local_u8CharIndex = copy_s8Char - 32 ;
	}

	/* Background */
	TFT_voidDrawRectangle( copy_u16X, copy_u16Y ,copy_u8Size*TFT_CHARACTER_WIDTH ,copy_u8Size*TFT_CHARACTER_HIGHT ,copy_u16BackColor);

	for (u8 i = 0; i <TFT_CHARACTER_WIDTH ; i++ ){
		for (u8 j = 0 ; j <TFT_CHARACTER_HIGHT ; j++){
			if (TFT_font[local_u8CharIndex][i] & (1 << j)){
				if (copy_u8Size == 1){
					voidDrawPixel(copy_u16X+i , copy_u16Y+j , copy_u16Color);
				}
				else {
					u16 local_x = copy_u16X+(i*copy_u8Size) ;
					u16 local_y = copy_u16Y+(j*copy_u8Size) ;
					TFT_voidDrawRectangle( local_x, local_y ,copy_u8Size ,copy_u8Size ,copy_u16Color);
				}
			}
		}
	}
}

