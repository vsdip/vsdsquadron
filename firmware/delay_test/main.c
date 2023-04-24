/*
Title: delay_test
Description: Code to test the delay function
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

/*
# Can be found at vsdsquadron_software/firmware/includes/gpio_config/gpio_config_io.c
void delay(const int d)
{

	// Configure timer for a single-shot countdown
	reg_timer0_config = 0;
	reg_timer0_data = d;
	reg_timer0_config = 1;

	// Loop, waiting for value to reach zero
   reg_timer0_update = 1;  // latch current value
   while (reg_timer0_value > 0) {
		   reg_timer0_update = 1;
   }

}
*/

#include "../includes/squadron.c"

void main()
{
	init(); // Initialise VSDsquadron

	// while (1)
	// {
	// 	for (int i = 10000; i <= 100000; i+=10000)
	// 	{
	// 		reg_mprj_datal = 0x00000000; // GPIO0 - GPIO31 High
	// 		delay(i);		 // Delay
	// 		reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low
	// 		delay(i);		 // Delay
	// 	}
	// }

	while (1)
	{
		
			reg_mprj_datal = 0x00000000; // GPIO0 - GPIO31 High
			delay(10000);		 // Delay
			reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low
			delay(10000);		 // Delay
		
	}
}
