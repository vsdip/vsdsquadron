TOOLCHAIN_PREFIX=riscv64-unknown-elf
INCLUDES=-I$(shell pwd) -I../_includes/ 
DEVICE=/dev/serial/by-id/usb-FTDI_Single_RS232-HS-if00-port0    # replace by the terminal used by your device
BAUDS=9600

.SUFFIXES:

all: check_part setup hex

check_part:
ifndef PART
	$(error "PART not defined.  Please use 'make PART=<part_id>'")
endif

setup: check_part
	cp ../_includes/gpio_def/gpio_config_def_$(PART).py gpio_config_def.py

hex:  main.hex

gpio_config_data.c: 
	python3 ../_includes/gpio_config/gpio_config_builder.py

%.elf: %.c ../_includes/sections.lds ../_includes/crt0_vex.S gpio_config_data.c
	$(TOOLCHAIN_PREFIX)-gcc $(INCLUDES) -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,../_includes/sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../_includes/crt0_vex.S ../_includes/isr.c $<
	$(TOOLCHAIN_PREFIX)-objdump -D $@ > $*.lst

%.hex: %.elf
	$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -i.orig -e 's/@1000/@0000/g' $@
	rm -f *.elf *.bin *.vvp *.orig  

# ---- Flash ----

flash: main.hex
	python3 ../_util/caravel_hkflash.py $<
	python3 ../_util/caravel_hkstop.py


# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.lst *.orig gpio_config_data.* gpio_config_def.py
	rm -rf __pycache__
	
terminal:
	sudo picocom -b $(BAUDS) $(DEVICE) --imap lfcrlf,crcrlf --omap delbs,crlf 

.PHONY: clean hex all flash setup

