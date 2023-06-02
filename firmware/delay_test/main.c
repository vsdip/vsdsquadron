/*
Title: delay_test
Description: Code to test the delay function
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

/*
# Can be found at vsdsquadron_software/firmware/_includes/gpio_config/gpio_config_io.c
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

#include "../_includes/squadron.c"

void set_registers()
{
	reg_mprj_io_0 = GPIO_MODE_MGMT_STD_ANALOG;
	reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_2 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_3 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_4 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_5 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_7 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_8 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_9 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;

	reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
}

void init()
{
    // Management GPIO Configuration
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    // User GPIO Configuration
    set_registers();
    gpio_config_io();
}

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
