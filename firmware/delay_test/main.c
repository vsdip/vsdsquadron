#include "../includes/squadron.c"

void main()
{
	init(); // Initialise VSDsquadron

	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			reg_mprj_datal = 0x00000000; // GPIO0 - GPIO31 High
			delay(i * 10000000);		 // Delay 1 Second
			reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low
			delay(i * 10000000);		 // Delay 1 Second
		}
	}
}
