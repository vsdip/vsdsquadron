#include "../includes/squadron.c"

void display(int count) // Function to display the data on the four Led's
{
	count = ~count;												// Invert count as Led's are Active Low
	reg_mprj_datal = ((count >> 1) & 0xfffffffe) | (count & 1); // Shift data to be accurately displayed on GPIO1 and GPIO2
	reg_mprj_datah = count << 4;								// Shift data to be accurately displayed on GPIO37 (reg_mprj_datah bit 6)
}

void main()
{
	init();						 // Initialize VSDSquadron
	reg_gpio_out = 0x1;			 // Management gpio Low
	reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
	reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

	int count = 0x00000000;

	while (1)
	{

		display(count);
		count++;
		delay(5000000);
	}
}
