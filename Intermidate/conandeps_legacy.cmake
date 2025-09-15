message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(GTest)
find_package(spdlog)
find_package(nlohmann_json)
find_package(hiredis)
find_package(mariadb-connector-c)
find_package(OpenSSL)
find_package(ZLIB)
find_package(lz4)
find_package(zstd)

set(CONANDEPS_LEGACY  gtest::gtest  spdlog::spdlog  nlohmann_json::nlohmann_json  hiredis::hiredis  mariadb-connector-c::mariadb-connector-c  openssl::openssl  ZLIB::ZLIB  LZ4::lz4_static  zstd::libzstd_static )