###
### Directories.mk
###

# Input:
# 		none
#
# Output:
# 		SRC_MODULES 		src module directories for the build
# 		INCLUDES 			include directories
#
#
# Containes src directories
# Each src director must contain a module.mk that has:
# 		SRC += $(wildcard <Directory>/*.cpp)
#

SRC_MODULES := \
					src/main \
					src/main/utils \
					src/controller \
					src/directives/followme \
					src/common/commondefs \

INCLUDES := $(SRC_MODULES)
