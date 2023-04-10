#include "../includes/squadron.c"

void main()
{
	init(); // Initialise VSDsquadron

	reg_gpio_out = 0x1;			 // Management gpio Low
	reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
	reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

	int data = 0;

	while (1)
	{

		data = (reg_mprj_datal & 0x00000002) > 1;

		data = (~data) & 0x00000001;

		reg_mprj_datal = reg_mprj_datal | data;
	}
}
