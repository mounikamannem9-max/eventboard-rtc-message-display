#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define ADCLK 3000000
#define CLK_DIV ((PCLK/ADCLK)-1)

#define CH0 0X01
#define CH1 0x02
#define CH2 0x04
#define CH3 0x80

#define PDN_BIT (1<<21)
#define CLKDIV (CLK_DIV<<8)
#define START_CONV (1<<24)

#define RESULT 6
#define DONE_BIT 31

#define FN1 0
#define FN2 1
#define FN3 3
#define FN4 4


#define AIN0 0X00400000
#define AIN1 0X01000000
#define AIN2 0X04000000
#define AIN3 0X10000000

