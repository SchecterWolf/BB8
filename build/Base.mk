# Base.mk
# Sets up the Makefile common variables and source objects
#
# Input:
# 			TARGET_BASE_DIR 	base target directory for the build
# 			BUILD_BASE_DIR 		base build directory
#
# Output:
# 			BINEXT 		OS defined extension
# 			MKDIR 		Make directory command
#
# 			CXXFLAGS 	c++ flags
# 			FINAL_FLAGS 	additional flags for main make target
# 			FLAGS 		top level directive flags
# 			CXX 		compiler
# 			LDFLAGS 	flags for the linker
#
# 			OBJS 		Source objects in this build
# 			DEPS 		Dependency files
# 			DEPFLAGS 	dependency compiler flags
# 			POSTCOMPILE rename dependency files that succeed compilation	
#
# 			TARGET_DIR 	final output directory
# 			OBJDIR 		intermediate output directory (should be overriden in Foreign.mk)

# Default build targer
TARGET?=x86-linux

# Directories
TARGET_DIR?=$(TARGET_BASE_DIR)$(TARGET)/
OBJDIR = $(TARGET_DIR).obj/

# Include the list of directories
include $(BUILD_BASE_DIR)Directories.mk

# Make directory command
MKDIR=@mkdir -p

# C++ flags
CPPFLAGS+=-ggdb3 -std=c++0x -O0
CXXFLAGS+=-Wall -Werror -Wformat=2 -Wno-write-strings \
			-Wno-variadic-macros -Wno-unused-parameter -fno-omit-frame-pointer \
			-fno-common -Wno-strict-aliasing \
			-Wunreachable-code -Wlogical-op -Wstrict-overflow=1 \
			-ffloat-store -Wpointer-arith -Winline -Wundef -Wfloat-equal -Wcast-align \
			-fstrict-aliasing -Wstrict-aliasing=2 -Wswitch-default \
			-Wvariadic-macros -Wunused-parameter -fomit-frame-pointer \
			-Wformat-security -Werror=format-security -Wno-parentheses \
			-Wno-overloaded-virtual -Wno-unused-function -c
FINAL_FLAGS+=-Wno-unused-function

# utilize the gnu compiler to make temporary dependency files
DEPFLAGS+=-MMD -MP -MF $*.Td

# Each module.mk will append to this
SRC :=

# Sources
# main.cpp should not be included in any module.mk, otherwise mutilple
# mains will be included in the binaries
include $(patsubst %,%/module.mk,$(SRC_MODULES))

SRC_CXX := $(filter %.cpp,$(SRC))
OBJS += $(SRC_CXX:%.cpp=$(OBJDIR)%.o)
DEPS += $(OBJS:%.o=%.d)

# Include flags
INCLUDE_FLAGS=$(patsubst %,-I%,$(INCLUDES))

# Only keep temporary dependency files that succeed compilation
POSTCOMPILE = mv -f $*.Td $(OBJDIR)$*.d

# Linker flags
LDFLAGS?=

# Target specific variables
ifeq ($(TARGET), x86-linux)
	CXX=g++
	OS=linux
else ifeq ($(TARGET), aarch64-linux-gnu-g++-4.8)
	CXX=aarch64-linux-gnu-g++-4.8
	OS=linux
else ifeq ($(TARGET), arm-linux-gnueabihf-g++-4.8)
	CXX=arm-linux-gnueabihf-g++-4.8
	OS=linux
else
	$(error Invalid target: $(TARGET))
endif

# OS defined naming conventions
ifeq ($(OS), linux)
	BINEXT?=
endif

# Default directive = 'all'
__first: all

full: clean all

# Make
arm64:
	$(MAKE) all TARGET=aarch64-linux-gnu-g++-4.8

arm32:
	$(MAKE) all TARGET=arm-linux-gnueabihf-g++-4.8

# Clean
cleanarm64:
	$(MAKE) clean TARGET=aarch64-linux-gnu-g++-4.8

cleanarm32:
	$(MAKE) clean TARGET=arm-linux-gnueabihf-g++-4.
