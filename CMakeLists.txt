cmake_minimum_required(VERSION 3.13)  # CMake version check
project(cppEngine CXX)           # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard

set(CMAKE_PREFIX_PATH /Users/adarshh_g/Downloads/libtorch)
set(SOURCES
    src/main.cpp
    lib/Normalizer.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Add main.cpp file of the project root directory as a source file
add_executable(${PROJECT_NAME} 
    src/main.cpp
    lib/Normalizer.cpp
)

# Add executable target with source files listed in SOURCE_FILES variable
target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES})