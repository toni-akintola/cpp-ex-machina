cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(cppEngine)

set(CMAKE_CXX_STANDARD 20)



# Find curl package
find_package(CURL REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(Torch REQUIRED)
find_package(fmt)

set(SOURCES
    src/main.cpp
    lib/stock.cpp
)
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.6)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
# Link libraries
target_link_libraries(${PROJECT_NAME} 
    ${CURL_LIBRARIES}
    fmt::fmt
    Eigen3::Eigen
    nlohmann_json::nlohmann_json
    ${TORCH_LIBRARIES}
)