/*
Title: sevseg_single_digit 
Description: 4 bit up counter on single digit seven segment display
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../_includes/squadron.c"

/*##########################################################################
Sevensegment mapping
	a
   ---
f |   | b
  | g |
   ---
e |   | c
  |   |
   ---  . dp
	d

Sevensegment Pinout

g	f	com	a	b

e	d	com	c	dp

Caravel Mapping

37	36	35	0	1	2	3
c	d	e	g	f	a	b

##############################################################*/
void set_registers()
{
	reg_mprj_io_0 = GPIO_MODE_MGMT_STD_OUTPUT;
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

int sevseg(int num) // Function to display on segment
{
	int hex;

	switch (num)
	{
	case 0:
		hex = 0b01110111;
		break;
	case 1:
		hex = 0b01000001;
		break;
	case 2:
		hex = 0b00111011;
		break;
	case 3:
		hex = 0b01101011;
		break;
	case 4:
		hex = 0b01001101;
		break;
	case 5:
		hex = 0b01101110;
		break;
	case 6:
		hex = 0b01111110;
		break;
	case 7:
		hex = 0b01000011;
		break;
	case 8:
		hex = 0b01111111;
		break;
	case 9:
		hex = 0b01101111;
		break;
	case 10:
		hex = 0b01011111;
		break;
	case 11:
		hex = 0b01111100;
		break;
	case 12:
		hex = 0b00110110;
		break;
	case 13:
		hex = 0b01111001;
		break;
	case 14:
		hex = 0b00111110;
		break;
	case 15:
		hex = 0b00011110;
		break;
	}

	hex = ~hex;
	reg_mprj_datal = hex;
	reg_mprj_datah = hex >> 1;
}

void main()
{
	init();						 // Initialize VSDSquadron
	reg_gpio_out = 0x1;			 // Management gpio Low
	reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
	reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

	int count = 0;

	while (1)
	{
		sevseg(count);
		count++;
		delay(5000000);
		if (count == 16)
			count = 0;
	}
}
