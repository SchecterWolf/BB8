BB8_DIR?=./
TARGET_BASE_DIR?=$(BB8_DIR)target/
BUILD_BASE_DIR?=$(BB8_DIR)build/

# Initialize make environment
include $(BUILD_BASE_DIR)Base.mk

# BB8 Foreign
include $(BB8_DIR)$(TARGET_BASE_DIR)Foreign.mk

# Defaults
WARNINGS:=$(filter-out -Wswitch-enum, $(WARNINGS))
ifneq (,$(findstring -Wswitch-default, $(WARNINGS)))
	WARNINGS+=-Wswitch-default
endif
CFLAGS:=$(filter-out -Winline, $(CFLAGS))

all: bin

clean:
	rm -rf $(BUILD_DIR)

$(BB8_TARGET)deps:
	$(MKDIR) $(BB8_TARGET)
	@touch $(BB8_TARGET)deps

#
# Application
#
bin: $(BB8_FINAL)

$(BB8_FINAL): $(OBJS) $(BB8_TARGET)main.o
	$(CXX) $(OBJS) $(BB8_TARGET)main.o $(LDFLAGS) -o $(BB8_FINAL)

#
# Intermediate objects
#
$(BB8_TARGET)%.o: %.cpp
	$(MKDIR) $(shell dirname $@)
	$(CXX) $(DEPFLAGS) $(INCLUDE_FLAGS) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	$(POSTCOMPILE)

# Dones use error flags on main
$(BB8_TARGET)main.o: $(SRC_MAIN)main.cpp
	$(CXX) $(DEPFLAGS) $(INCLUDE_FLAGS) $(CPPFLAGS) -c $< -o $@

%.d: ;
