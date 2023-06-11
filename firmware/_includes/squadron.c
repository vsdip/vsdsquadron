#include "defs.h"
#include "gpio_config/gpio_config_io.c"

void display(int count) // Function to display the data on the four Led's
{
    count = ~count;              // Invert count as Led's are Active Low
    reg_mprj_datal = count;      // Shift data to be accurately displayed on GPIO1 and GPIO2
    reg_mprj_datah = count << 2; // Shift data to be accurately displayed on GPIO37 (reg_mprj_datah bit 6)
}