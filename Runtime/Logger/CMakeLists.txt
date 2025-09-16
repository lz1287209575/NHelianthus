# Add Source Files
set (
    LOGGER_SOURCE
    LoggerManager.cpp
)

#Add Header Files
set (
    LOGGER_HEADER
    LoggerManager.h
    LoggerConfig.h
    LogLevel.h
    BaseLogger.h
    SimpleLogger.h
    CategoryLogger.h
    StructedLogger.h
)

include_directories(${CMAKE_SOURCE_DIR}/Runtime)

# Create Library
add_library(
    helianthus_logger STATIC
    ${LOGGER_SOURCE}
    ${LOGGER_HEADER}
)

target_include_directories(
    helianthus_logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> # For users of the installed library
    $<INSTALL_INTERFACE:include/helianthus/Logger> # For users of the installed library
)

# link dependencies
target_link_libraries(
    helianthus_logger PUBLIC
    spdlog::spdlog
)

# Set Build Settings
target_compile_features(helianthus_logger PUBLIC cxx_std_20)

# Set Preprocessor Definitions
target_compile_definitions(
    helianthus_logger PUBLIC 
    HELIANTHUS_ENABLE_LOGGING=1
)

# Set Build Options
if (MSVC)
    target_compile_options(
        helianthus_logger PRIVATE
        /W4
    )
else()
    target_compile_options(
        helianthus_logger PRIVATE
        -Wall -Wextra
    )
endif()

set_target_properties(
    helianthus_logger PROPERTIES
    OUTPUT_NAME "helianthus_logger"
)
