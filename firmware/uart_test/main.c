/*
Title: uart_test
Description: Sends characters over UART
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../_includes/squadron.c"

void main()
{
	init_uart();

	char data[] = "Hello from VSDSQUADRON\n";

	while (1)
	{
		write_data(data);
	}
}
