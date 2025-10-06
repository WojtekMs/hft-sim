cmake_minimum_required(VERSION 3.30)

project(HFT-Sim CXX)

option(ENABLE_UT "Build project with unit tests" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(ENABLE_UT)
    include(FetchCatch2)
endif()

add_subdirectory(src)
