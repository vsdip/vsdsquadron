//---------------------------------------------------------
// calibration_pretest.c
//
// Simulate the calibration routine.
// Calibration algorithm:
//   For each channel:
//   1) Attempt to apply an input weak pull-up configuration
//	(DM=010) based on the number of independent and
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
// Written by Tim Edwards
// Febrary 11, 2023
//---------------------------------------------------------

#include <stdio.h>

int reg_mprj_io_0 = 0;
int reg_mprj_io_1 = 0;
int reg_mprj_io_2 = 0;
int reg_mprj_io_3 = 0;
int reg_mprj_io_4 = 0;
int reg_mprj_io_5 = 0;
int reg_mprj_io_6 = 0;
int reg_mprj_io_7 = 0;
int reg_mprj_io_8 = 0;
int reg_mprj_io_9 = 0;
int reg_mprj_io_10 = 0;
int reg_mprj_io_11 = 0;
int reg_mprj_io_12 = 0;
int reg_mprj_io_13 = 0;
int reg_mprj_io_14 = 0;
int reg_mprj_io_15 = 0;
int reg_mprj_io_16 = 0;
int reg_mprj_io_17 = 0;
int reg_mprj_io_18 = 0;
int reg_mprj_io_19 = 0;
int reg_mprj_io_20 = 0;
int reg_mprj_io_21 = 0;
int reg_mprj_io_22 = 0;
int reg_mprj_io_23 = 0;
int reg_mprj_io_24 = 0;
int reg_mprj_io_25 = 0;
int reg_mprj_io_26 = 0;
int reg_mprj_io_27 = 0;
int reg_mprj_io_28 = 0;
int reg_mprj_io_29 = 0;
int reg_mprj_io_30 = 0;
int reg_mprj_io_31 = 0;
int reg_mprj_io_32 = 0;
int reg_mprj_io_33 = 0;
int reg_mprj_io_34 = 0;
int reg_mprj_io_35 = 0;
int reg_mprj_io_36 = 0;
int reg_mprj_io_37 = 0;

int reg_mprj_datal, reg_mprj_datah;

