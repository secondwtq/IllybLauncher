cmake_minimum_required(VERSION 3.0)
project(illyb_launcher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL")

set(SOURCE_FILES main.cxx)
add_executable(illyb_launcher ${SOURCE_FILES} main.cxx)

target_include_directories(illyb_launcher PUBLIC "/usr/local/lib/wx/include/osx_cocoa-unicode-3.0"
                                                "/usr/local/include/wx-3.0")

target_link_libraries(illyb_launcher wx_baseu-3.0)
target_link_libraries(illyb_launcher wx_osx_cocoau_core-3.0)

find_library(FRAMEWORK_CORE_FOUNDATION CoreFoundation)
target_link_libraries(illyb_launcher ${FRAMEWORK_CORE_FOUNDATION})
