@echo off
chcp 65001 > nul
setlocal
echo @echo off > "%~dp0/deactivate_conanrunenv-release-x86_64.bat"
echo echo Restoring environment >> "%~dp0/deactivate_conanrunenv-release-x86_64.bat"
for %%v in (MARIADB_PLUGIN_DIR OPENSSL_MODULES) do (
    set foundenvvar=
    for /f "delims== tokens=1,2" %%a in ('set') do (
        if /I "%%a" == "%%v" (
            echo set "%%a=%%b">> "%~dp0/deactivate_conanrunenv-release-x86_64.bat"
            set foundenvvar=1
        )
    )
    if not defined foundenvvar (
        echo set %%v=>> "%~dp0/deactivate_conanrunenv-release-x86_64.bat"
    )
)
endlocal


set "MARIADB_PLUGIN_DIR=C:/Users/lz128/.conan2/p/b/maria35652cb81277f/p/lib/plugin;%MARIADB_PLUGIN_DIR%"
set "OPENSSL_MODULES=C:\Users\lz128\.conan2\p\b\opens21b806a7330d9\p\lib\ossl-modules"