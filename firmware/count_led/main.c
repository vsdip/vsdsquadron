#include "../includes/squadron.c"

void display(int count)
{
	count = ~count;
	reg_mprj_datal = ((count >> 1) & 0xfffffffe) | (count & 1);
	reg_mprj_datah = count << 4; // 000000
}

void main()
{
	init();
	reg_gpio_out = 0x0;
	reg_mprj_datah = 0xffffffff;
	reg_mprj_datal = 0xffffffff;

	int count = 0x00000000;

	while (1)
	{

		display(count);
		count++;
		delay(5000000);
	}
}
