# User Variables
set (SUPPORT_FUNCTION_CALL_TRACE 1)

# NO DATA FOR SECTION: Custom additions (begin)

# Common Include
include (${CAMX_PATH}/build/infrastructure/linuxembedded/common.cmake)

# Files and Build Type
add_library( camxswlfdmanager
    ../../camxfdmanagernode.cpp
    ../../camxfdutils.cpp
    ../../camxfdasserts.cpp
)

# Libraries to compile
target_link_libraries (camxswlfdmanager camxcore)
target_link_libraries (camxswlfdmanager libcamxfdengine)

# Include Paths
include_directories (${CAMX_C_INCLUDES})
include_directories (../..)
include_directories (${CAMX_CDK_PATH}/fd)
include_directories (${CAMX_CDK_PATH}/generated/g_facedetection)
include_directories (../../../../../hwl/titan17x)
include_directories (../../../../../hwl/fd)
include_directories (../../../../../hwl/titan17x/regmap/titan170)
include_directories (../../../../../core)
include_directories (../../../../../core/ncs)
include_directories (../..)
include_directories (${CAMX_SYSTEM_PATH}/fd/fdengine/inc)
include_directories (${CAMX_SYSTEM_PATH}/swprocessalgo/inc)
# Dependencies


# Definitions
add_definitions (${CAMX_CFLAGS})
add_definitions (${CAMX_CPPFLAGS})
# NO DATA FOR SECTION: Custom additions (end)

# Auto-Gen
#add_dependencies(camxswlfdmanager autogen)

if (CONFIG STREQUAL "Debug")
    add_definitions( -g )
endif()

