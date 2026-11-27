#   Copyright (C) 2026 PS5 Payload SDK contributors
#
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

include ../Makefile.inc

CFLAGS := -target x86_64-sie-ps5 -fPIC -fno-plt -fno-stack-protector
CFLAGS += -nobuiltininc -isystem ../include/freebsd -I../include
CFLAGS += -fvisibility-nodllstorageclass=default -Wall -Werror -O1

.PHONY: all clean install

all: libps5microphone.a

microphone.o: microphone.c ../include/ps5/microphone.h ../include/ps5/audioin.h
	$(CC) -c $(CFLAGS) -o $@ $<

libps5microphone.a: microphone.o
	$(AR) -rsc $@ $^

clean:
	rm -f *.a *.o

install: libps5microphone.a
	install -d $(DESTDIR)/target/lib
	install $^ $(DESTDIR)/target/lib
