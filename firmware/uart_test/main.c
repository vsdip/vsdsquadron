#include "../includes/squadron.c"

void main()
{
	init();
	init_uart();

	char data[] = "Hello from VSDSQUADRON";

	while (1)
	{
		write_data(data);
	}
}
