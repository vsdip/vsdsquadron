#include "../includes/squadron.c"

void main()
{
	init_uart();

	char data[] = "Hello from VSDSQUADRON\n";

	while (1)
	{
		write_data(data);
	}
}
