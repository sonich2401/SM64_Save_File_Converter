#RenDev#2616 File Selector Tool
#    Copyright (C) 2021 RenDev
#
#    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
#    Permission is also granted to not credit the author in any way as long as you do not take credit
#    for this piece of software.
#
#    Anyone is free to copy, modify, publish, use, compile, sell, or
#    distribute this software, either in source code form or as a compiled
#    binary, for any purpose, commercial or non-commercial, and by any
#    means.
#
#    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
#    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
#    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
#    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
#    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/

CC = g++
UNAME = $(shell uname)
CC_ARGS = -Wno-unused-result -Ofast -lX11
DEFINES_DEF = DATE="\"`date`\"" VER=\"$(VERSION)\" PROG_NAME=\"$(BUILD)\" OS_CLEAR=\"$(OS_CLEAR)\" FORCE_EXPERIMENTAL_FS

ODIR := build
ROOT_DIRECTORY=.
SOURCES := ${shell find ${ROOT_DIRECTORY} -type d -print}
INCLUDE := ./include

C_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.c) ) $(wildcard *.c)
CPP_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.cpp) ) #$(wildcard *.cpp)
H_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.h) ) $(wildcard *.h)

ASM_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.asm) ) $(wildcard *.asm)
S_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.s) ) $(wildcard *.s)

O_FILES = $(abspath $(addprefix $(ODIR)/, $(CPP_FILES:.cpp=.o)))


VERSION := 1.0
BUILD := $(shell basename $(CURDIR)).linux
DEFINE_PREFIX = -
OS_CLEAR = clear


FORCE_EXPERIMENTAL_FS=true

ifndef $(DEBUG)
DEBUG = false
endif

ifeq ($(DEBUG), true)
DEFINES_DEF += DEBUG=$(DEBUG)
CC_ARGS += -g
endif

DEFINES = $(foreach def,$(DEFINES_DEF), $(DEFINE_PREFIX)D$(def))


$(ODIR)/./%.o : %.cpp
	@echo $(notdir $(basename $*)).cpp
	@mkdir -p $(dir $@)
	@$(CC) -c $*.cpp -o $@ -I $(INCLUDE) $(CC_ARGS) $(DEFINES)


.PHONY: all
.PHONY: message
.PHONY: compile
.PHONY: wine_release
.PHONY: wine_deubg

all: compile run
	

compile: message $(addprefix $(ODIR)/, $(CPP_FILES:.cpp=.o)) | $(ODIR)
	@$(CC) $(O_FILES) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) 

message:
	@echo Building ...
	@echo "\tDebug Build = $(DEBUG)"
	@echo "\tTarget = $(UNAME)"
	@echo "\tVersion = $(VERSION)"
	@echo "\tC++ Files to Compile = $(words $(CPP_FILES))"
	
$(ODIR):
	@mkdir -p $@

link:
	@echo $(CC) $(O_FILES) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES)

compile1:
	@$(foreach cc,$(CPP_FILES),  $(shell $(CC) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) -c $(cc) -o $(ODIR)/$(notdir $(basename $(cc)).o)))
	@$(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(O_FILES)
compile2:
#@$(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(CPP_FILES)
	@$(CC) $(CPP_FILES) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) 
run:
	@./$(BUILD)

clean:
	@rm -rf $(ODIR)
	@rm -rf x64
	@rm -rf Debug
	@rm -rf Release
	@rm -rf .vs
	@rm -rf $(BUILD)


debug:
	@$(MAKE) DEBUG=true --no-print-directory
release:
	@$(MAKE) --no-print-directory
