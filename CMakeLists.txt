cmake_minimum_required(VERSION 3.28)
project(experiments-ref-count)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

include(FindThreads)

# Add your executable
add_executable(experiments-ref-count src/main.cpp)

# Link nanobench to your executable
target_link_libraries(experiments-ref-count PRIVATE nanobench Threads::Threads fmt)

add_subdirectory(external)
