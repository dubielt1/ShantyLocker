cmake_minimum_required(VERSION 3.6)
project(ShantyLocker)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(ImageMagick COMPONENTS Magick++)
find_package(XCB REQUIRED)
find_package(XCB-UTIL REQUIRED)
find_package(XCB-EWMH REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp xcbutil/xcbutil.cpp obscure/obscure.cpp)
add_executable(ShantyLocker ${SOURCE_FILES})

# Local include dir
include_directories(${CMAKE_SOURCE_DIR}/include)

# Magick++
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(ShantyLocker ${ImageMagick_LIBRARIES})

# XCB-UTIL
include_directories(${LIBXCB-UTIL_INCLUDE_DIRS})
target_link_libraries(ShantyLocker ${LIBXCB-UTIL_LIBRARIES})

# XCB-EWMH
include_directories(${LIBXCB-EWMH_INCLUDE_DIRS})
target_link_libraries(ShantyLocker ${LIBXCB-EWMH_LIBRARIES})

# XCB
include_directories(${LIBXCB_INCLUDE_DIRS})
target_link_libraries(ShantyLocker ${LIBXCB_LIBRARIES})