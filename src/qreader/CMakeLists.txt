cmake_minimum_required(VERSION 3.5)

project(qreader LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)

set(TS_FILES qreader_en_US.ts)

if(ANDROID)
    add_library(qreader SHARED
      main.cpp
      qml.qrc
      ${TS_FILES}
    )
else()
    add_executable(qreader
      main.cpp
      commandlinearguments.h
      commandlineparser.h
      commandlineparser.cpp
      qreaderapplication.h
      qreaderapplication.cpp
      qml.qrc
      ${TS_FILES}
    )
endif()

target_include_directories(qreader PRIVATE ${CMAKE_SOURCE_DIR}/src/third_party/spdlog/include)

target_compile_definitions(qreader
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qreader
  PRIVATE Qt5::Core Qt5::Quick)

target_link_libraries(qreader PRIVATE spdlog_header_only)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
