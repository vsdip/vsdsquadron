/*
Title: uart_test
Description: Sends characters over UART
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../_includes/squadron.c"

#define UART_EV_TX 0x1
#define UART_EV_RX 0x2

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

bool has_char()
{
	return !reg_uart_rxempty;
}

void putchar(char x)
{
	// Wait until ready
	while (reg_uart_txfull)
		;

	// Write character
	reg_uart_data = x;

	// Wait until send completed
	while (reg_uart_txfull)
		;
}

char getchar()
{
	while (!has_char())
		;

	// Read the data
	uint8_t c = reg_uart_data;

	// Clear the data out of the FIFO
	reg_uart_ev_pend = UART_EV_RX;

	return c;
}

void main()
{
	init_uart();

	while (1)
	{
		char c = getchar();
		putchar(c);
	}
}