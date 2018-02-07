#
# Makefile for 1541 Ultimate Project
#
# This Makefile requires GNU make
#
# --------------------------------------------------------------------------
SHELL = /bin/bash
MAKEFILE = Makefile

# Core information
CC  = gcc

# minizip

MINIZ_INCLUDE=../software/system
MINIZ_HEADERS=$(MINIZ_INCLUDE)/miniz.h util.h
MINIZ_SOURCES=$(MINIZ_INCLUDE)/miniz.c util.c miniz-tool.c

# bsdiff

BSDIFF_HEADERS=bsdiff.h util.h
BSDIFF_SOURCES=bsdiff.c util.c bsdiff-tool.c

# rompack
ROMPACK_INCLUDE=$(MINIZ_INCLUDE)
ROMPACK_HEADERS=$(MINIZ_INCLUDE)/miniz.h util.h
ROMPACK_SOURCES=$(MINIZ_INCLUDE)/miniz.c util.c rompack-tool.c

# --------------------------------------------------------------------------
# Compiling

%: %.c
	@echo $@
	@$(CC) $(CFLAGS) $^ -o $(basename $@)

# --------------------------------------------------------------------------
# Binaries

.PHONY:	all clean
all:   	bin2hex hex2bin make_array make_mem makeappl promgen checksum dump_vcd dump_bus_trace dump_rtos_trace swap svf_dump miniz bsdiff rompack

miniz: $(MINIZ_HEADERS) $(MINIZ_SOURCES)
	@echo $@
	@$(CC) $(CFLAGS) -I $(MINIZ_INCLUDE) -o $@ $(MINIZ_SOURCES)

bsdiff: $(BSDIFF_HEADERS) $(BSDIFF_SOURCES)
	@echo $@
	@$(CC) $(CFLAGS) -o $@ $(BSDIFF_SOURCES)

rompack: $(ROMPACK_HEADERS) $(ROMPACK_SOURCES)
	@echo $@
	@$(CC) $(CFLAGS) -I $(ROMPACK_INCLUDE) -o $@ $(ROMPACK_SOURCES)

ifneq ($(SYSTEMDRIVE), C:)
#	echo $(SYSTEMDRIVE)
	@$(MAKE) -C 64tass
endif

clean:
	@rm -f bin2hex
	@rm -f hex2bin
	@rm -f make_array
	@rm -f make_mem
	@rm -f makeappl
	@rm -f promgen
	@rm -f checksum
	@rm -f swap
	@rm -f svf_dump
	@rm -f dump_vcd
	@rm -f dump_bus_trace
	@rm -f dump_rtos_trace
	@rm -f bin2hex.exe
	@rm -f hex2bin.exe
	@rm -f make_array.exe
	@rm -f make_mem.exe
	@rm -f makeappl.exe
	@rm -f promgen.exe
	@rm -f checksum.exe
	@rm -f dump_vcd.exe
	@rm -f dump_rtos_trace.exe
	@rm -f dump_bus_trace.exe
	@rm -f swap.exe
	@rm -f svf_dump.exe
	@rm -f 64tass/64tass
	@rm -f 64tass/*.o
	@rm -f miniz
	@rm -f bsdiff
	@rm -f rompack

svf_dump: ../software/application/tester/svf_player.c
	@echo $@
	@$(CC) ../software/application/tester/svf_player.c $(CFLAGS) -DDUMP -o $(basename $@)

