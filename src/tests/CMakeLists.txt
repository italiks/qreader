cmake_minimum_required(VERSION 3.5)

project(CommandLineParser LANGUAGES CXX)


find_package(Qt5Test REQUIRED)
find_package(Qt5Gui REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(CommandLineParser tst_commandlineparser.cpp
    ${CMAKE_SOURCE_DIR}/src/qreader/commandlineparser.cpp)
add_test(NAME CommandLineParser COMMAND CommandLineParser)

target_link_libraries(CommandLineParser PRIVATE Qt5::Gui Qt5::Test)

message ("include path - " ${CMAKE_SOURCE_DIR})
target_include_directories (CommandLineParser PRIVATE ${CMAKE_SOURCE_DIR}/src/qreader)

