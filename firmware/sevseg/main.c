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

g	f	com	a	b

e	d	com	c	dp

Caravel Mapping

37	36	35	0	1	2	3
c	d	e	g	f	a	b

##############################################################*/

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
