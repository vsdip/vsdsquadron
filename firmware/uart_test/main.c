/*
Title: uart_test
Description: Sends characters over UART
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../_includes/squadron.c"

void init_uart()
{
	// Management GPIO Configuration
	reg_gpio_mode1 = 1;
	reg_gpio_mode0 = 0;
	reg_gpio_ien = 1;
	reg_gpio_oe = 1;
	reg_gpio_out = 0x1; // Management gpio Low

// UART Clock Configuration
#ifdef reg_uart_clkdiv
	reg_uart_clkdiv = 10417; // If the speed is 12.5MHz then this would give 9600 baud
#endif

	// UART PIN Configuration

	reg_uart_enable = 1;
	reg_mprj_xfer = 1;

	reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL; // Rx
	reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;		 // Tx

	gpio_config_io();
}

void write_data(char *data)
{
	int index = 0;
	while (data[index] != '\0')
	{
		reg_uart_data = data[index];
		while (reg_uart_txfull == 1)
		{
			/* Do nothing */
		}
		delay(5000);
		index++;
	}
}

void main()
{
	init_uart();

	char data[] = "Hello from VSDSQUADRON\n";

	while (1)
	{
		write_data(data);
	}
}
