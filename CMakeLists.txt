cmake_minimum_required(VERSION 3.10)
project(ImageViewer)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories for header files
include_directories(${OpenCV_INCLUDE_DIRS} src)

# Add executable and link source files from the 'src' folder
add_executable(image_viewer src/main.cpp src/mouse_events.cpp src/image_utils.cpp)

# Link the executable with OpenCV libraries
target_link_libraries(image_viewer ${OpenCV_LIBS})
