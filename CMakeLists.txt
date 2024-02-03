cmake_minimum_required(VERSION 3.10)
project(Serial)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include(FindPkgConfig)
pkg_search_module(LIBUSB1 REQUIRED libusb-1.0)
include_directories(${LIBUSB1_INCLUDE_DIRS})

# Include directories
include_directories(src)
include_directories(src/terminal)
include_directories(src/devices)


# Main application
add_executable(
    serial 
    main.cpp
    src/terminal/terminal.cpp
)
target_link_libraries(serial ${CURSES_LIBRARIES})

# Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test terminal
add_executable(
    serial_test 
    src/terminal/tests/terminal.test.cpp 
    src/terminal/terminal.cpp
)
target_link_libraries(serial_test gtest gtest_main pthread ${CURSES_LIBRARIES})
# add_executable(serial_test ./src/terminal/tests/terminal.test.cpp)
# target_link_libraries(serial_test ${GTEST_LIBRARIES} pthread)

add_executable(
    devices_test
    src/devices/tests/devices.test.cpp
    src/devices/devices.cpp
    src/devices/device.cpp
)
target_link_libraries(devices_test gtest gtest_main pthread ${LIBUSB1_LIBRARIES})