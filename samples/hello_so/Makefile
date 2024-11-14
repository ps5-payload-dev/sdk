#   Copyright (C) 2024 John Törnblom
#
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING. If not see
# <http://www.gnu.org/licenses/>.

PS5_HOST ?= ps5
PS5_PORT ?= 9021

ifdef PS5_PAYLOAD_SDK
    include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
else
    $(error PS5_PAYLOAD_SDK is undefined)
endif

ELF := hello_so.elf

CFLAGS := -Wall -g -Wl,--as-needed

# DAG:
#  hello_so.elf
#      /data/libtest.so
#          libSceLibcInternal.sprx
#          /data/libA.so
#              libSceLibcInternal.sprx
#          /data/libB.so
#              libSceRandom.sprx


all: $(ELF) libtest.so

$(ELF):  main.c libtest.so
	$(CC) $(CFLAGS) -o $@ $^

libA.so: libA.c
	$(CC) $(CFLAGS) -shared -o $@ $^ -Wl,-soname=/data/$@

libB.so: libB.c
	$(CC) $(CFLAGS) -shared -lSceRandom -o $@ $^ -Wl,-soname=/data/$@

libtest.so: libtest.c libA.so libB.so
	$(CC) $(CFLAGS) -shared -o $@ $^ -Wl,-soname=/data/$@

clean:
	rm -f *.so *.o *.elf

upload:
	curl -T libA.so ftp://$(PS5_HOST):2121/data/libA.so
	curl -T libB.so ftp://$(PS5_HOST):2121/data/libB.so
	curl -T libtest.so ftp://$(PS5_HOST):2121/data/libtest.so

test: $(ELF)
	$(PS5_DEPLOY) -h $(PS5_HOST) -p $(PS5_PORT) $^

debug: $(ELF)
	gdb \
	-ex "target extended-remote $(PS5_HOST):2159" \
	-ex "file $(ELF)" \
	-ex "remote put $(ELF) /data/$(ELF)" \
	-ex "set remote exec-file /data/$(ELF)" \
	-ex "start"
