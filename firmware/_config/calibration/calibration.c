#include "../defs.h"
//---------------------------------------------------------
// calibration.c
//---------------------------------------------------------
// Run the calibration routine on MPW-two hardware.
// Calibration algorithm:
//   For each channel:
//   1) Attempt to apply an input-only configuration
//	(DM=001) based on the number of independent and
//	dependent hold violations in the channels up to the
//	channel under test, and assuming an independent hold
//	violation for the channel under test.
//   2)	Read back the value at that channel 
//      a) If 1, then flag an independent hold violation
//	   and move to the next channel
//	b) If 0, then flag a dependent hold violation
//	   and repeat for the current channel
//	   i) If 1, then move to the next channel
//	   ii) If 0, then flag an error at the channel
//---------------------------------------------------------
// NOTE:
// Throughout the program, "l" ("left") refers to the
// left-hand side of the chip (GPIO 37 to 19) while "r"
// ("right") refers to the right-hand side of the chip
// (GPIO 0 to 18).  In the clock routines below, values
// are for "clocklr";  e.g., "clock10" sets the left side
// to 1 and the right side to 0.
//---------------------------------------------------------
// calibration_test2 differs from calibration_test in that
// it uses the built-in automatic programming instead of
// the bit-bang programming.
//---------------------------------------------------------
// NOTE:  The logic in the caravel control block
// inadvertently disables the weak pull-up and pull-down
// modes, so a "1" value can only be read if the channel
// is driven externally.  The MPW-two boards were shipped
// with an STMicro Nucleo board, so the Nucleo can be used
// with some handshaking to apply the needed signals to
// the GPIO pins.
//---------------------------------------------------------
// Calibration sequence (handshaking with Nucleo board)
// (1)  Power up:  Chip sets GPIO[0] to input and
//	GPIO[37] to output.  Sets GPIO[37] value to "0".
// (2)  Chip waits on Nucleo to set GPIO[0] high
// (3)  Nucleo sets all pins on low side (GPIO[0-18]) to
//	output and sets all values to "1".
// (4)  Chip sees GPIO[0] go high, starts low side
//	calibration.
// (5)  When low-side calibration is done, chip sets
//	GPIO[37] high.
// (6)  Nucleo sees GPIO[37] go high, releases all low
//	side pins except for GPIO[0], sets all high side
//	pins to output with value 1 (note that both
//	chip and Nucleo drive GPIO[37] to the same value)
// (7)  Nucleo sets GPIO[0] low, then releases it (sets
//	it to an input).
// (8)  Chip sees GPIO[0] go low, releases GPIO[37] (sets
//	it to an input), sets GPIO[0] to an output with
//	value 0.
// (9)  Chip starts high side calibration.
// (10) When high-side calibration is done, chip sets
//	GPIO[0] high.
// (11) Nucleo sees GPIO[0] go high and releases all
//	pins except for GPIO[37].
// (12) Nucleo sets GPIO[37] low then releases it (sets
//	it to an input).
// (13) Chip sees GPIO[37] go low and sets outputs to
//	mark where dependent violations are located
//	(note that GPIO[37] and GPIO[0] never have 
//	dependent violations so are always zero).
// (14) Nucleo sees GPIO[0] go low and reads result.
//
// Additional (not done yet) handshaking:
// (15) Chip waits some specified time for the Nucleo
//	to read the result, then sets GPIO[0] high
//	and sets all channels high that are "unknown"
//	due to an error occurring.
//---------------------------------------------------------
// For diagnostic purposes, the management GPIO pin
// (LED on the development board) is toggled with a
// number of pulses indicating the step in the
// sequence above.
//---------------------------------------------------------
// Written by Tim Edwards
// February 11, 2023
//---------------------------------------------------------

// Recast the reg_mprj_io_* definitions as a single
// parameterized definition, for simplicity

#define reg_mprj_io(i) (*(volatile uint32_t*)(0x26000024 + (i << 2)))

void runtime_configure()
{
    // NOTE:  Registers need to be set so that the housekeeping module
    // knows which direction the single-pin interface to each GPIO
    // goes.  Only the input disable bit (bit 3) is relevant.  If
    // input disable = 0, then the channel is assumed to be input;
    // if input disable = 1, then the channel is assumed to be output.

    int i;
    for (i = 0; i < 38; i++) reg_mprj_io(i) = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
}

void final_configure()
{
    int i;
    for (i = 0; i < 38; i++) reg_mprj_io(i) = GPIO_MODE_MGMT_STD_OUTPUT;
}

