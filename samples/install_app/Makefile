#   Copyright (C) 2025 John Törnblom
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

FTP_URL := ftp://$(PS5_HOST):2121

ifdef PS5_PAYLOAD_SDK
    include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
else
    $(error PS5_PAYLOAD_SDK is undefined)
endif
ELF2SELF := ./make_fself.py

TITLE_ID := FAKE02932

CFLAGS := -Wall -Werror -g -DTITLE_ID=\"$(TITLE_ID)\"
LDADD  := -lSceIpmi -lSceAppInstUtil -lSceUserService -lSceSystemService

PS4_SDK_VERSION ?= 0x07590001

AUTHID   := 0x3800000000000022
AUTHINFO := 00 00 00 00 00 00 00 00 00 00 00 00 00 1C 00 40 00 FF 00 00 00 00 \
            00 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 80 \
            00 40 00 40 00 00 00 00 00 00 00 80 00 00 00 00 00 00 00 08 00 40 \
            FF FF 00 00 00 F0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
            00 00 00 00

.INTERMEDIATE: eboot.elf

all: payload.elf $(TITLE_ID)/eboot.bin

payload.elf: payload.c
	$(CC) $(CFLAGS) $(LDADD) -o $@ $^

eboot.o: eboot.c
	$(CC) -c $(CFLAGS) -o $@ $^

eboot.elf: eboot.o
	$(LD) --static -T eboot.x -o $@ $^

$(TITLE_ID)/eboot.bin: eboot.elf
	$(ELF2SELF) --ptype fake --paid $(AUTHID) \
		    --auth-info "$(AUTHINFO)" \
		    --app-version $(PS4_SDK_VERSION) \
		    --fw-version $(PS4_SDK_VERSION) $^ $@

$(TITLE_ID)/icon0.png:
	convert -size 512x512 -gravity center label:'$(TITLE_ID)' $@

clean:
	rm -f *.o *.elf $(TITLE_ID)/eboot.bin

test: $(TITLE_ID)/eboot.bin $(TITLE_ID)/icon0.png payload.elf
	curl -Q "MTRW" $(FTP_URL) > /dev/null

	curl -Q "MKD /system_ex/app/$(TITLE_ID)"         $(FTP_URL) > /dev/null || true
	curl -Q "MKD /system_ex/app/$(TITLE_ID)/sce_sys" $(FTP_URL) > /dev/null || true
	curl -Q "MKD /user/app/$(TITLE_ID)"              $(FTP_URL) > /dev/null || true
	curl -Q "MKD /user/app/$(TITLE_ID)/sce_sys"      $(FTP_URL) > /dev/null || true

	curl -T "$(TITLE_ID)/eboot.bin"          "$(FTP_URL)/system_ex/app/$(TITLE_ID)/"
	curl -T "$(TITLE_ID)/sce_sys/param.json" "$(FTP_URL)/user/app/$(TITLE_ID)/sce_sys/"
	curl -T "$(TITLE_ID)/icon0.png"          "$(FTP_URL)/user/app/$(TITLE_ID)/sce_sys/"

	$(PS5_DEPLOY) -h $(PS5_HOST) -p $(PS5_PORT) payload.elf

	curl -T "$(TITLE_ID)/sce_sys/param.json.system" "$(FTP_URL)/system_ex/app/$(TITLE_ID)/sce_sys/param.json"
