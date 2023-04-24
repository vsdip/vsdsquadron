/*
Title: count_led
Description: 4 bit binary up counter on onboard GPIO 0,37,1,2
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/
#include "../includes/squadron.c"

// GPIO 0,37,1,2

void main()
{
	init();						 // Initialize VSDSquadron
	reg_gpio_out = 0x1;			 // Management gpio Low
	reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
	reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

	int count = 0x00000000;

	while (1)
	{

		display(count);
		count++;
		delay(5000000);
	}
}
