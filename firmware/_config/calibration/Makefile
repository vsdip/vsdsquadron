
# TOOLCHAIN_PATH=/usr/local/bin/
TOOLCHAIN_PATH=/opt/riscv32imc/bin/
# TOOLCHAIN_PATH=/ef/apps/bin/

# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
# TOOLCHAIN_PREFIX=riscv64
TOOLCHAIN_PREFIX=riscv32
INCLUDES=-I$(shell pwd) -I../ -I../generated/

# ---- Test patterns for project raven ----

.SUFFIXES:

PATTERN = calibration

hex:  ${PATTERN:=.hex}

%.elf: %.c ../sections.lds ../crt0_vex.S
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-gcc $(INCLUDES) -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../crt0_vex.S ../isr.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-unknown-elf-objdump -D $@ > $*.lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O verilog $< $@
	sed -i'.orig' -e 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O binary $< $@

client: client.c
	gcc client.c -o client

flash: calibration.hex
	python3 ../util/caravel_hkflash.py $<
	python3 ../util/caravel_hkstop.py

flash_nucleo: calibration.hex
	make -f ../nucleo/Makefile flash FILE=calibration.hex

sanity_check: gpio_config_def.py
	make -f ../nucleo/Makefile sanity_check FILE=gpio_config_def.py

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.lst *.orig

.PHONY: clean hex all flash