void runtime_configure()
{
    reg_mprj_io_0 &= 0x1fff;
    reg_mprj_io_1 &= 0x1fff;
    reg_mprj_io_2 &= 0x1fff;
    reg_mprj_io_3 &= 0x1fff;
    reg_mprj_io_4 &= 0x1fff;
    reg_mprj_io_5 &= 0x1fff;
    reg_mprj_io_6 &= 0x1fff;
    reg_mprj_io_7 &= 0x1fff;
    reg_mprj_io_8 &= 0x1fff;
    reg_mprj_io_9 &= 0x1fff;
    reg_mprj_io_10 &= 0x1fff;
    reg_mprj_io_11 &= 0x1fff;
    reg_mprj_io_12 &= 0x1fff;
    reg_mprj_io_13 &= 0x1fff;
    reg_mprj_io_14 &= 0x1fff;
    reg_mprj_io_15 &= 0x1fff;
    reg_mprj_io_16 &= 0x1fff;
    reg_mprj_io_17 &= 0x1fff;
    reg_mprj_io_18 &= 0x1fff;
    reg_mprj_io_19 &= 0x1fff;
    reg_mprj_io_20 &= 0x1fff;
    reg_mprj_io_21 &= 0x1fff;
    reg_mprj_io_22 &= 0x1fff;
    reg_mprj_io_23 &= 0x1fff;
    reg_mprj_io_24 &= 0x1fff;
    reg_mprj_io_25 &= 0x1fff;
    reg_mprj_io_26 &= 0x1fff;
    reg_mprj_io_27 &= 0x1fff;
    reg_mprj_io_28 &= 0x1fff;
    reg_mprj_io_29 &= 0x1fff;
    reg_mprj_io_30 &= 0x1fff;
    reg_mprj_io_31 &= 0x1fff;
    reg_mprj_io_32 &= 0x1fff;
    reg_mprj_io_33 &= 0x1fff;
    reg_mprj_io_34 &= 0x1fff;
    reg_mprj_io_35 &= 0x1fff;
    reg_mprj_io_36 &= 0x1fff;
    reg_mprj_io_37 &= 0x1fff;

    fprintf(stdout, "GPIO[0] = 0x%04x\n", reg_mprj_io_0);
    fprintf(stdout, "GPIO[1] = 0x%04x\n", reg_mprj_io_1);
    fprintf(stdout, "GPIO[2] = 0x%04x\n", reg_mprj_io_2);
    fprintf(stdout, "GPIO[3] = 0x%04x\n", reg_mprj_io_3);
    fprintf(stdout, "GPIO[4] = 0x%04x\n", reg_mprj_io_4);
    fprintf(stdout, "GPIO[5] = 0x%04x\n", reg_mprj_io_5);
    fprintf(stdout, "GPIO[6] = 0x%04x\n", reg_mprj_io_6);
    fprintf(stdout, "GPIO[7] = 0x%04x\n", reg_mprj_io_7);
    fprintf(stdout, "GPIO[8] = 0x%04x\n", reg_mprj_io_8);
    fprintf(stdout, "GPIO[9] = 0x%04x\n", reg_mprj_io_9);
    fprintf(stdout, "GPIO[10] = 0x%04x\n", reg_mprj_io_10);
    fprintf(stdout, "GPIO[11] = 0x%04x\n", reg_mprj_io_11);
    fprintf(stdout, "GPIO[12] = 0x%04x\n", reg_mprj_io_12);
    fprintf(stdout, "GPIO[13] = 0x%04x\n", reg_mprj_io_13);
    fprintf(stdout, "GPIO[14] = 0x%04x\n", reg_mprj_io_14);
    fprintf(stdout, "GPIO[15] = 0x%04x\n", reg_mprj_io_15);
    fprintf(stdout, "GPIO[16] = 0x%04x\n", reg_mprj_io_16);
    fprintf(stdout, "GPIO[17] = 0x%04x\n", reg_mprj_io_17);
    fprintf(stdout, "GPIO[18] = 0x%04x\n", reg_mprj_io_18);
    fprintf(stdout, "GPIO[19] = 0x%04x\n", reg_mprj_io_19);
    fprintf(stdout, "GPIO[20] = 0x%04x\n", reg_mprj_io_20);
    fprintf(stdout, "GPIO[21] = 0x%04x\n", reg_mprj_io_21);
    fprintf(stdout, "GPIO[22] = 0x%04x\n", reg_mprj_io_22);
    fprintf(stdout, "GPIO[23] = 0x%04x\n", reg_mprj_io_23);
    fprintf(stdout, "GPIO[24] = 0x%04x\n", reg_mprj_io_24);
    fprintf(stdout, "GPIO[25] = 0x%04x\n", reg_mprj_io_25);
    fprintf(stdout, "GPIO[26] = 0x%04x\n", reg_mprj_io_26);
    fprintf(stdout, "GPIO[27] = 0x%04x\n", reg_mprj_io_27);
    fprintf(stdout, "GPIO[28] = 0x%04x\n", reg_mprj_io_28);
    fprintf(stdout, "GPIO[29] = 0x%04x\n", reg_mprj_io_29);
    fprintf(stdout, "GPIO[30] = 0x%04x\n", reg_mprj_io_30);
    fprintf(stdout, "GPIO[31] = 0x%04x\n", reg_mprj_io_31);
    fprintf(stdout, "GPIO[32] = 0x%04x\n", reg_mprj_io_32);
    fprintf(stdout, "GPIO[33] = 0x%04x\n", reg_mprj_io_33);
    fprintf(stdout, "GPIO[34] = 0x%04x\n", reg_mprj_io_34);
    fprintf(stdout, "GPIO[35] = 0x%04x\n", reg_mprj_io_35);
    fprintf(stdout, "GPIO[36] = 0x%04x\n", reg_mprj_io_36);
    fprintf(stdout, "GPIO[37] = 0x%04x\n", reg_mprj_io_37);

    fprintf(stdout, "\n");
}

//---------------------------------------------------------
// Main program
//---------------------------------------------------------

