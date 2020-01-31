cmake_minimum_required(VERSION 3.2)
project(bigcat-dbg)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-DSYSTEM_DIRS=${SYSTEM_DIRS})
add_compile_options(-Wall -Wextra)
add_compile_options(-g)

include_directories(BEFORE include)

add_library(elf-dependency STATIC lib/elf-dependency.cc)
add_library(ldso-path STATIC lib/ldso-path.cc)

add_executable(ldk-load-lib src/ldk-load-lib.c)
target_link_libraries(ldk-load-lib dl)

add_executable(ldk-depends-lib src/ldk-depends-lib.cc)
target_link_libraries(ldk-depends-lib elf-dependency ldso-path dl)

install(
    TARGETS ldk-load-lib ldk-depends-lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
