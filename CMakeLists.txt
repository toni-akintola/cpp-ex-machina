cmake_minimum_required(VERSION 3.10)
project(cppEngine)

set(CMAKE_CXX_STANDARD 20)



# Find curl package
find_package(CURL REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(fmt)


# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(curl src/curl.cpp)
# Link libraries
target_link_libraries(curl ${CURL_LIBRARIES})
target_link_libraries(curl fmt::fmt)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${CURL_LIBRARIES})