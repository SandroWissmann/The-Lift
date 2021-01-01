cmake_minimum_required(VERSION 3.5)

project(Lift_test LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(
    Lift_test
    tst_lift_test.cpp
    ../TheLift/lift.cpp
    )
add_test(NAME Lift_test COMMAND Lift_test)

target_link_libraries(Lift_test PRIVATE Qt${QT_VERSION_MAJOR}::Test)

