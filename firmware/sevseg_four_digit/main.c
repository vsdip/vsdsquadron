/*
Title: sevseg_four_digit
Description: up counter on four digit seven segment display
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../includes/squadron.c"

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

D1	A	F	D2	D3	B

E	D	DP	c	G	D4

Caravel Mapping

34	35	36	37
D4	D3	D2	D1

6	5	4	3	2	1	0
A	B	C	D	E	F	G
##############################################################*/

int sevseg(int num, int digit) // Function to display on segment
{
	int hex;
	int loc;
	switch (num)
	{
	case 0:
		hex = 0b01111110;
		break;
	case 1:
		hex = 0b00110000;
		break;
	case 2:
		hex = 0b01101101;
		break;
	case 3:
		hex = 0b01111001;
		break;
	case 4:
		hex = 0b00110011;
		break;
	case 5:
		hex = 0b01011011;
		break;
	case 6:
		hex = 0b01011111;
		break;
	case 7:
		hex = 0b01110000;
		break;
	case 8:
		hex = 0b01111111;
		break;
	case 9:
		hex = 0b01111011;
		break;
	case 10:
		hex = 0b01110111;
		break;
	case 11:
		hex = 0b00011111;
		break;
	case 12:
		hex = 0b01001110;
		break;
	case 13:
		hex = 0b00111101;
		break;
	case 14:
		hex = 0b01001111;
		break;
	case 15:
		hex = 0b01000111;
		break;
	}
	loc =
		hex = ~hex;
	reg_mprj_datal = hex;
	reg_mprj_datah = 0xFFFFFFFF & (1 << (digit + 1));
}

void main()
{
	init();						 // Initialize VSDSquadron
	reg_gpio_out = 0x1;			 // Management gpio Low
	reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
	reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

	int count = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	// while (1)
	// {
	// 	for (int i = 1; i < 5; i++)
	// 	{
	// 		for (int j = 0; j < 16; j++)
	// 		{
	// 			sevseg(j, i);
	// 			delay(5000000);
	// 		}
	// 	}
	// }

	while (1)
	{
		a = count / 1000;
		b = (count % 1000) / 100;
		c = (count % 100) / 10;
		d = count % 10;
		for (int k; k < 1000; k++)
		{
			sevseg(a, 4);
			delay(10000);
			sevseg(b, 3);
			delay(10000);
			sevseg(c, 3);
			delay(10000);
			sevseg(d, 1);
			delay(10000);
		}

		count++;
	}
}
