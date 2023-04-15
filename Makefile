# === begin config block ===
# change these variables to configure build
WARNINGS := -Wall -Wextra -Werror
CFLAGS := -O2 -g
# ==== end config block ====

ifndef REPO
$(error variable REPO not set)
endif

CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
OBJCOPY := arm-none-eabi-objcopy
SCANINC := python tools/scaninc.py

CFLAGS += $(WARNINGS) -Wno-multichar -Wno-builtin-declaration-mismatch
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -mcpu=arm7tdmi -mthumb -mlong-calls
CFLAGS += -I $(REPO)/tools/agbcc/include -I $(REPO)/include -nostdinc
CFLAGS += -undef -DEU -DREVISION=0 -DLANGUAGE=ENGLISH

tmcr.gba: Buildfile.event tmc_eu.gba $(shell $(SCANINC) Buildfile.event)
	cp tmc_eu.gba $@
	mono ColorzCore.exe A FE8 -output:$@ -input:$<

modules.cevent: $(shell ls modules/*)
	tools/merge_modules.py > $@

%.cevent: %.o symbols.json
	eac compile -o $@ $< --symbols symbols.json

%.bin: %.o
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) -mcpu=arm7tdmi -c -o $@ $<

symbols.json: $(REPO)/tmc_eu.elf
	eac extract_symbols -o $@ $<

.PHONY: clean
clean:
	rm -f tmcr.gba
	rm -f $(shell find . -name '*.cevent')

.PHONY: run
run: tmcr.gba
	mgba-qt tmcr.gba