int main()
{
    unsigned char channel, i;
    unsigned char repeat, error, result;
    int value;
    int dep_l, dep_r;

    /* Main config storate is up to 247 bits of data */
    unsigned char config_data[31];

    // reg_gpio_mode1 = 1;
    // reg_gpio_mode0 = 0;
    // reg_gpio_ien = 1;
    // reg_gpio_oe = 1;

    // reg_mprj_datah = 0;
    // reg_mprj_datal = 0;

    // Make sure that the user project is not doing anything.
    // reg_la2_data = 2;			// reset is applied
    // reg_la0_oenb = reg_la0_iena = 0;
    // reg_la1_oenb = reg_la1_iena = 0;
    // reg_la2_oenb = reg_la2_iena = 0;
    // reg_la3_oenb = reg_la3_iena = 0;
    // reg_la2_oenb = reg_la2_iena = 3;	// reset and clock are manual.

    // reg_gpio_out = 1; // OFF

    dep_l = dep_r = 0;

    /* Simulation */
    reg_mprj_datal = 1;
    reg_mprj_datah = 0;

    // Do left and right sides separately.  Start with the right side

    for (i = 0; i < 31; i++)
	config_data[i] = 0;

    // Starting bit sequence is 1000000000011 in channel 0,
    config_data[1] = 0x10;
    config_data[0] = 0x03;

    repeat = 0;
    error = 0;
    for (channel = 0; channel <= 18; channel++) {

	// Set the configuaration (8 bit data into 13 bit registers)
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

	/* Simulation */
	if (repeat == 0)
	    fprintf(stdout, "Right side test channel GPIO %d\n", channel);
	else
	    fprintf(stdout, "Right side re-test channel GPIO %d\n", channel);

	// Now load the configuration
	// reg_mprj_xfer = 1;
	// while (reg_mprj_xfer == 1);
	runtime_configure();

	// Read the value of the channels (right)
	value = reg_mprj_datal;

	// What is the value in the channel under test?
	value &= 0x7ffff;
 	result = ((value & (1 << channel)) == 0) ? 0 : 1;

	/* Simulation */
	fprintf(stdout, "Result is %d\n", result);

	// If the result is zero, and we are repeating, then flag an error and stop.

	if (repeat == 1) {
            if (result == 0) {
		error = 1;

		/* Simulation */
		fprintf(stdout, "Result is bad, test failed.\n");

		break;
	    }
	    else {
		repeat = 0;
		// Record the dependent hold violation
		dep_r |= (1 << channel);
		// Result good, continue on to next channel

		/* Simulation */
		fprintf(stdout, "Result is good, channel has dependent hold\n");
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

		/* Simulation */
		fprintf(stdout, "Result is bad, repeating assuming dependent hold\n");
	    }
	    else {
		/* Simulation */
		fprintf(stdout, "Result is good, channel has independent hold\n");
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

	/* Simulation */
	if (repeat == 1) {
	    reg_mprj_datal <<= 1;
	}
	else if ((channel > 12) || (channel < 1) || (channel == 6) || (channel == 9) ||
		(channel == 10)) {
	    reg_mprj_datal <<= 1;
	}
    }

    // Clear the lower channels (only need to do the last few used)
    reg_mprj_io_18 = 0;
    reg_mprj_io_17 = 0;
    reg_mprj_io_16 = 0;
    reg_mprj_io_15 = 0;

    // Repeat for the left side.

    /* Simulation */
    reg_mprj_datal = 0;
    reg_mprj_datah = 0x20;

    for (i = 0; i < 31; i++)
	config_data[i] = 0;

    // Starting bit sequence is 1000000000011 in channel 37,
    config_data[1] = 0x10;
    config_data[0] = 0x03;

    repeat = 0;
    error = 0;
    for (channel = 0; channel <= 18; channel++) {

	// reg_gpio_out = 0; // ON

	// Set the configuaration (8 bit data into 13 bit registers)
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

	/* Simulation */
	if (repeat == 0)
	    fprintf(stdout, "Left side test channel GPIO %d\n", 37 - channel);
	else
	    fprintf(stdout, "Left side re-test channel GPIO %d\n", 37 - channel);

	// Now load the configuration
	// reg_mprj_xfer = 1;
	// while (reg_mprj_xfer == 1);
	runtime_configure();

	// Read the value of the channels (left)
	value = (reg_mprj_datah << 13) | (reg_mprj_datal >> 19);

	// What is the value in the channel under test?
 	result = ((value & (1 << (18 - channel))) == 0) ? 0 : 1;

	/* Simulation */
	fprintf(stdout, "Result is %d\n", result);

	// If the result is zero, and we are repeating, then flag an error and stop.

	if (repeat == 1) {
            if (result == 0) {
		error = 1;

		/* Simulation */
		fprintf(stdout, "Result is bad, test failed.\n");
		break;
	    }
	    else {
		repeat = 0;
		// Record the dependent hold violation
		dep_l |= (1 << channel);
		// Result good, continue on to next channel

		/* Simulation */
		fprintf(stdout, "Result is good, channel has dependent hold\n");
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

		/* Simulation */
		fprintf(stdout, "Result is bad, repeating assuming dependent hold\n");
	    }
	    else {
		/* Simulation */
		fprintf(stdout, "Result is good, channel has independent hold\n");
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

	/* Simulation */
	if (repeat == 1) {
	    if (reg_mprj_datah == 1)
		reg_mprj_datal = 0x80000000;
	    else
		reg_mprj_datal >>= 1;
	    reg_mprj_datah >>= 1;
	}
	else if ((channel > 7) || (channel < 1) || (channel == 2) || (channel == 3) ||
		(channel == 5) || (channel == 6)) {
	    if (reg_mprj_datah == 1)
		reg_mprj_datal = 0x80000000;
	    else
		reg_mprj_datal >>= 1;
	    reg_mprj_datah >>= 1;
	}
    }

    /* Simulation */
    fprintf(stdout, "Done with testing.  Generating result.\n");

    // Set up all channels for output based on the pattern of dependent and
    // independent hold violations.

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

    /* Simulation */
    fprintf(stdout, "Final configuration:\n");
    runtime_configure();

    // End with an output pattern indicating the configuration

    value = 0;
    for (i = 0; i < 19; i++) {
	if ((dep_l & (1 << i)) != 0)
	    value |= 0x1;
	value <<= 1;
    }
    fprintf(stdout, "Temp value:\n");
    fprintf(stdout, "Value = 0x%08x\n", value);

    reg_mprj_datal = dep_r | (value << 18);
    reg_mprj_datah = (value >> 14);

    fprintf(stdout, "Final values:\n");
    fprintf(stdout, "Dependent-right DEP_R = 0x%05x\n", dep_r);
    fprintf(stdout, "Dependent-left  DEP_L = 0x%05x\n", dep_l);

    fprintf(stdout, "Data low  = 0x%08x\n", reg_mprj_datal);
    fprintf(stdout, "Data high = 0x%08x\n", reg_mprj_datah);

    return 0;
}

