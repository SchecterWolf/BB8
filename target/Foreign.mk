# Foreign.mk
# Sets up the target build environment variables for the a Makefile
#
# Input:
# 			TARGET 		Target name
# 			OBJS 		intermediate object files
# 			OBJDIR 		intermediate output directory
#
# Output:
# 			BUILD_DIR 	Target directory
# 			BB8_TARGET 	Target objects and deps directory
# 			BB8_NAME 	target name
# 			BB8_BIN 	binary directory name
# 			BB8_FINAL 	executable name
#

BB8_DIR?=../
INSTALL_DIR?=/usr/local/

#
# Config
#
BUILD_DIR=$(BB8_DIR)target/$(TARGET)/
BB8_TARGET=$(BUILD_DIR).obj/
BB8_NAME=BB-Boot
BB8_BIN=$(BB8_NAME)$(BINEXT)
BB8_FINAL=$(BUILD_DIR)$(BB8_BIN)

# OBJDIR should be aliased
OBJDIR=$(BB8_TARGET)

# Include any dependency files if they exist
#ifndef NO_DEP
#-include $(DEPS)
#endif

#
# Flags
#
#CFLAGS+=-I$(BB8_INC)
ifeq ($(OS), linux)
	LDFLAGS+=-lpthread -ldl
endif

#
# Make Directives
#
bb8-make:
	$(MKDIR) $(TARGET_DIR)
	cd $(TARGET_DIR) && (ln -s $(TARGET_REL)$(BB8_FINAL_BIN) $(BB8_BIN) 2> /dev/null || true)

bb8-clean:
	rm -f $(TARGET_DIR)$(BB8_BIN) $(TARGET_DIR)$(BB8_LIB) $(TARGET_DIR)$(BB8_ARCH)
