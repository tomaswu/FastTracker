cmake_minimum_required(VERSION 3.16)

set(name FastTracker)
project(${name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

include_directories(srcs)

cmake_policy(SET CMP0148 NEW)

cmake_host_system_information(RESULT host_name QUERY HOSTNAME)
message("host name is:" ${host_name})
if (${host_name} STREQUAL "TOMASWUFAA0") # mac-win
    set(MSVC_VERSION 1920)
    set(Python_EXECUTABLE C:/Users/tomaswu/miniconda3/envs/py311/python.exe)

    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.6.1/msvc2019_64")
    #list(APPEND CMAKE_PREFIX_PATH "C:/Users/tomaswu/myprograms/opencv/build")
    set(OpenCV_DIR "C:/Users/tomaswu/myprograms/opencv/build")
    list(APPEND CMAKE_PREFIX_PATH "C:/Users/tomaswu/miniconda3/envs/py311/Lib/site-packages/pybind11/share/cmake/pybind11")
    list(APPEND CMAKE_PREFIX_PATH "C:/Users/tomaswu/miniconda3/envs/py311")

    
elseif(${host_name} STREQUAL "TomasdeMacBook-Pro.local") #mac
    list(APPEND CMAKE_PREFIX_PATH /Users/tomaswu/usr/op455/lib/cmake/opencv4)
    # list(APPEND CMAKE_PREFIX_PATH /Users/tomaswu/Qt/6.6.2/macos/lib/cmake)
    list(APPEND CMAKE_PREFIX_PATH "/Users/tomaswu/miniconda3/envs/py311/lib/python3.11/site-packages/pybind11/share/cmake/pybind11")
    list(APPEND CMAKE_PREFIX_PATH "/Users/tomaswu/miniconda3/envs/py311")
    set(Qt6_DIR /Users/tomaswu/Qt/6.6.2/macos/lib/cmake/Qt6)
    include_directories(/Users/tomaswu/Qt/6.6.2/macos/lib/QtWidgets.framework/Versions/A/Headers)
else() # win

endif()

find_package(Python 3.11.8 EXACT COMPONENTS Interpreter Development REQUIRED)
find_package(Qt6 6.6 REQUIRED COMPONENTS Core Gui Widgets Charts)
find_package(OpenCV)
set(PYBIND11_PYHTON_VERSION 3.11)
find_package(pybind11 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Qt6_INCLUDE_DIRS})
message("opencv libs::" ${OpenCV_LIBRARIES})
message("opencv include:"${OpenCV_INCLUDE_DIRS})

file(GLOB srcs  
        "srcs/views/*.h"
        "srcs/views/*.cpp"
        "srcs/views/*.ui"
        "srcs/video/*.h"
        "srcs/video/*.cpp"
        "srcs/utils/*.h"
        "srcs/utils/*cpp"
        "srcs/TomasCommandLineTools/*.h"
        "srcs/TomasCommandLineTools/*.cpp"
        "srcs/*.h"
        "srcs/*.cpp"
        "resources/*.qrc"
                )

qt_standard_project_setup()

qt_add_executable(${name} ${srcs})

target_link_libraries(${name} PRIVATE 
                        Qt6::Core
                        Qt6::Gui
                        Qt6::Widgets
                        Qt6::Charts
                        ${OpenCV_LIBRARIES}
                        pybind11::embed
                        )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_property(TARGET ${name} PROPERTY WIN32_EXECUTABLE false)
endif()
