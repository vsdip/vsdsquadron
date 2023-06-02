#include "defs.h"
#include "gpio_config/gpio_config_io.c"

void display(int count) // Function to display the data on the four Led's
{
    count = ~count;              // Invert count as Led's are Active Low
    reg_mprj_datal = count;      // Shift data to be accurately displayed on GPIO1 and GPIO2
    reg_mprj_datah = count << 2; // Shift data to be accurately displayed on GPIO37 (reg_mprj_datah bit 6)
}
// ---------UART--------------

void init_uart()
{
    // Management GPIO Configuration
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;
    reg_gpio_out = 0x1; // Management gpio Low

// UART Clock Configuration
#ifdef reg_uart_clkdiv
    reg_uart_clkdiv = 10417; // If the speed is 12.5MHz then this would give 9600 baud
#endif

    // UART PIN Configuration

    reg_uart_enable = 1;
    reg_mprj_xfer = 1;

    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL; // Rx
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;       // Tx

    gpio_config_io();
}

void write_data(char *data)
{
    int index = 0;
    while (data[index] != '\0')
    {
        reg_uart_data = data[index];
        while (reg_uart_txfull == 1)
        {
            /* Do nothing */
        }
        delay(5000);
        index++;
    }
}