void disabled_configure()
{
    int i;
    for (i = 0; i < 38; i++) reg_mprj_io(i) = 0;
}

void gpio_toggle(int num)
{
    int i, j;

    // Delay with #num pulses
    
    for (j = 0; j < 500; j++);
    for (i = 0; i < num; i++)
    {
	reg_gpio_out = 1; // High
	for (j = 0; j < 500; j++);
	reg_gpio_out = 0; // Low
	for (j = 0; j < 500; j++);
    }
    for (j = 0; j < 1000; j++);
}

//---------------------------------------------------------
// Main program
//---------------------------------------------------------

void main()
{
    unsigned char channel, i;
    unsigned char repeat, error, result;
    int value, j, k;
    int dep_l, dep_r;	// Distribution of dependent hold violations

    /* Main config storage is up to 247 bits of data */
    unsigned char config_data[31];

    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;
    reg_gpio_out = 0;	// Diagnostic low, LED on

    reg_mprj_datah = 0;
    reg_mprj_datal = 0;

    // Make sure that the user project is not doing anything.
    reg_la2_data = 2;			// reset is applied
    reg_la0_oenb = reg_la0_iena = 0;
    reg_la1_oenb = reg_la1_iena = 0;
    reg_la2_oenb = reg_la2_iena = 0;
    reg_la3_oenb = reg_la3_iena = 0;
    reg_la2_oenb = reg_la2_iena = 3;	// reset and clock are manual.

    reg_gpio_out = 1; // OFF

    dep_l = dep_r = 0;

    // Step (1).  Set GPIO[0] to input, GPIO[37] to output, all others disabled.
    // gpio_toggle(1);
    disabled_configure();
    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // Step (2).  Wait for Nucleo to set GPIO[0] high
    // gpio_toggle(2);
    while ((reg_mprj_datal & 0x1) == 0);

    // Step (3) happens on the Nucleo side.
    
    // Step (4).  Start calibration low (right) side.
    // gpio_toggle(4);
    for (i = 0; i < 31; i++)
	config_data[i] = 0;

    // Starting bit sequence is 1000000000011 in channel 0,
    config_data[1] = 0x10;
    config_data[0] = 0x03;

    repeat = 0;
    error = 0;
    for (channel = 0; channel <= 18; channel++) {

	// Set the configuration (8 bit data into 13 bit registers)
	reg_mprj_io_0  = (config_data[0] >> 0)  | (config_data[1] << 8);
	reg_mprj_io_1  = (config_data[1] >> 5)  | (config_data[2] << 3) | (config_data[3] << 11);
	reg_mprj_io_2  = (config_data[3] >> 2)  | (config_data[4] << 6);
	reg_mprj_io_3  = (config_data[4] >> 7)  | (config_data[5] << 1) | (config_data[6] << 9);
	reg_mprj_io_4  = (config_data[6] >> 4)  | (config_data[7] << 4) | (config_data[8] << 12);
	reg_mprj_io_5  = (config_data[8] >> 1)  | (config_data[9] << 7);
	reg_mprj_io_6  = (config_data[9] >> 6)  | (config_data[10] << 2) | (config_data[11] << 10);
	reg_mprj_io_7  = (config_data[11] >> 3) | (config_data[12] << 5);
	reg_mprj_io_8  = (config_data[13] >> 0) | (config_data[14] << 8);
	reg_mprj_io_9  = (config_data[14] >> 5) | (config_data[15] << 3) | (config_data[16] << 11);
	reg_mprj_io_10 = (config_data[16] >> 2) | (config_data[17] << 6);
	reg_mprj_io_11 = (config_data[17] >> 7) | (config_data[18] << 1) | (config_data[19] << 9);
	reg_mprj_io_12 = (config_data[19] >> 4) | (config_data[20] << 4) | (config_data[21] << 12);
	reg_mprj_io_13 = (config_data[21] >> 1) | (config_data[22] << 7);
	reg_mprj_io_14 = (config_data[22] >> 6) | (config_data[23] << 2) | (config_data[24] << 10);
	reg_mprj_io_15 = (config_data[24] >> 3) | (config_data[25] << 5);
	reg_mprj_io_16 = (config_data[26] >> 0) | (config_data[27] << 8);
	reg_mprj_io_17 = (config_data[27] >> 5) | (config_data[28] << 3) | (config_data[29] << 11);
	reg_mprj_io_18 = (config_data[29] >> 2) | (config_data[30] << 6);

	// Now load the configuration
	reg_mprj_xfer = 1;
	while (reg_mprj_xfer == 1);
	runtime_configure();

	// Read the value of the channels (right)
	value = reg_mprj_datal;

	// What is the value in the channel under test?
	value &= 0x7ffff;
 	result = ((value & (1 << channel)) == 0) ? 0 : 1;

	// If the result is zero, and we are repeating, then flag an error and stop.

	if (repeat == 1) {
            if (result == 0) {
		gpio_toggle(4);
		error = 1;
		break;
	    }
	    else {
		repeat = 0;
		// Record the dependent hold violation
		dep_r |= (1 << channel);
		// Result good, continue on to next channel
		gpio_toggle(3);
	    }
	}
	else {
	    if (result == 0) {
		repeat = 1;
		/* Add '1' in front of any '1' bit */
		for (i = 30; i > 0; i--) {
		    config_data[i] |= (config_data[i] << 1) | (config_data[i - 1] >> 7);
		}
		config_data[0] |= (config_data[0] << 1);
		gpio_toggle(2);
	    }
	    else {
		gpio_toggle(1);
	    }
	}
	if (repeat == 1) channel--;
	else {
	    /* Shift all bits up 12 for next test */
	    for (i = 29; i > 0; i--) {
	    	config_data[i + 1] = (config_data[i] << 4) | (config_data[i - 1] >> 4);
	    }
	    config_data[1] = (config_data[0] << 4);
	    config_data[0] = 0;
	}
    }

    // Clear the lower channels (only need to do the last few used)
    reg_mprj_io_18 = 0;
    reg_mprj_io_17 = 0;
    reg_mprj_io_16 = 0;
    reg_mprj_io_15 = 0;

    // Reset the programming to leave GPIO[0] as an input
    disabled_configure();
    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // Step (5).  Right side calibration complete.  Set GPIO[37] high.
    // gpio_toggle(5);
    reg_mprj_datah = 0x20;

    // Step (6) and (7):  Nucleo is preparing for left side calibration.
    // gpio_toggle(6);
    while ((reg_mprj_datal & 0x1) == 1);

    // Step (8). Chip releases GPIO[37] and sets GPIO[0] as output.
    // gpio_toggle(8);
    reg_mprj_datal = 0x0;
    disabled_configure();
    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // Step (9). Repeat calibration on the left side.
    // gpio_toggle(9);
    for (i = 0; i < 31; i++)
	config_data[i] = 0;

    // Starting bit sequence is 1000000000011 in channel 37,
    config_data[1] = 0x10;
    config_data[0] = 0x03;

    repeat = 0;
    error = 0;
    for (channel = 0; channel <= 18; channel++) {

	// Set the configuration (8 bit data into 13 bit registers)
	reg_mprj_io_37 = (config_data[0] >> 0)  | (config_data[1] << 8);
	reg_mprj_io_36 = (config_data[1] >> 5)  | (config_data[2] << 3) | (config_data[3] << 11);
	reg_mprj_io_35 = (config_data[3] >> 2)  | (config_data[4] << 6);
	reg_mprj_io_34 = (config_data[4] >> 7)  | (config_data[5] << 1) | (config_data[6] << 9);
	reg_mprj_io_33 = (config_data[6] >> 4)  | (config_data[7] << 4) | (config_data[8] << 12);
	reg_mprj_io_32 = (config_data[8] >> 1)  | (config_data[9] << 7);
	reg_mprj_io_31 = (config_data[9] >> 6)  | (config_data[10] << 2) | (config_data[11] << 10);
	reg_mprj_io_30 = (config_data[11] >> 3) | (config_data[12] << 5);
	reg_mprj_io_29 = (config_data[13] >> 0) | (config_data[14] << 8);
	reg_mprj_io_28 = (config_data[14] >> 5) | (config_data[15] << 3) | (config_data[16] << 11);
	reg_mprj_io_27 = (config_data[16] >> 2) | (config_data[17] << 6);
	reg_mprj_io_26 = (config_data[17] >> 7) | (config_data[18] << 1) | (config_data[19] << 9);
	reg_mprj_io_25 = (config_data[19] >> 4) | (config_data[20] << 4) | (config_data[21] << 12);
	reg_mprj_io_24 = (config_data[21] >> 1) | (config_data[22] << 7);
	reg_mprj_io_23 = (config_data[22] >> 6) | (config_data[23] << 2) | (config_data[24] << 10);
	reg_mprj_io_22 = (config_data[24] >> 3) | (config_data[25] << 5);
	reg_mprj_io_21 = (config_data[26] >> 0) | (config_data[27] << 8);
	reg_mprj_io_20 = (config_data[27] >> 5) | (config_data[28] << 3) | (config_data[29] << 11);
	reg_mprj_io_19 = (config_data[29] >> 2) | (config_data[30] << 6);

	// Now load the configuration
	reg_mprj_xfer = 1;
	while (reg_mprj_xfer == 1);
	runtime_configure();

	// Read the value of the channels (left)
	value = (reg_mprj_datah << 13) | (reg_mprj_datal >> 19);

	// What is the value in the channel under test?
 	result = ((value & (1 << (18 - channel))) == 0) ? 0 : 1;

	// If the result is zero, and we are repeating, then flag an error and stop.

	if (repeat == 1) {
            if (result == 0) {
		gpio_toggle(4);
		error = 1;
		break;
	    }
	    else {
		repeat = 0;
		// Record the dependent hold violation
		dep_l |= (1 << channel);
		// Result good, continue on to next channel
		gpio_toggle(3);
	    }
	}
	else {
	    if (result == 0) {
		repeat = 1;
		/* Add '1' in front of any '1' bit */
		for (i = 30; i > 0; i--) {
		    config_data[i] |= (config_data[i] << 1) | (config_data[i - 1] >> 7);
		}
		config_data[0] |= (config_data[0] << 1);
		gpio_toggle(2);
	    }
	    else {
		gpio_toggle(1);
	    }
	}
	if (repeat == 1) channel--;
	else {
	    /* Shift all bits up 12 for next test */
	    for (i = 29; i > 0; i--) {
	    	config_data[i + 1] = (config_data[i] << 4) | (config_data[i - 1] >> 4);
	    }
	    config_data[1] = (config_data[0] << 4);
	    config_data[0] = 0;
	}
    }

    // Reset the programming to leave GPIO[37] as an input
    disabled_configure();
    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // Step (10). Calibration is complete.  Set GPIO[0] high.
    // gpio_toggle(10);
    reg_mprj_datal = 0x1;

    // Step (11) and (12).  Nucleo prepares for read-back
    // gpio_toggle(11);
    while ((reg_mprj_datah & 0x20) != 0);

    // Step (13).  Set up all channels for output based on the pattern of
    // dependent and independent hold violations.

    // gpio_toggle(13);

    for (i = 0; i < 31; i++)
	config_data[i] = 0;

    for (channel = 19; channel > 0; channel--) {

	/* Move configuration up by 12 bits */
	for (i = 29; i > 0; i--) {
	    config_data[i + 1] = (config_data[i] << 4) | (config_data[i - 1] >> 4);
	}
	config_data[1] = config_data[0] << 4;
	config_data[0] = 0;

	/* If there is a dependent hold violation, then add 1 to the end of 1 chains */
	if ((dep_r & (1 << channel)) != 0)
	{
	    for (i = 30; i > 0; i--) {
		config_data[i] |= (config_data[i] << 1) | (config_data[i - 1] >> 7);
	    }
	}

	/* Add new configuration at low end */
    	config_data[1] |= 0x18;
    	config_data[0] = 0x01;
    }

    // Set the configuration (8 bit data into 13 bit registers)
    reg_mprj_io_0  = (config_data[0] >> 0)  | (config_data[1] << 8);
    reg_mprj_io_1  = (config_data[1] >> 5)  | (config_data[2] << 3) | (config_data[3] << 11);
    reg_mprj_io_2  = (config_data[3] >> 2)  | (config_data[4] << 6);
    reg_mprj_io_3  = (config_data[4] >> 7)  | (config_data[5] << 1) | (config_data[6] << 9);
    reg_mprj_io_4  = (config_data[6] >> 4)  | (config_data[7] << 4) | (config_data[8] << 12);
    reg_mprj_io_5  = (config_data[8] >> 1)  | (config_data[9] << 7);
    reg_mprj_io_6  = (config_data[9] >> 6)  | (config_data[10] << 2) | (config_data[11] << 10);
    reg_mprj_io_7  = (config_data[11] >> 3) | (config_data[12] << 5);
    reg_mprj_io_8  = (config_data[13] >> 0) | (config_data[14] << 8);
    reg_mprj_io_9  = (config_data[14] >> 5) | (config_data[15] << 3) | (config_data[16] << 11);
    reg_mprj_io_10 = (config_data[16] >> 2) | (config_data[17] << 6);
    reg_mprj_io_11 = (config_data[17] >> 7) | (config_data[18] << 1) | (config_data[19] << 9);
    reg_mprj_io_12 = (config_data[19] >> 4) | (config_data[20] << 4) | (config_data[21] << 12);
    reg_mprj_io_13 = (config_data[21] >> 1) | (config_data[22] << 7);
    reg_mprj_io_14 = (config_data[22] >> 6) | (config_data[23] << 2) | (config_data[24] << 10);
    reg_mprj_io_15 = (config_data[24] >> 3) | (config_data[25] << 5);
    reg_mprj_io_16 = (config_data[26] >> 0) | (config_data[27] << 8);
    reg_mprj_io_17 = (config_data[27] >> 5) | (config_data[28] << 3) | (config_data[29] << 11);
    reg_mprj_io_18 = (config_data[29] >> 2) | (config_data[30] << 6);

    for (i = 0; i < 31; i++)
	config_data[i] = 0;

    for (channel = 19; channel > 0; channel--) {
	/* Move configuration up by 12 bits */
	for (i = 29; i > 0; i--) {
	    config_data[i + 1] = (config_data[i] << 4) | (config_data[i - 1] >> 4);
	}
	config_data[1] = config_data[0] << 4;
	config_data[0] = 0;

	/* If there is a dependent hold violation, then add 1 to the end of 1 chains */
	if ((dep_l & (1 << channel)) != 0)
	{
	    for (i = 30; i > 0; i--) {
		config_data[i] |= (config_data[i] << 1) | (config_data[i - 1] >> 7);
	    }
	}

	/* Add new configuration at low end */
    	config_data[1] |= 0x18;
    	config_data[0] = 0x01;
    }

    // Set the configuration (8 bit data into 13 bit registers)
    reg_mprj_io_37 = (config_data[0] >> 0)  | (config_data[1] << 8);
    reg_mprj_io_36 = (config_data[1] >> 5)  | (config_data[2] << 3) | (config_data[3] << 11);
    reg_mprj_io_35 = (config_data[3] >> 2)  | (config_data[4] << 6);
    reg_mprj_io_34 = (config_data[4] >> 7)  | (config_data[5] << 1) | (config_data[6] << 9);
    reg_mprj_io_33 = (config_data[6] >> 4)  | (config_data[7] << 4) | (config_data[8] << 12);
    reg_mprj_io_32 = (config_data[8] >> 1)  | (config_data[9] << 7);
    reg_mprj_io_31 = (config_data[9] >> 6)  | (config_data[10] << 2) | (config_data[11] << 10);
    reg_mprj_io_30 = (config_data[11] >> 3) | (config_data[12] << 5);
    reg_mprj_io_29 = (config_data[13] >> 0) | (config_data[14] << 8);
    reg_mprj_io_28 = (config_data[14] >> 5) | (config_data[15] << 3) | (config_data[16] << 11);
    reg_mprj_io_27 = (config_data[16] >> 2) | (config_data[17] << 6);
    reg_mprj_io_26 = (config_data[17] >> 7) | (config_data[18] << 1) | (config_data[19] << 9);
    reg_mprj_io_25 = (config_data[19] >> 4) | (config_data[20] << 4) | (config_data[21] << 12);
    reg_mprj_io_24 = (config_data[21] >> 1) | (config_data[22] << 7);
    reg_mprj_io_23 = (config_data[22] >> 6) | (config_data[23] << 2) | (config_data[24] << 10);
    reg_mprj_io_22 = (config_data[24] >> 3) | (config_data[25] << 5);
    reg_mprj_io_21 = (config_data[26] >> 0) | (config_data[27] << 8);
    reg_mprj_io_20 = (config_data[27] >> 5) | (config_data[28] << 3) | (config_data[29] << 11);
    reg_mprj_io_19 = (config_data[29] >> 2) | (config_data[30] << 6);

    // Now load the configuration
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
    final_configure();

    // End with an output pattern indicating the configuration

    value = 0;
    for (i = 0; i < 19; i++) {
	if ((dep_l & (1 << i)) != 0)
	    value |= 0x1;
	value <<= 1;
    }
    // Keep low bit set so Nucleo continues waiting
    reg_mprj_datal = dep_r | (value << 18) | 0x1;
    reg_mprj_datah = (value >> 14);

    // Clear low bit to let Nucleo know that result is ready.
    reg_mprj_datal &= 0xfffffffe;

    // gpio_toggle(14);
    while (1) {
	/* Rapid blink */
	reg_gpio_out = 0;
	for (j = 0; j < 10000; j++);
	reg_gpio_out = 1;
	for (j = 0; j < 10000; j++);
    }	
}

