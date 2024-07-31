cmake_minimum_required(VERSION 3.10)
project(cppEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Find curl package
find_package(CURL REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${CURL_LIBRARIES})