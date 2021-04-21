CC := gcc
CC_ARGS := -Wno-incompatible-pointer-types -Ofast -Wno-discarded-qualifiers -Wno-unused-result
UNAME := $(shell uname)
ifneq ($(UNAME), Linux)
	VS_PATH = C://"Program Files (x86)"/"Microsoft Visual Studio"/2019/Community/VC/Tools/MSVC/"14.27.29110"/bin/Hostx64/x64
	CC := $(VS_PATH)/cl.exe
endif

ROOT_DIRECTORY=.
SOURCES := ${shell find ${ROOT_DIRECTORY} -type d -print}
INCLUDE := ./

C_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.c) ) $(wildcard *.c)
#CPP_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.cpp) ) $(wildcard *.cpp)
H_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.h) ) $(wildcard *.h)

#CP_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.cp) ) $(wildcard *.cp)
#ASM_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.asm) ) $(wildcard *.asm)
#S_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.s) ) $(wildcard *.s)


BUILD := $(shell basename $(CURDIR))
VERSION := 0.0
ifeq ($(UNAME), Linux)
	DEFINE_PREFIX = -
	OS_CLEAR = clear
else
	DEFINE_PREFIX = /
	OS_CLEAR = cls
endif
DEFINES_DEF = DATE="\"`date`\"" VER=$(VERSION) PROG_NAME=\"$(BUILD)\" OS_CLEAR=\"$(OS_CLEAR)\" OS=$(UNAME)
DEFINES = $(foreach def,$(DEFINES_DEF), $(DEFINE_PREFIX)D$(def))



all:
	@echo Building ...
	@echo "\tTarget = $(UNAME)"
	@echo "\tVersion = $(VERSION)"
	@echo "\tC Files to Compile = $(words $(C_FILES))"
	
	@$(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(C_FILES)
print:
	@echo $(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(C_FILES)
print_H:
	@echo $(H_FILES)