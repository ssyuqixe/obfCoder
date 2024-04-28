cmake_minimum_required(VERSION 3.0...3.7)
project(obfcoder VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if (NOT Qt5_FOUND)
    set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")
endif()

find_package(Qt5 CONFIG COMPONENTS Widgets REQUIRED)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    set(OPENSSL_USE_STATIC_LIBS TRUE)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(windeployqt)
#include(openSSLcopy)

set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

set(OBF_SOURCES
    src/main.cpp
    src/GUI.cpp
    src/Parser.cpp
    src/Settings.cpp
    src/Encryption.cpp
    src/Junker.cpp
    src/FileHandling.cpp
    src/Manager.cpp
	src/Comments.cpp
	src/Looper.cpp
	src/Enters.cpp
	src/Renamer.cpp
	src/Spaces.cpp
    )
    
    set(OBF_HEADERS
    inc/GUI.h
    inc/Parser.h
    inc/Settings.h
    inc/Encryption.h
    inc/Junker.h
    inc/FileHandling.h
    inc/Component.h
    inc/Manager.h
	inc/Comments.h
	inc/Looper.h
	inc/Enters.h
	inc/Renamer.h
	inc/Spaces.h
    inc/GUI.ui
    )

add_executable(${PROJECT_NAME}
    WIN32 # remove console 
    ${OBF_SOURCES}
    ${OBF_HEADERS}
)
include_directories(src)
include_directories(inc)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets OpenSSL::SSL OpenSSL::Crypto)

# Copy needed Qt libraries
windeployqt(${PROJECT_NAME})
# Copy needed OpenSSL library
# openSSLcopy(${PROJECT_NAME})