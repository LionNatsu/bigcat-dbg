cmake_minimum_required(VERSION 3.2)
project(bigcat-dbg)

set(CMAKE_CXX_STANDARD 11)

add_executable(load-shlib load-shlib.c)
target_link_libraries(load-shlib dl)

install(
    TARGETS
    load-shlib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
