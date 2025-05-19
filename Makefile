CCX ?= g++
CC ?= gcc

ifeq ($(CCX), clang)
CC := clang
OPT_FLAGS := -fno-stack-protector -flto -funsafe-math-optimizations -fno-signed-zeros -fcf-protection=none -mtune=native -fomit-frame-pointer
WARN_FLAGS := -Wno-inconsistent-missing-override -Wno-unused-result -Wno-unknown-pragmas -Wno-unused-function -Wno-write-strings
else
OPT_FLAGS := -fno-stack-protector -finline-small-functions -flto -faggressive-loop-optimizations -funsafe-math-optimizations -fno-signed-zeros -fsingle-precision-constant -fcf-protection=none -fvtable-verify=none -mtune=native -fomit-frame-pointer
WARN_FLAGS := -Wno-unused-result -Wno-unknown-pragmas -Wno-unused-function -Wno-write-strings
endif

UNAME = $(shell uname)

ALL_DYNAMIC ?= true
ifeq ($(TARGET), win32)
DYNAMIC_LIBS_LIST = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lcomdlg32 -lstdc++fs -static-libgcc -static -pthread
else
STATIC_LIBS_LIST = -lc -lgcc -lstdc++ -lX11 -lstdc++fs -lxcb -lXau -lXdmcp
DYNAMIC_LIBS_LIST = -lGL -ldl -lm -lpthread
endif

ifeq ($(ALL_DYNAMIC), true)
DYNAMIC_LIBS := $(DYNAMIC_LIBS_LIST) $(STATIC_LIBS_LIST)
else
STATIC_LIBS := $(STATIC_LIBS_LIST)
DYNAMIC_LIBS := $(DYNAMIC_LIBS_LIST)
endif


PIXEL_GAME_ENGINE_ARGS := -std=c++17
CC_ARGS = $(WARN_FLAGS)
CCX_ARGS = $(WARN_FLAGS) $(PIXEL_GAME_ENGINE_ARGS)

ifeq ($(TARGET), win32)
PIXEL_GAME_ENGINE_ARGS += -static-libstdc++
DEFINES_DEF =
else
DEFINES_DEF = DATE="\"`date`\"" VER="\"$(VERSION)\"" PROG_NAME="\"$(BUILD)\"" OS_CLEAR="\"$(OS_CLEAR)\"" 
#FORCE_EXPERIMENTAL_FS
endif

ODIR ?= build

ROOT_DIRECTORY=.
SOURCES := ${shell find ${ROOT_DIRECTORY} -type d -print}
INCLUDE := ./include

C_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.c) )
C_FILES := $(filter-out ./include/sound/stb_vorbis.c,$(C_FILES))
CPP_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.cpp) ) #$(wildcard *.cpp)
ifeq ($(TARGET), win32)
CPP_FILES := $(filter-out ./include/filesys/os/Linux/XFileSelector/utils/Window.cpp,$(CPP_FILES))
CPP_FILES := $(filter-out ./include/filesys/os/Linux/XFileSelector/utils/MainWin.cpp,$(CPP_FILES))
CPP_FILES := $(filter-out ./include/filesys/os/Linux/XFileSelector/FileSelect.cpp,$(CPP_FILES))
endif
H_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.h) ) $(wildcard *.h)

