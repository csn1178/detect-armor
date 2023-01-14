cmake_minimum_required(VERSION 3.20)
project(robomaster2)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR "D:\\Clion-openCV\\opencv\\mingw-build\\install")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
# "C_Test"与你工程的命名相关，注意和原来CMakeList.txt中的声明一致
add_executable(robomaster2 main.cpp Armor.cpp Armor.h)
target_link_libraries(robomaster2 ${OpenCV_LIBS})


