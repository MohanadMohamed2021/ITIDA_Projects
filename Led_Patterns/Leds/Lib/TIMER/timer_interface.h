#ifndef timer_interface
#define timer_interface

#define TMR_u8_Normal   0
#define TMR_u8_CTC      1

#define TMR_u8_TIMER_PIE_ON        1
#define TMR_u8_TIMER_PIE_OFF       0

#define TMR_u8_COMPARE_PIE_ON         1
#define TMR_u8_COMPARE_PIE_OFF        0


void TMR0_voidInitial(void);

u8 TMR_u8SetCallBack(u8 Copy_u8Mode,void (*Copy_pf)(void));

void TMR0_voidControlPIE(u8 Copy_u8TimerPIEState,u8 Copy_u8ComparePIEState);

void TMR1_voidInitial(void);

void TMR_voidSetOcr0Value(u8 *Copy_pu8Ocr0Value);

void TMR_voidSetOcr1aValue(u8 *Copy_pu8Ocr1aValue);

void TMR1_voidReadTMR1Reg(u16 *Copy_pu16TMR1Reg);

void TMR1_voidEnableICU(void);

void TMR1_voidDisableICU(void);

u8 TMR1_u8GetTotalPeriod(u32 *Copy_pu32TotalPeriod); 

u8 TMR1_u8GetDutyCycle(u8 *Copy_pu8DutyCycle); 

#endif
