/*
Title: blink_led
Description: Toggles all GPIOs at a specified frequency
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../_includes/squadron.c"

void main()
{
	init(); // Initialise VSDsquadron

	while (1)
	{
		reg_gpio_out = 0x0;			 // Management gpio High
		reg_mprj_datal = 0x00000000; // GPIO0 - GPIO31 High
		reg_mprj_datah = 0x00000000; // GPIO32 - GPIO37 High

		delay(10000000); // Delay 1 Second

		reg_gpio_out = 0x1;			 // Management gpio Low
		reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
		reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

		delay(10000000); // Delay 1 Second
	}
}
