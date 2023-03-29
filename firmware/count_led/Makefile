TOOLCHAIN_PATH=

TOOLCHAIN_PREFIX=riscv64

INCLUDES=-I$(shell pwd) -I../includes/ 

.SUFFIXES:

all: check_part setup hex

check_part:
ifndef PART
	$(error "PART not defined.  Please use 'make PART=<part_id>'")
endif

setup: check_part
	cp ../includes/gpio_def/gpio_config_def_$(PART).py gpio_config_def.py

hex:  main.hex

gpio_config_data.c: gpio_config_def.py gpio_config_io.py
	python3 ../includes/gpio_config/gpio_config_builder.py

sim: gpio_config_def.py gpio_config_io.py gpio_config_data.c
	python3 ../includes/gpio_config/gpio_config_simulator.py

check: gpio_config_def.py gpio_config_io.py gpio_config_data.c
	python3 ../includes/gpio_config/gpio_config_checker.py

%.elf: %.c ../includes/sections.lds ../includes/crt0_vex.S gpio_config_data.c
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-gcc $(INCLUDES) -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,../includes/sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../includes/crt0_vex.S ../includes/isr.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-unknown-elf-objdump -D $@ > $*.lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O verilog $< $@
	sed -i.orig -e 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O binary $< $@

# ---- Flash ----

flash: main.hex
	python3 ../util/caravel_hkflash.py $<
	python3 ../util/caravel_hkstop.py


# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.lst *.orig gpio_config_data.* gpio_config_def.py
	rm -rf __pycache__
	
.PHONY: clean hex all flash setup

