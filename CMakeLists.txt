cmake_minimum_required(VERSION 3.5)
project(qreader_proj)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src/third_party/spdlog)
add_subdirectory(src/tests)
add_subdirectory(src/qreader)
