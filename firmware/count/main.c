#include "../includes/squadron.c"

void main()
{
	init();
	init_uart();

	char data[] = "Hello from VSDSQUADRON\n";

	while (1)
	{
		char count_to = 9;

		for (int i = 0; i <= count_to; i++)
		{
			write_data(count_to);
		}

		
	}
}
