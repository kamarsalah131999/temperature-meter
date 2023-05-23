/*
 * ADC driver.c
 *
 * Created: 26/02/2022 11:54:28 PM
 *  Author: kamar salah
 */ 
#include <avr/io.h>
#include "macros.h"

void ADC_vint (void)
{
	SET_BIT (ADCSRA,ADEN);                                                            //	Enable ADC 
	SET_BIT (ADMUX,REFS0);                                                            // configurate voltage refrence = voltage of microcontloer = 5V 
	
	// adjust ADC clock to 125 khz by division =64  >> clock od micro= 8 MHZ >> clock of ADC = 8MHZ/64
	SET_BIT (ADCSRA,ADPS2);
	SET_BIT (ADCSRA,ADPS1);
}

unsigned short ADC_u16read (void)
{
	unsigned short read_val;
	SET_BIT (ADCSRA,ADSC);                                                           // enable ADC to start convirsion 
	SET_BIT (ADCSRA,ADATE);                                                          // enable auto triger 
	while (READ_BIT (ADCSRA,ADSC) ==0);                                               // if ADSC become 0 means the conversion is ended and start read the output                                                       
	
	/*position till ADIF become 1 and start ISR code but we dont enable any interruput */
    SET_BIT(ADCSRA,ADIF); // clear ADIF
    
	/* read output from ADC convrsion  */
	read_val = ADCL;
	read_val |= (ADCH<<8);
	return read_val;                                                     
}
