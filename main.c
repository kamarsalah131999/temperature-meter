/*
 * coding.c
 *
 * Created: 2/03/2022 9:18:26 PM
 * Author : kamar salah
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util//delay.h>
#include "ADC driver.h"
#include "LCD driver.h"


unsigned short temperature;
int main(void)
{
	LCD_vinit();                                                                       // inthalizing lcd
	ADC_vint();                                                                        // intializing ADC
	
	LCD_vsend_sring(" temperature = ");
	
	while (1) 
    {
		temperature = (ADC_u16read() *0.25 );
		
		/* if temperature one digit */
		if (temperature <10)
		{ 
			LCD_vmove_cursor( 1,13);
			LCD_vsend_char(temperature + 48);                                           // 48 decimal 0f 0 in ASCII code
			LCD_vsend_char(0XDF);                                                        // ASCII code of degree 
			LCD_vsend_char('c');
			LCD_vsend_char(0x20);                                                        // free space

		}
		 /* if temperture consists of two digit */
		 else if (temperature<100)
		 {
			 LCD_vmove_cursor(1,13);
			 LCD_vsend_char((temperature/10)+48);                                       // writing in seconed digit
			 LCD_vsend_char((temperature%10)+48);                                        // writing in frist digit
			 LCD_vsend_char(0XDF);                                                        
			 LCD_vsend_char('c');
			 LCD_vsend_char(0x20);
		 }
		 /* if temperture consists of three  digit */
		 else if (temperature>100)
		 {
			 LCD_vmove_cursor(1,13);
			 LCD_vsend_char((temperature/100)+48);                                // writing the number in third digit
			 LCD_vsend_char(((temperature/10)%10)+48);                           // writing the number in seconed  digit
			 LCD_vsend_char((temperature%10)+48);                               // writing the number in frist digit
			 LCD_vsend_char(0XDF);                                                        
			 LCD_vsend_char('c');
			 LCD_vsend_char(0x20);
		 }
		 
		 else 
		 {
		 }
    }
}

