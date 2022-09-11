cmake_minimum_required(VERSION 3.10)
project(agm-renderer)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)
find_package(OpenMP REQUIRED)

set(SRCS
    src/main.cpp
)

add_executable(agm-renderer ${SRCS})
target_include_directories(agm-renderer PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(agm-renderer PRIVATE -Wall)
target_link_libraries(agm-renderer PRIVATE fmt::fmt-header-only OpenMP::OpenMP_CXX)
