# Add Subdirectory

add_subdirectory(Logger)

# Create Main Library
add_library(helianthus_runtime INTERFACE)

# Set Include Directory
target_include_directories(
    helianthus_runtime INTERFACE
    $<BUILD_INTERFACE:$(CMAKE_SOURCE_DIR)/Runtime>
    $<BUILD_INTERFACE:$(CMAKE_SOURCE_DIR)>
    $<INSTALL_INTERFACE:include/helianthus> # For users of the installed library
)

# Link Sub Libraries
target_link_libraries(
    helianthus_logger
)

# Set Build Settings
target_compile_features(helianthus_runtime INTERFACE cxx_std_20)

#Set Target Library
target_link_libraries(helianthus_runtime INTERFACE ${HELIANTHUS_LIBS})
