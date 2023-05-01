export PATH=$PATH:/bin:/usr/local/bin/:../../venv/bin:/usr/bin/:.

#FLASH=/media/efabless/PYBFLASH/
FLASH?=/media/yatharth/PYBFLASH
DEV=$(shell mpremote connect list | grep STLink | cut -f 1 -d ' ')
#COPY_CMD=rshell --port ${DEV} cp
COPY_CMD=cp

########### cross compile python to micropython bin. ###################

# mpy-cross is specific to the build machine, not the Nucleo.
# the current executable is for a M1 mac.  it needs to be compiled for other build machines

compile:
	mpy-cross flash.py
	mpy-cross io_config.py
	mpy-cross gpio_config_builder.py
	mpy-cross i2c.py
	mpy-cross nucleo_api.py
	mpy-cross boot.py

# runs script from the local filesystem
reset: check_device
	#mpremote connect ${DEV} soft-reset
	mpremote connect ${DEV} exec "import machine; machine.reset()"

# runs script from the local filesystem
version: check_device
	@mpremote connect ${DEV} exec "import io_config; io_config.version()"

# run io_config test to characterize a new part
# alternate -- mpremote connect ${DEV} exec "import io_config; io_config.run()"
# alternate -- mpremote connect ${DEV} exec "import machine; machine.reset()"
run: check_device check_part
	mpremote connect ${DEV} exec "import io_config; io_config.run('$(PART)', $(VOLTAGE))"

run_analog: check_device check_part
ifdef VOLTAGE
	mpremote connect ${DEV} exec "import io_config; io_config.run('$(PART)', voltage=$(VOLTAGE), analog=True)"
else
	mpremote connect ${DEV} exec "import io_config; io_config.run('$(PART)', analog=True)"
endif

# copy the definition file for a part after running io_config
get_config: check_device
	mpremote connect ${DEV} cp :gpio_config_def.py .

# run a sanity check using the gpio_config_def.py file on the nucleo
sanity_check: check_device
ifndef FILE
	$(error FILE is undefined, please export it before running make flash)
else
	$(COPY_CMD) ${FILE} ${FLASH}/gpio_config_def.py
	sync
	sleep 2
	mpremote connect ${DEV} exec "import io_config; io_config.run_sanity_check()"
endif

# power up the caravel hat while mounted to Nucleo
poweron: check_device
	mpremote connect ${DEV} exec "import io_config; io_config.run_poweron($(VOLTAGE))"

change_power: check_device check_voltage
	mpremote connect ${DEV} exec "import io_config; io_config.run_change_power($(VOLTAGE))"

# flash firmware on caravel hat while mounted to Nucleo
flash: check_volume check_device
ifndef FILE
	$(error FILE is undefined, please export it before running make flash)
else
	$(COPY_CMD) ${FILE} ${FLASH}/firmware.hex
	sync
	sleep 2
	mpremote connect ${DEV} exec "import io_config; io_config.run_flash_caravel($(VOLTAGE))"
endif

# enter repl on nucleo
repl:
	mpremote connect ${DEV} repl

# flash micropython firmware image.  this firmware image has been rebuilt to add pins for the Caravel Nucleo Hat
F746ZG: compile
	st-flash --connect-under-reset --format ihex write F746ZG_firmware.hex
	sleep 5
	make F746ZG-copy

# copies scripts to nucleo
copy2 F746ZG-copy: compile check_volume
	$(COPY_CMD) flash.mpy i2c.mpy gpio_config_builder.mpy nucleo_api.mpy io_config.mpy ${FLASH}
	$(COPY_CMD) config_io_o.hex ${FLASH}
	$(COPY_CMD) main.py ${FLASH}
	sync
	ls ${FLASH}

check_volume:
	@if [ ! -d "$(FLASH)" ]; then \
		echo "Nucleo volume not found.  Please export FLASH=/<my_path>/PYBFLASH"; \
		exit 1; \
	fi

check_device:
ifndef DEV
	$(error "Nucleo device file not found")
endif

check_part:
ifndef PART
	$(error "PART not defined.  Please use 'make run PART=<part_id>'")
endif

check_voltage:
ifndef VOLTAGE
	$(error "VOLTAGE not defined.  Please use 'make change_power VOLTAGE=<voltage>'")
endif

check-python:
ifeq ($(shell which python3),)
$(error Please install python 3.6+)
endif

setup: check-python
	python3 -m pip install rshell
	python3 -m pip install mpy-cross
	python3 -m pip install mpremote

#####################targets for building hex file#########################################

TOOLCHAIN_PATH=

TOOLCHAIN_PREFIX=riscv64

INCLUDES=-I$(shell pwd) -I../_includes/ 

SED_CMD=sed -i'.orig' -e


.SUFFIXES:

all: check_part setup hex

check_part:
ifndef PART
	$(error "PART not defined.  Please use 'make PART=<part_id>'")
endif

hex:  config_io_o.hex

%.elf: %.c ../sections.lds ../crt0_vex.S ./gpio_config_data.c ./send_packet.c
	#$(TOOLCHAIN_PATH)riscv32-unknown-linux-gnu-gcc -I../ -I../generated/ -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../crt0_vex.S ../isr.c ../gpio_program.c $<

	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc -I../ -I../generated/ -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../crt0_vex.S ../isr.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-objdump -s  config_io_o.elf > config_io_o.lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O verilog $< $@
	$(SED_CMD) 's/@10/@00/g' $@
	$(SED_CMD) '1,/@00/!d' $@

clean:
	rm -f *.elf *.hex *.bin *.vvp *.lst *.orig gpio_config_data.* gpio_config_def.py
	rm -rf __pycache__
	

check_part:
ifndef PART
	$(error "PART not defined.  Please use 'make PART=<part_id>'")
endif



################### copy def file ###################################
vsd: check_part
	cp gpio_config_def.py ../_includes/gpio_def/gpio_config_def_$(PART).py

.PHONY: clean image hex copy repl run
