cmake_minimum_required(VERSION 3.17)
project(SplayTree)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADER_FILES
    *.hpp
    *.inl
)

file(GLOB SOURCE_FILES
    *.cpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})