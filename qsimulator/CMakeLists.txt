cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

add_subdirectory(quantum-engine)

set(TARGET qsimulator)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${TARGET} SHARED src/simulator.cpp)

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC
        GSL
        qengine
)
