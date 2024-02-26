cmake_minimum_required(VERSION 3.16)

set(name FastTracker)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.6.1/msvc2019_64")

list(APPEND CMAKE_PREFIX_PATH "C:/Users/tomaswu/myprograms/opencv/build")

include_directories("c:/Users/tomaswu/myprograms/opencv/build/include")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(opencv)

file(GLOB srcs "views/*.h" "views/*.cpp" "views/*.ui"
                "video/*.h" "video/*.cpp"
                "utils/*.h" "utils/*cpp"
                "TomasCommandLineTools/*.h" "TomasCommandLineTools/*.cpp"
                "srcs/*.h" "srcs/*.cpp"
                )

qt_add_executable(${name} ${srcs})

target_link_libraries(${name} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets opencv_world460)

set_property(TARGET ${name} PROPERTY WIN32_EXECUTABLE false)