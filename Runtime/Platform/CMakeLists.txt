# Add Source Files
set (
    PLATFORM_SOURCE
    Process.cpp
)

#Add Header Files
set (
    PLATFORM_HEADER
)

# Create Library
add_library(
    helianthus_platform STATIC
    ${PLATFORM_SOURCE}
    ${PLATFORM_HEADER}
)

include_directories(${CMAKE_SOURCE_DIR}/Runtime)

target_include_directories(
    helianthus_platform PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> # For users of the installed library
    $<INSTALL_INTERFACE:include/helianthus/Platform> # For users of the installed library
)

# link dependencies
target_link_libraries(
    helianthus_platform PUBLIC
)

# Set Build Settings
target_compile_features(helianthus_platform PUBLIC cxx_std_20)

# Set Preprocessor Definitions
target_compile_definitions(
    helianthus_platform PUBLIC 
    HELIANTHUS_ENABLE_PLATFORM=1
)

# Set Build Options
if (MSVC)
    target_compile_options(
        helianthus_platform PRIVATE
        /W4
    )
else()
    target_compile_options(
        helianthus_platform PRIVATE
        -Wall -Wextra
    )
endif()

set_target_properties(
    helianthus_platform PROPERTIES
    OUTPUT_NAME "helianthus_platform"
)
