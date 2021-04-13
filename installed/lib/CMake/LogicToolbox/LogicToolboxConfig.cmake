# - Config file for 'LogicToolbox' package
# It defines the following variables
#  LOGICTOOLBOX_INCLUDE_DIRS - include directories
#  LOGICTOOLBOX_LIBRARIES    - libraries to link against

# Include directory
set(LOGICTOOLBOX_INCLUDE_DIRS "/home/hamza/Desktop/LogicToolbox-master/installed/include")

# Import the exported targets
include("/home/hamza/Desktop/LogicToolbox-master/installed/lib/CMake/LogicToolbox/LogicToolboxTargets.cmake")

# Set the expected library variable
set(LOGICTOOLBOX_LIBRARIES logictoolbox)
