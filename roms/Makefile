BSDIFF=../tools/bsdiff
MINIZ=../tools/miniz
ROMPACK=../tools/rompack

ROMPACK_ADR_U2P=../software/io/flash/rom_pack_addresses_u2p.h
ROMPACK_FILES=$(ROMPACK_ADR_U2P)

.PHONY: all clean

INPUT_FILES=\
	ar5ntsc.bin\
	ar5pal.bin\
	ar6pal.bin\
	epyx.bin\
	final3.bin\
	kcs.bin\
	rr38ntsc.bin\
	rr38pal.bin\
	ss5ntsc.bin\
	ss5pal.bin\
	tar_ntsc.bin\
	tar_pal.bin

OUTPUT_FILES=\
	ar5ntsc.bin§ar5pal.bin.mz\
	ar5pal.bin.mz\
	ar6pal.bin.mz\
	epyx.bin.mz\
	final3.bin.mz\
	kcs.bin.mz\
	rr38ntsc.bin§rr38pal.bin.mz\
	rr38pal.bin.mz\
	ss5ntsc.bin§ss5pal.bin.mz\
	ss5pal.bin.mz\
	tar_ntsc.bin§tar_pal.bin.mz\
    tar_pal.bin.mz

all: rom_pack.bin

%.mz: %
	$(MINIZ) $< > $@

rom_pack.bin: $(BSDIFF) $(MINIZ) $(ROMPACK) $(INPUT_FILES) $(OUTPUT_FILES) $(ROMPACK_FILES)
	@echo -n " ==> Uncompressed size total: "
	@du -csh $(INPUT_FILES) | tail -n1 | cut -f1
	@echo -n " ==> Compressed size total  : "
	@du -csh $(OUTPUT_FILES) | tail -n1 | cut -f1
	@cat *.mz > $@
	cat $(ROMPACK_FILES)

ar5ntsc.bin§ar5pal.bin:	
	$(BSDIFF) ar5pal.bin ar5ntsc.bin > $@

rr38ntsc.bin§rr38pal.bin:
	$(BSDIFF) rr38pal.bin rr38ntsc.bin > $@

ss5ntsc.bin§ss5pal.bin:
	$(BSDIFF) ss5pal.bin ss5ntsc.bin > $@

tar_ntsc.bin§tar_pal.bin:
	$(BSDIFF) tar_pal.bin tar_ntsc.bin > $@

$(ROMPACK_ADR_U2P):
	$(ROMPACK) 0x200000 $@

clean:
	@rm -f *§*
	@rm -f *.mz
	@rm -f rom_pack.bin
	@rm -f $(ROMPACK_FILES)

