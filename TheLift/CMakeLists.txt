cmake_minimum_required(VERSION 3.14)

project(TheLift LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        backend.h
        backend.cpp
        building.h
        building.cpp
        floor.h
        floor.cpp
        floormodel.h
        floormodel.cpp
        lift.h
        lift.cpp
        liftmanagercontroller.h
        liftmanagercontroller.cpp
        liftmanagerworker.h
        liftmanagerworker.cpp
        main.cpp
        qml.qrc
)

qt_add_executable(TheLift
    ${PROJECT_SOURCES}
)

target_compile_definitions(TheLift
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(TheLift
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
