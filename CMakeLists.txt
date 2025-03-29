cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Kai)

project(${PROJECT_NAME})

set(BUILD_DEBUG ON)

if ( BUILD_DEBUG )
set(CMAKE_BUILD_TYPE Debug)
set( CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-build-debug")
else ()
set(CMAKE_BUILD_TYPE Release)
set( CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-build-release")
endif ()

set(CMAKE_TOOLCHAIN_FILE "conan_toolchain.cmake")

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(dpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} dpp::dpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${dpp_INCLUDE_DIRS})