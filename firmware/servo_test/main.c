/*
Title: servo_test
Description: Rotation of servo motor - sending PWM signal through software
Date: 2023-04-24
Author: Bala Dhinesh & Gokul C
License: MIT License
*/

#include "../includes/squadron.c"

void main()
{
    init(); // Initialise VSDsquadron
    int t = 5000;
    int c = 1;
    int spd = 50;
    while (1)
    {
        reg_gpio_out = 0x0;          // Management gpio High
        reg_mprj_datal = 0xfffffff9; // GPIO0 - GPIO31 High
        // reg_mprj_datah = 0xffffffff; // GPIO32 - GPIO37 High

        delay(200000 - t); // Delay 1 Second
        // delay(t); // Delay 1 Second

        reg_gpio_out = 0x1; // Management gpio Low
        // reg_mprj_datah = 0xffffffff; // GPIO0 - GPIO31 Low
        reg_mprj_datal = 0xffffffff; // GPIO32 - GPIO37 Low

        delay(t); // Delay 1 Second
                  // delay(200000-t); // Delay 1 Second
        if (c)
            t += spd;
        else
            t -= spd;
        // delay(100000);
        if (t > 15000)
        {
            c = 0;
            spd += 25;
        }
        if (t < 5000)
        {
            c = 1;
            spd += 25;
        }
        if (spd > 200)
            spd = 50;
    }
}