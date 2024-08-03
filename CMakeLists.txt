cmake_minimum_required(VERSION 3.10)
project(cppEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Eigen3

# Find CURL
find_package(CURL REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(fmt)

set(SOURCES
    src/main.cpp
    lib/stock.cpp
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests)
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    lib/GeometricBrownianMotion.cpp  
)

# Link libraries
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${CURL_LIBRARIES})
