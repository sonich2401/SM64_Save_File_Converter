CC := g++
CC_ARGS := -Ofast -Wno-unused-result
UNAME := $(shell uname)
ifneq ($(UNAME), Linux)
	VS_PATH = C://"Program Files (x86)"/"Microsoft Visual Studio"/2019/Community/VC/Tools/MSVC/"14.27.29110"/bin/Hostx64/x64
	CC := $(VS_PATH)/cl.exe
endif

ODIR := build
ROOT_DIRECTORY=.
SOURCES := ${shell find ${ROOT_DIRECTORY} -type d -print}
INCLUDE := ./

#C_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.c) ) $(wildcard *.c)
CPP_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.cpp) ) $(wildcard *.cpp)
H_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.h) ) $(wildcard *.h)

#CP_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.cp) ) $(wildcard *.cp)
#ASM_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.asm) ) $(wildcard *.asm)
#S_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.s) ) $(wildcard *.s)

O_FILES = $(foreach cc,$(CPP_FILES),  $(ODIR)/$(notdir $(basename $(cc)).o) )



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


#%.o: $(C_FILES)
#	$(CC) -c $< $(C_ARGS) -I $(INCLUDE) $(DEFINES) -o $@

#$(BUILD): $(O_FILES)
#	$(CC) $^ -o $@




all:
	@$(MAKE) message --no-print-directory
	@$(MAKE) compile --no-print-directory
message:
	@echo Building ...
	@echo "\tTarget = $(UNAME)"
	@echo "\tVersion = $(VERSION)"
	@echo "\tC Files to Compile = $(words $(CPP_FILES))"
compile:
	@$(foreach cc,$(CPP_FILES),  $(shell $(CC) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) -c $(cc) -o $(ODIR)/$(notdir $(basename $(cc)).o)))
	@$(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(O_FILES)
print:
	@echo $(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(C_FILES)
print_H:
	@echo $(H_FILES)
print_O:
	@echo $(O_FILES)
print_C:
	@echo $(C_FILES)
clean:
	@rm $(O_FILES)