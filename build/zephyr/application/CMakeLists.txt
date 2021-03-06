cmake_minimum_required(VERSION 3.11)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(application)

target_sources(app PRIVATE src/runner.c)

set(ROOTDIR "../../..")

# Add libpull to the build
file(GLOB_RECURSE libpull_src ${ROOTDIR}/src/*.c)
file(GLOB libpull_headers ${ROOTDIR}/include)
target_sources(app PRIVATE ${libpull_src})
include_directories(${libpull_headers} ${ROOTDIR})

add_definitions(-DLOGGER_VERBOSITY=4)
add_definitions(-DMEMORY_FLASH_IMPL=1 -DSIMPLE_MANIFEST=1)
add_definitions(-DWITH_UPDATE_AGENT=1 -DWITH_CONNECTION_ZOAP=1)
add_definitions(-DWITH_PLATFORM_NRF52840=1)

set(TINYCRYPT 1) # TINYCRYPT or TINYDTLS or MBEDTLS
if (TINYCRYPT)
    add_definitions(-DWITH_TINYCRYPT=1)
elseif(TINYDTLS)
    add_definitions(-DWITH_TINYDTLS=1)
    include_directories(${ROOTDIR}/ext/tinydtls)
    file(GLOB ecc_src ${ROOTDIR}/ext/tinydtls/ecc/ecc.c)
    file(GLOB sha2_src ${ROOTDIR}/ext/tinydtls/sha2/sha2.c)
    file(GLOB crypto_src ${ROOTDIR}/ext/tinydtls/crypto.c)
    add_definitions(-DWITH_SHA256 -DSHA2_USE_INTTYPES_H)
    target_sources(app PRIVATE ${ecc_src} ${sha2_src} ${crypto_src})
elseif(MBEDTLS)
    add_definitions(-DWITH_MBEDTLS=1)
endif(TINYCRYPT)

# Add the board headers
include_directories(${ROOTDIR}/src/platform/nrf52840)
