#include "../includes/defs.h"
#include "../includes/gpio_config/gpio_config_io.c"

void set_registers() {

    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL; // Rx
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT; // Tx

}

void write_data(char *data) {   
    int index = 0;
    while (data[index] != '\0') {
        reg_uart_data = data[index];
        while (reg_uart_txfull == 1) {
            /* Do nothing */
        }
        delay(5000);
        index++;
    }
}



// void read_data(char *buf, int size) {
//     int index = 0;
//     char c;
//     while (index < size - 1) {
//         while (reg_uart_rxempty == 1) {
//             /* Do nothing */
//         }
//         c = reg_uart_data;
//         if (c == '\r' || c == '\n') {
//             break;
//         }
//         buf[index] = c;
//         index++;
//     }
//     buf[index] = '\0';
// }

void main()
{
    
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    #ifdef reg_uart_clkdiv
        reg_uart_clkdiv=10417; // If the speed is 12.5MHz then this would give 9600 baud
    #endif
    reg_uart_enable=1;

    reg_mprj_xfer = 1; 

    set_registers();
    reg_mprj_datah = 0;
    reg_mprj_datal = 0;
    gpio_config_io();

    // char buf[100];

    while(1)
    {
        char data[] = "Hello from VSDSQUADRON";

        // write_data(data);
        // write_data("\nPlease enter an input: ");
        // read_data(buf, 100);

        // write_data("The entered data is ");
        // write_data(buf);
        // write_data("\n");
    }

}
