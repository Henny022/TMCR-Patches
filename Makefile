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

ASFLAGS := -mcpu=arm7tdmi -mthumb
ASFLAGS += -I $(REPO)/build/EU -I $(REPO)/asm/macros

.DELETE_ON_ERROR:

tmcr.gba: Buildfile.event tmc_eu.gba $(shell $(SCANINC) Buildfile.event) Language\ Raws/Data.txt Language\ Raws/Pointer.txt Language\ Raws/CheckIds.txt Language\ Raws/script.txt
	cp tmc_eu.gba $@
	mono ColorzCore.exe A FE8 -output:$@ -input:$<

modules.cevent: $(shell ls modules/*)
	tools/merge_modules.py > $@

EACFLAGS = 

# : EACFLAGS += --allow-unsafe-hooks
%.cevent: %.o symbols.json
	eac compile -o $@ $< --symbols symbols.json $(EACFLAGS)

%.bin: %.o
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $<

symbols.json: $(REPO)/tmc_eu.elf
	eac extract_symbols -o $@ $<

.PHONY: clean
clean:
	rm -f tmcr.gba
	rm -f $(shell find . -name '*.cevent')

.PHONY: run
run: tmcr.gba
	mgba-qt tmcr.gba
