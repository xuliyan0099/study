# User Variables
set (SUPPORT_FUNCTION_CALL_TRACE 1)

# NO DATA FOR SECTION: Custom additions (begin)

# Common Include
include (${CAMX_PATH}/build/infrastructure/linuxembedded/common.cmake)

# Files and Build Type
add_library( camxhwlbps
    ../../camxbpsnode.cpp
)

# Libraries to compile
target_link_libraries (camxhwlbps camxhwliqmodule)
target_link_libraries (camxhwlbps camxcore)
target_link_libraries (camxhwlbps striping)

# Include Paths
include_directories (${CAMX_C_INCLUDES})
include_directories (../..)
include_directories (../..)
include_directories (../../../iqsetting)
include_directories (../../../ispiqmodule)
include_directories (../../../titan17x)
include_directories (../../../titan17x/regmap/titan170)
#include_directories (${CAMX_OUT_HEADERS})
#include_directories (system/media/camera/include)
include_directories (${CAMX_EXT_INCLUDE}/system)
include_directories (${CAMX_SYSTEM_PATH}/stripinglib/external/utils/inc)
include_directories (${CAMX_SYSTEM_PATH}/stripinglib/common/inc)

if(IQSETTING EQUAL "OEM1")
include_directories (${CAMX_OEM1IQ_PATH}/iqsetting)
else()
include_directories (../../../iqinterpolation)
endif()
# Dependencies


# Definitions
add_definitions (${CAMX_CFLAGS})
add_definitions (${CAMX_CPPFLAGS})
# NO DATA FOR SECTION: Custom additions (end)

# Auto-Gen
#add_dependencies(camxhwlbps autogen)

if (CONFIG STREQUAL "Debug")
    add_definitions( -g )
endif()

