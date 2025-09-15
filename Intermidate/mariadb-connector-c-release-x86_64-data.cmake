########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(mariadb-connector-c_COMPONENT_NAMES "")
if(DEFINED mariadb-connector-c_FIND_DEPENDENCY_NAMES)
  list(APPEND mariadb-connector-c_FIND_DEPENDENCY_NAMES CURL ZLIB zstd)
  list(REMOVE_DUPLICATES mariadb-connector-c_FIND_DEPENDENCY_NAMES)
else()
  set(mariadb-connector-c_FIND_DEPENDENCY_NAMES CURL ZLIB zstd)
endif()
set(CURL_FIND_MODE "NO_MODULE")
set(ZLIB_FIND_MODE "NO_MODULE")
set(zstd_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(mariadb-connector-c_PACKAGE_FOLDER_RELEASE "C:/Users/lz128/.conan2/p/b/maria35652cb81277f/p")
set(mariadb-connector-c_BUILD_MODULES_PATHS_RELEASE )


set(mariadb-connector-c_INCLUDE_DIRS_RELEASE "${mariadb-connector-c_PACKAGE_FOLDER_RELEASE}/include"
			"${mariadb-connector-c_PACKAGE_FOLDER_RELEASE}/include/mariadb")
set(mariadb-connector-c_RES_DIRS_RELEASE )
set(mariadb-connector-c_DEFINITIONS_RELEASE )
set(mariadb-connector-c_SHARED_LINK_FLAGS_RELEASE )
set(mariadb-connector-c_EXE_LINK_FLAGS_RELEASE )
set(mariadb-connector-c_OBJECTS_RELEASE )
set(mariadb-connector-c_COMPILE_DEFINITIONS_RELEASE )
set(mariadb-connector-c_COMPILE_OPTIONS_C_RELEASE )
set(mariadb-connector-c_COMPILE_OPTIONS_CXX_RELEASE )
set(mariadb-connector-c_LIB_DIRS_RELEASE "${mariadb-connector-c_PACKAGE_FOLDER_RELEASE}/lib")
set(mariadb-connector-c_BIN_DIRS_RELEASE )
set(mariadb-connector-c_LIBRARY_TYPE_RELEASE STATIC)
set(mariadb-connector-c_IS_HOST_WINDOWS_RELEASE 1)
set(mariadb-connector-c_LIBS_RELEASE mariadbclient)
set(mariadb-connector-c_SYSTEM_LIBS_RELEASE ws2_32 shlwapi secur32)
set(mariadb-connector-c_FRAMEWORK_DIRS_RELEASE )
set(mariadb-connector-c_FRAMEWORKS_RELEASE )
set(mariadb-connector-c_BUILD_DIRS_RELEASE )
set(mariadb-connector-c_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(mariadb-connector-c_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${mariadb-connector-c_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${mariadb-connector-c_COMPILE_OPTIONS_C_RELEASE}>")
set(mariadb-connector-c_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${mariadb-connector-c_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${mariadb-connector-c_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${mariadb-connector-c_EXE_LINK_FLAGS_RELEASE}>")


set(mariadb-connector-c_COMPONENTS_RELEASE )