ASM_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.asm) ) $(wildcard *.asm)
S_FILES := $(foreach dir,$(SOURCES),  $(wildcard $(dir)/*.s) ) $(wildcard *.s)

O_FILES = $(abspath $(addprefix $(ODIR)/, $(CPP_FILES:.cpp=.o))) $(abspath $(addprefix $(ODIR)/, $(C_FILES:.c=.o)))



VERSION := 1.1
BUILD ?= sm64sfm
DEFINE_PREFIX ?= -
OS_CLEAR ?= clear

FORCE_EXPERIMENTAL_FS ?= true
DEBUG ?= false


ifeq ($(DEBUG), true)
DEFINES_DEF += DEBUG=$(DEBUG)
CC_ARGS += -g -pg
CCX_ARGS += -g -pg

CC_ARGS += -Wall -Wfatal-errors -Wall -Wextra
CCX_ARGS +=  -Wall  -Wfatal-errors -Wall -Wextra

#CC_ARGS += -Og
#CCX_ARGS += -Og
else
CC_ARGS += -Ofast
CCX_ARGS += -Ofast

CC_ARGS += $(OPT_FLAGS)
CCX_ARGS += $(OPT_FLAGS)
endif

DEFINES = $(foreach def,$(DEFINES_DEF), $(DEFINE_PREFIX)D$(def))


$(ODIR)/./%.o : %.cpp
	@echo $(notdir $(basename $*)).cpp
	@mkdir -p $(dir $@)
	@$(CCX) -c $*.cpp -o $@ -I $(INCLUDE) $(CCX_ARGS) $(DEFINES)

$(ODIR)/./%.o : %.c
	@echo $(notdir $(basename $*)).c
	@mkdir -p $(dir $@)
	@$(CC) -c $*.c -o $@ -I $(INCLUDE) $(CC_ARGS) $(DEFINES)
	
	
THREAD_COUNT ?= $(grep -c processor /proc/cpuinfo)
RELEASE_FOLDER ?= release_build
DEBUG_FOLDER ?= debug_build

.PHONY: all
.PHONY: message
.PHONY: compile
.PHONY: release_compile
.PHONY: build
.PHONY: debug
.PHONY: release

$(BUILD): release

all: clean compile run


compile: $(addprefix $(ODIR)/, $(CPP_FILES:.cpp=.o)) $(addprefix $(ODIR)/, $(C_FILES:.c=.o)) | $(ODIR)
	@echo "Linking ..."
#$(CCX) $(O_FILES) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(CCX_ARGS) $(DEFINES) $(DYNAMIC_LIBS) ${shell ./maybestatic.sh  $(STATIC_LIBS) }
	@$(CCX) $(O_FILES) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(CCX_ARGS) $(DEFINES) $(DYNAMIC_LIBS)

#@printf " $(subst ",\", ${shell ./maybestatic.sh  $(STATIC_LIBS) })" >> link.sh
#	@chmod +x ./link.sh
#	@./link.sh
	@echo "\033[32;1mDone!\033[30;0m"


release_compile: compile
	@strip $(BUILD) -o $(BUILD).tmp
	@mv $(BUILD).tmp $(BUILD)

message:
	@echo Building ...
	@echo "\tDebug Build = $(DEBUG)"
	@echo "\tTarget = $(UNAME)"
	@echo "\tVersion = $(VERSION)"
	@echo "\tC++ Files to Compile = $(words $(CPP_FILES))"
	@echo "\tC Files to Compile = $(words $(C_FILES))"
	
$(ODIR):
	@mkdir -p $@

link:
	@echo $(CCX) $(O_FILES) -o $(BUILD) -I $(INCLUDE) $(CC_ARGS) $(CCX_ARGS) $(DEFINES)

run:
	@./$(BUILD)

clean:
	@rm -rf $(ODIR)
	@rm -rf $(RELEASE_FOLDER)
	@rm -rf $(DEBUG_FOLDER)
	@rm -rf x64
	@rm -rf Debug
	@rm -rf Release
	@rm -rf .vs
	@rm -rf $(BUILD)

debug:
	@$(MAKE) message DEBUG=true --no-print-directory
	@$(MAKE) -j $(THREAD_COUNT) compile ODIR="$(DEBUG_FOLDER)" DEBUG=true --no-print-directory

release:
	@$(MAKE) message --no-print-directory
	@$(MAKE) -j $(THREAD_COUNT) release_compile ODIR="$(RELEASE_FOLDER)" --no-print-directory

DESKTOP_SHORTCUT_DIR = /usr/share/applications
install:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) compile -j $(THREAD_COUNT) --no-print-directory
#files belong to root now so allow all users to access them again
	@chmod -R +rwx build
	@mkdir -p /usr/local/bin
	@cp ./$(BUILD) /usr/local/bin
	@chmod +x /usr/local/bin/$(BUILD)
	
#install desktop/start menu shortcut
	@cp ./linux_only_tools/$(BUILD).desktop $(DESKTOP_SHORTCUT_DIR)/sm64sfm.desktop
	@chmod +x $(DESKTOP_SHORTCUT_DIR)/sm64sfm.desktop

	@$(MAKE) clean --no-print-directory
	@echo Installed Successfully!

uninstall:
#create install location
	@rm -rf $(INSTALL_DIR)
	@rm -f /usr/bin/sm64fm

	@echo Deleted Successfully!
