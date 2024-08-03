cmake_minimum_required(VERSION 3.10)
project(cppEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Eigen3
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Find CURL
find_package(CURL REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests)
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/GeometricBrownianMotion.cpp  
)

# Link libraries
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${CURL_LIBRARIES})
