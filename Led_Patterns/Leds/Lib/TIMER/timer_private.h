#ifndef timer_private
#define timer_private

#define OCR0_u8_REG *((volatile u8*)0x5C)

#define TIMSK_u8_REG *((volatile u8*)0x59)

#define TIFR_u8_REG *((volatile u8*)0x58)

#define TCNT_u8_REG *((volatile u8*)0x52)

#define TCCR0_u8_REG *((volatile u8*)0x53)

#define TCCR1A_u8_REG *((volatile u8*)0x4F) 

#define TCCR1B_u8_REG *((volatile u8*)0x4E)

#define TCNT1LH_u16_REG *((volatile u16*)0x4C)

#define OCR1ALH_u16_REG *((volatile u16*)0x4A)

#define OCR1BLH_u16_REG *((volatile u16*)0x48)

#define ICR1LH_u16_REG *((volatile u16*)0x46)

#define  TMR_u8_NORMAL_MODE     0
#define  TMR_u8_CTC_MODE        1
#define  TMR_u8_PWM_MODE        2
#define  TMR_u8_FAST_PWM_MODE   3




#define TMR_u8_NON_INVERTING   0
#define TMR_u8_INVERTING       1





#endif