# Steps VSDSquadron Calibration

This directory provides a diagnostic software for characterizing timing failure patterns between GPIO pads.

## INSTALLATION

1. Install the required tools including **mpremote**, **mpy-cross** and **rshell**.  

```bash
  make setup
```

- **mpremote** is used for connecting the Micropython
- **mpy-cross** is a cross compiler for Micropython the compiles a python file into a binary format which can be run in 
micropython.  It is used here to reduce the size of the files because the size of the flash on the Nucleo board is 
limited on some models.

2. You will also need to install the **stlink** tools for your client.   These are required to flash Micropython firmware on the Nucleo board.

   - https://github.com/stlink-org/stlink/tree/master

3. After you made both USB connections, you will need to find the path for the Flash volume.  

   - On MacOS, it should be located at `//Volumes/PYBFLASH`.
   - On Ubuntu, it should be mounted at `/media/<userid>/PYBFLASH`.
   - You will need to `export FLASH=<path>` or set the path in the Makefile at the top of the file.
   - NOTE: For some linux platforms, the PYBFLASH volume is not automatically

### UPDATE THE DIAGNOSTIC SOFTWARE

It will be required to update the diagnostic software to get the latest enhancements and bug fixes.

```bash
make F746ZG
```

You can also just recompile and copy the files onto the flash by running on of the following make targets:

```bash
make F746ZG-copy
```

### RUNNING THE DIAGNOSTIC

To run the diagnostic, enter the following commands.  

The PART variable is an ID for the part you are testing defined by you.  It will be recorded in the output of the test for future reference.

```bash
cd vsdip/firmware/_config

## for digital (or analog) projects using Caravel & user_project_wrapper
make run PART=<part id>

## for analog projects using Caravan & user_analog_project_wrapper
make run_analog PART=<part id>

```

Type `Ctrl-C` to exit the test diagnostic once it completes.  If the test completed for the part, run the following to retrieve the configuration file.  The file will indicated the IO that were successfully configured.  Successfully configured IO can be used for this part for firmware routines.

```bash
make vsd PART=<part id>
```

The file is specific to the part you ran the diagnostic with. Each part will have a different `gpio_config_def.py` file because the timing failure pattern will be different for each part.
