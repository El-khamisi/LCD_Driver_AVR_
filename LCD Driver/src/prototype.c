/*
 * prototype.c
 *
 * Created: 2020-03-13 10:31:14 AM
 *  Author: M.El5amisi
 */ 

#include "prototype.h"


void setup_pin(uint8_t port , uint8_t pin, uint8_t state)
{
	if (state)
	{
		*(uint8_t *) (port)|= (1<<pin);
	}
	else
	*(uint8_t *) (port) &= ~(1<<pin);
	
}

void write_pin(uint8_t port , uint8_t pin, uint8_t state)
{
	if (state)
	{
		*(uint8_t *) (port+1)|= (1<<pin);
	}
	else
	*(uint8_t *) (port+1)&= ~(1<<pin);
	
}



volatile void initialization()
{
	_delay_ms(15);
	
	setup_pin(RS_port, RS_pin, output);
	setup_pin(Enable_port, Enable_pin, output);
	
	write_pin(Enable_port, Enable_pin, low);
	
	
	if (mod == 8)
	{
		*(volatile uint8_t *)(Data_Pins)=0xff;
		*(volatile uint8_t *)(Data_Pins+1)=0x00;
		
		command(0x38);
	}
	else if (mod == 4)
	{
		*(volatile uint8_t *)(Data_Pins) = 0xf0;
		*(volatile uint8_t *)(Data_Pins+1)=0x00;
		command(0x33);
		command(0x32);
		command(0x28);
	}
	
	command(0x0e);
	command(0x01);
	_delay_ms(2);
	command(0x06);
	
	
}





volatile void command (volatile uint8_t cmd)
{
	
	write_pin(RS_port, RS_pin, low);
	if (mod == 8)
	{
	*(volatile uint8_t *)(Data_Pins+1)=cmd;
	
	
	}
	else if (mod == 4)
	{
		
		*(volatile uint8_t *)(Data_Pins+1)=cmd & 0xf0 ;
		write_pin(Enable_port, Enable_pin, high);
		_delay_us(1);
		write_pin(Enable_port, Enable_pin, low);
		_delay_us(100);
		*(volatile uint8_t *)(Data_Pins+1)=cmd<<4 ;
	}
	write_pin(Enable_port, Enable_pin, high);
	_delay_us(1);
	write_pin(Enable_port, Enable_pin, low);
	_delay_us(100);
	
}


volatile void charr ( volatile char c)
{
	write_pin(RS_port, RS_pin, high);
	

	if (mod == 8)
	{
		*(volatile uint8_t *)(Data_Pins+1)=c;
		
	}
	else if (mod == 4)
	{
		*(volatile uint8_t *)(Data_Pins+1)=c & 0xf0;	
		write_pin(Enable_port, Enable_pin, high);
		_delay_us(1);
		write_pin(Enable_port, Enable_pin, low);
		_delay_us(100);
		*(volatile uint8_t *)(Data_Pins+1)=c<<4;
		
	}
	write_pin(Enable_port, Enable_pin, high);
	_delay_us(1);
	write_pin(Enable_port, Enable_pin, low);
	_delay_us(100);
}


volatile void text(char *str)
{
	uint8_t i=0;
	while(str[i] != 0 )
	{
		charr(str[i]);
		if (i == 15)
		{
			command(0xC0);
		}
		i++;
	}
	command(0xF);
}
