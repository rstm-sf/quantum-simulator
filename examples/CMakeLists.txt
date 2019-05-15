cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(TARGET example-simulator)

project(${TARGET})

add_executable(${TARGET}
    example-simulator.cpp
)

target_compile_features(${TARGET} PUBLIC cxx_std_17)

target_link_libraries(${TARGET}
    PRIVATE
        qsimulator
)
