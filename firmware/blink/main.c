#include "../includes/squadron.c"

void main()
{
	init();

	while (1)
	{

		reg_mprj_datal = 0x00000000;
		reg_mprj_datah = 0x00000000;
		reg_gpio_out = 0x0;

		delay(1000000);

		reg_mprj_datal = 0xffffffff;
		reg_mprj_datah = 0xffffffff;
		reg_gpio_out = 0x1;

		delay(1000000);
	}
}
