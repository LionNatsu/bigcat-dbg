cmake_minimum_required(VERSION 3.2)
project(bigcat-dbg)

set(CMAKE_CXX_STANDARD 11)

include_directories(BEFORE include)

add_executable(ldk-load-lib src/ldk-load-lib.c)
target_link_libraries(ldk-load-lib dl)

install(
    TARGETS ldk-load-lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
