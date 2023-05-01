/*
Title: line_follower
Description: Line following robot
Date: 2023-04-24
Author: Yatharth
License: MIT License
*/

#include "../_includes/defs.h"
#include "../_includes/gpio_config/gpio_config_io.c"

void set_registers()
{
    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_2 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_3 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_4 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_7 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_8 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_9 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;

    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
}

void init()
{
    // Management GPIO Configuration
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    // User GPIO Configuration
    set_registers();
    gpio_config_io();
}

void forward()
{
    reg_mprj_datal = 5;
}

void right()
{
    reg_mprj_datal = 9;
}

void left()
{
    reg_mprj_datal = 6;
}

void stop()
{
    reg_mprj_datal = 0;
}

void test()
{
    while (1)
    {
        forward();
        delay(10000000);
        right();
        delay(10000000);
        left();
        delay(10000000);
        stop();
        delay(10000000);
    }
}

void main()
{
    init(); // Initialise VSDsquadron

    // IO0 - Motor Right A
    // IO1 - Motor Right B

    // IO2 - Motor Left A
    // IO3 - Motor Left B

    // IO36 - Sensor Right
    // IO37 - Sensor Left

    while (1)
    {
        if (((reg_mprj_datah >> 4) & 3) == 0) // if Right Sensor and Left Sensor are at White color then it will call forword function
        {
            forward();
        }
        if (((reg_mprj_datah >> 4) & 3) == 1) // if Right Sensor is Black and Left Sensor is White then it will call turn Right function
        {
            right();
        }
        if (((reg_mprj_datah >> 4) & 3) == 2) // if Right Sensor is White and Left Sensor is Black then it will call turn Left function
        {
            left();
        }
        if (((reg_mprj_datah >> 4) & 3) == 3) // if Right Sensor and Left Sensor are at Black color then it will call Stop function
        {
            stop();
        }
    }
}