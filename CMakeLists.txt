cmake_minimum_required(VERSION 3.13)  
project(cppEngine CXX)           
set(CMAKE_CXX_STANDARD 17)           

set(CMAKE_PREFIX_PATH /Users/adarshh_g/Downloads/libtorch)
set(SOURCES
    src/main.cpp
    lib/Normalizer.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CURL_INCLUDE_DIRS})
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(${PROJECT_NAME} 
    src/main.cpp
    lib/Normalizer.cpp
)

target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES})