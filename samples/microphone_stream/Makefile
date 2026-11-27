PS5_PAYLOAD_SDK ?= /opt/ps5-payload-sdk

include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk

ELF := microphone_stream.elf
CFLAGS := -Wall -Werror -g
LDLIBS := -lps5microphone -lSceAudioIn -lSceUserService -lpthread

.PHONY: all clean

all: $(ELF)

$(ELF): main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(ELF)
