MAKE    ?= make
PYTHON  ?= python3

DESTDIR ?= /opt/ps5-payload-sdk

LLVM_CONFIG_CANDIDATES := llvm-config-21 \
                          llvm-config-20 llvm-config-19 llvm-config-18 \
                          llvm-config-17 llvm-config-16 llvm-config-15 \
                          llvm-config
LLVM_CONFIG_CANDIDATES := $(foreach LCC,$(LLVM_CONFIG_CANDIDATES), \
                          $(if $(shell command -v $(LCC) 2>/dev/null), $(LCC)))

LLVM_CONFIG ?= $(firstword $(LLVM_CONFIG_CANDIDATES))
ifndef LLVM_CONFIG
    $(error Unable to find llvm-config)
endif

LLVM_BINDIR := $(shell $(LLVM_CONFIG) --bindir)
CC := $(LLVM_BINDIR)/clang
AR := $(LLVM_BINDIR)/llvm-ar
LD := $(LLVM_BINDIR)/ld.lld

# ld is moved out of llvm on MacOS
ifeq ($(shell command -v $(LD) 2>/dev/null),)
OS := $(shell uname -s)
ifeq ($(OS),Darwin)
BREW := $(shell command -v brew 2>/dev/null)
ifneq ($(BREW),)
LD := $(shell $(BREW) --prefix lld 2>/dev/null)/bin/ld.lld
else
    $(error Unable to find Homebrew)
endif
endif
endif
