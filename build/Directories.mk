###
### Directories.mk
###

# Input:
# 		none
#
# Output:
# 		SRC_MODULES 		src module directories for the build
# 		SRC_MAIN 			directory of the main
# 		INCLUDES 			include directories
#
#
# Containes src directories
# Each src director must contain a module.mk that has:
# 		SRC += $(wildcard <Directory>/*.cpp)
#

# Alphabetical
SRC_MODULES := \
					src/common/commondefs \
					src/controller \
					src/directives/followme \
					src/main/sub \
					src/main/utils \
					src/utils \
					src/utils/log \
					src/utils/macro \


SRC_MAIN := src/main/
INCLUDES := $(SRC_MODULES)
