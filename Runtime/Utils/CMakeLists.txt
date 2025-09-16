# Add Source Files
set (
    UTILS_SOURCE
    StringUtils.cpp
)

#Add Header Files
set (
    UTILS_HEADER
    StringUtils.h
)

# Create Library
add_library(
    helianthus_utils STATIC
    ${UTILS_SOURCE}
    ${UTILS_HEADER}
)

include_directories(${CMAKE_SOURCE_DIR}/Runtime)

target_include_directories(
    helianthus_utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> # For users of the installed library
    $<INSTALL_INTERFACE:include/helianthus/Utils> # For users of the installed library
)

# link dependencies
target_link_libraries(
    helianthus_utils PUBLIC
)

# Set Build Settings
target_compile_features(helianthus_utils PUBLIC cxx_std_20)

# Set Preprocessor Definitions
target_compile_definitions(
    helianthus_utils PUBLIC 
    HELIANTHUS_ENABLE_UTILS=1
)

# Set Build Options
if (MSVC)
    target_compile_options(
        helianthus_utils PRIVATE
        /W4
    )
else()
    target_compile_options(
        helianthus_utils PRIVATE
        -Wall -Wextra
    )
endif()

set_target_properties(
    helianthus_utils PROPERTIES
    OUTPUT_NAME "helianthus_utils"
)
