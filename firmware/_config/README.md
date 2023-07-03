# Steps VSDSquadron Calibration

This directory provides a diagnostic software for characterizing timing failure patterns between GPIO pads.

## INSTALLATION

1. Install the required tools including **mpremote**, **mpy-cross** and **rshell**.  

- **mpremote** is used for connecting the micropython
- **mpy-cross** is a cross compiler for micropython the compiles a python file into a binary format which can be run in 
micropython. It is used here to reduce the size of the files because the size of the flash on the Nucleo board is 
limited on some models.
- **rshell** is a simple shell which runs on the host and uses MicroPython's raw-REPL to send python snippets to the pyboard in order to get filesystem information, and to copy files to and from microPython's filesystem.

**Note**: It is necessary to have python3 and pip3 to install these softwares.

```bash
  sudo apt install python3
  sudo apt-get install python3-pip
  sudo apt update
  sudo apt upgrade
```

for installing mpremote

```bash
  sudo pip3 install mpremote
```

for installing mpy_cross

```bash
  python3 -m pip install mpy_cross
```

for installing rshell

```bash
  sudo pip3 install rshell
```
You will also need to install the **stlink** tools for your client.  These are required to flash micropython firmware on the Nucleo board.

   - https://github.com/stlink-org/stlink/releases : stlink v1.7.0 ( recommend to use the .deb file for an easy installation --> found under __Assets__ )



2. After installing all the necessary tools ,run the following command in the **firmware** directory. Ensure that the "setup" script is **executable**.

```bash
  make setup
```


3. After you made both USB connections, you will need to find the path for the Flash volume.  

   - On MacOS, it should be located at `//Volumes/PYBFLASH`.
   - On Ubuntu, it should be mounted at `/media/<userid>/PYBFLASH`.
   - make sure to **change <userid>** mentioned in the ![Makerfile](https://github.com/Visruat/vsdsquadron/blob/main/firmware/_config/Makefile)
   - You will need to `export FLASH=<path>` or set the path in the Makefile at the top of the file.
                            **OR**
   - If this doesnt work you can also directly set the path in the bashrc file of your system (ctrl + H --> to access hidden files). Add the following command at the end of the file.
   ```bash
    export PATH="$PATH:$HOME/.local/bin"
   ``` 
   - if the above method is followed comment out the path present in the Makerfile.
   
   - NOTE: For some linux platforms, the PYBFLASH volume is not automatically detected.

### UPDATE THE DIAGNOSTIC SOFTWARE

It will be required to update the diagnostic software to get the latest enhancements and bug fixes.

```bash
make F746ZG
```

**Note**
If an error occurs during the process, then try these steps:
- make sure the connections are done properly.
- try running the command again.
- if the above step does not work, power off and power on the white board (Nucleo) and run it again.
- if the error still persists, hold down the black reset button of the white board (Nucleo) and run the command. wait for few seconds and release the button. 

You can also just recompile and copy the files onto the flash by running the following make targets:

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

Type `Ctrl-C` to exit the test diagnostic once it completes.  If the test completed for the part, run the following to retrieve the configuration file.  The file will indicate the IO that were successfully configured.  Successfully configured IO can be used for this part for firmware routines.

```bash
make vsd PART=<part id>
```

The file is specific to the part you ran the diagnostic with. Each part will have a different `gpio_config_def.py` file because the timing failure pattern will be different for each part.
