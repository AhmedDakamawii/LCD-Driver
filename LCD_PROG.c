

#define LOW 0
#define HIGH 1
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_INTERFACE.h"
#include "LCD_CFG.h"
#include <AVR/delay.h>



void LCD_VidIntialize (void)
{ DIO_VidsetportDirection(DATA_PORT , 0b11111111);
 DIO_VidsetpinDirection(CONTROL_PORT,RS,1);
 DIO_VidsetpinDirection(CONTROL_PORT,RW,1);
 DIO_VidsetpinDirection(CONTROL_PORT,EN,1);

						_delay_ms(35);
						LCD_VidsendCommend (FUN_SET);
							_delay_ms(1);
							LCD_VidsendCommend (LCD_DISPLAY);
							_delay_ms(1);
							LCD_VidsendCommend (LCD_CLEAR);
						 _delay_ms(2);
						 
	
}

void LCD_VidsendData (u8 COPY_U8Data)
{
	DIO_VidsetpinValue(CONTROL_PORT,RS,1);
	DIO_VidsetpinValue(CONTROL_PORT,RW,0);
	DIO_VidsetportValue(DATA_PORT,COPY_U8Data);
	DIO_VidsetpinValue(CONTROL_PORT,EN,1);
							 _delay_ms(1);
	DIO_VidsetpinValue(CONTROL_PORT,EN,0);
								 _delay_ms(2);

}

void LCD_VidsendCommend (u8 COPY_U8Commend)
{
	DIO_VidsetpinValue(CONTROL_PORT,RS,0);
	DIO_VidsetpinValue(CONTROL_PORT,RW,0);
	DIO_VidsetportValue(DATA_PORT,COPY_U8Commend);
	
	DIO_VidsetpinValue(CONTROL_PORT,EN,1);
								 _delay_ms(1);
		DIO_VidsetpinValue(CONTROL_PORT,EN,0);
								 _delay_ms(2);

}

void LCD_VidsendDataString (u8* COPY_U8Arrdata )
{
	u8* ptr= COPY_U8Arrdata;
	for (int i=0; ptr[i]!='\0' ;i++)
	{
		LCD_VidsendData(ptr[i]);
	}
}
	
	
void LCD_VidsendIntger (u32 COPY_U32NUM)
{
	u8 j=0;
	u8 mod=0;

u32 arr2[10]={0};
while (COPY_U32NUM > 0)
{
	 mod =COPY_U32NUM % 10;
	arr2[j]=mod;
	j++;
	COPY_U32NUM=COPY_U32NUM / 10;
}
arr2[j]='\0';
while (j > 0)
{
	j--;
LCD_VidsendData(arr2[j]+'0');

}


}
void LCD_SetCursor (u8 r,u8 c)
{  u8 temp;
	if (r==1)
	{
		temp=0x80+c-1;
		LCD_VidsendCommend(temp);
	}
	if (r==2)
	{
		temp=0xc0+c-1;
		LCD_VidsendCommend(temp);
	}
	
	
}



