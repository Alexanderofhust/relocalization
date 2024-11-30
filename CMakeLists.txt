cmake_minimum_required(VERSION 3.20)
project(RelocalizationExample)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
        main.cpp
        Relocalization.cpp
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
