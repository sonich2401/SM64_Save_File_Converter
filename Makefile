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
BUILD := sm64sfm
DEFINE_PREFIX = -
OS_CLEAR = clear

#ifndef $(INSTALL_PATH)
#INSTALL_PATH = .
#endif

DEFINES_DEF := DATE="\"`date`\"" VER=\"$(VERSION)\" PROG_NAME=\"$(BUILD)\" OS_CLEAR=\"$(OS_CLEAR)\"

ifndef $(DEBUG)
DEBUG = false
endif

ifeq ($(DEBUG), true)
DEFINES_DEF += DEBUG=$(DEBUG)
CC_ARGS += -g
endif

ifndef $(INSTALL_PATH)
DEFINES_DEF += INSTALL_PATH=\"$(INSTALL_PATH)\"
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
.PHONY: install
.PHONY: uninstall

.PHONY: delete_path_macro_objects

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

$(BUILD): compile

run:
	@./$(BUILD)

clean:
	@rm -rf $(ODIR)
	@rm -rf x64
	@rm -rf Debug
	@rm -rf Release


INSTALL_DIR = /usr/bin/$(BUILD)
DESKTOP_SHORTCUT_DIR = /usr/share/applications
install:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) compile INSTALL_PATH=\"$(INSTALL_DIR)\" --no-print-directory
#files belong to root now so allow all users to access them again
	@chmod -R +rwx build
#create install location
	@mkdir -p $(INSTALL_DIR)
#install exectauable
	@cp ./$(BUILD) $(INSTALL_DIR)/$(BUILD)
	@chmod +x $(INSTALL_DIR)/$(BUILD)
#create an alias
	@rm -rf /usr/bin/sm64fm
	@ln -s $(INSTALL_DIR)/$(BUILD) /usr/bin/sm64fm

#install resources
	@cp -r ./pic $(INSTALL_DIR)/pic
	@cp -r ./snd $(INSTALL_DIR)/snd
	@cp ./LICENCE $(INSTALL_DIR)/LICENCE
	@chmod u=r $(INSTALL_DIR)/LICENCE
	@chmod -R u=r $(INSTALL_DIR)/pic
	@chmod -R u=r $(INSTALL_DIR)/snd

#install updater
	@cp ./linux_only_tools/updater.sh $(INSTALL_DIR)/$(BUILD)_updater.sh
	@chmod +x $(INSTALL_DIR)/$(BUILD)_updater.sh
	
#install desktop/start menu shortcut
	@cp ./linux_only_tools/$(BUILD).desktop $(DESKTOP_SHORTCUT_DIR)/$(BUILD).desktop
	@chmod +x $(DESKTOP_SHORTCUT_DIR)/$(BUILD).desktop

	@$(MAKE) clean --no-print-directory
	@echo Installed Successfully!

uninstall:
#create install location
	@rm -rf $(INSTALL_DIR)
	@rm -f /usr/bin/sm64fm

	@echo Deleted Successfully!

debug:
	@$(MAKE) DEBUG=true --no-print-directory
release:
	@$(MAKE) --no-print-directory


touch_all:
	@find . -type f -exec touch {} +

restore_rights:
	@chmod -R +rwx $(BUILD)
	@chmod -R +rwx pic
	@chmod -R +rwx snd
	@chmod -R +rwx src

print_Def:
	@echo $(DEFINES)