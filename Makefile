CC = g++




ifndef UNAME
UNAME = $(shell uname)
PIXEL_GAME_ENGINE_ARGS = -lX11 -lpng -lGL -lpthread -std=c++17
CC_ARGS = -Ofast -Wno-unused-result $(PIXEL_GAME_ENGINE_ARGS) -ldl
else
PIXEL_GAME_ENGINE_ARGS = -ldwmapi -lGL -lpng -lopengl32 -lpthread  -lstdc++fs
CC_ARGS = -std=c++17  -static -mwindows -Ofast $(PIXEL_GAME_ENGINE_ARGS)
endif

ifneq ($(UNAME), Linux)
CC = wine "/mnt/Windows/Program Files (x86)/CodeBlocks/MinGW/bin/g++.exe"
#CC = "/C/Program Files (x86)/CodeBlocks/MinGW/bin/g++.exe"
endif

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
ifeq ($(UNAME), Linux)
	BUILD := $(shell basename $(CURDIR)).linux
	DEFINE_PREFIX = -
	OS_CLEAR = clear
else
	BUILD := $(shell basename $(CURDIR)).exe
	DEFINE_PREFIX = -
	OS_CLEAR = cls
endif

DEFINES_DEF = DATE="\"`date`\"" VER=\"$(VERSION)\" PROG_NAME=\"$(BUILD)\" OS_CLEAR=\"$(OS_CLEAR)\"

ifndef $(DEBUG)
DEBUG = false
endif

ifeq ($(DEBUG), true)
DEFINES_DEF += DEBUG=$(DEBUG)
CC_ARGS += -g
endif

DEFINES = $(foreach def,$(DEFINES_DEF), $(DEFINE_PREFIX)D$(def))

ifeq ($(UNAME), Windows)
DEFINES = 
endif


$(ODIR)/./%.o : %.cpp
	@echo $(notdir $(basename $*)).cpp
	@mkdir -p $(dir $@)
	@$(CC) -c $*.cpp -o $@ -I $(INCLUDE) $(CC_ARGS) $(DEFINES)


.PHONY: all
.PHONY: message
.PHONY: compile
.PHONY: wine_release
.PHONY: wine_deubg
.PHONY: touch_all

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


compile1:
	@$(foreach cc,$(CPP_FILES),  $(shell $(CC) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) -c $(cc) -o $(ODIR)/$(notdir $(basename $(cc)).o)))
	@$(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(O_FILES)
compile2:
#@$(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(CPP_FILES)
	@$(CC) $(CPP_FILES) -o $(BUILD) -I $(INCLUDE) -I "Z:/mnt/Windows/Program Files (x86)/CodeBlocks/MinGW/lib/gcc/mingw32/5.1.0/include/c++" $(CC_ARGS) $(DEFINES) 
run:
	@./$(BUILD)

clean:
	@rm -rf $(ODIR)
	@rm -rf x64
	@rm -rf Debug
	@rm -rf Release


debug:
	@$(MAKE) DEBUG=true --no-print-directory
release:
	@$(MAKE) --no-print-directory

wine_debug:
	@$(MAKE) UNAME=Windows DEBUG=true --no-print-directory
wine_release:
	@$(MAKE) UNAME=Windows --no-print-directory

touch_all:
	@find . -type f -exec touch {} +

#FOR DEBUGGGING PURPOSES
print:
#@echo $(CC) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(DEFINES) $(CPP_FILES)
	@echo $(CC) $*.cpp -o $@ -I $(INCLUDE) $(CC_ARGS) $(DEFINES)
	
print_H:
	@echo $(H_FILES)
print_O:
	@echo $(O_FILES)
print_C:
	@echo $(C_FILES)
print_CPP:
	@echo $(CPP_FILES)
print_dir:
	@echo $(dir include/resource/resources.h)
