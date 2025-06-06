cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME Kai)

project(${PROJECT_NAME})

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_library(${PROJECT_NAME}Lib STATIC ${SRC_FILES})
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/app/kai.cpp)

include(cmake/CPM.cmake)

# Add Discord Bot Library
CPMAddPackage("gh:brainboxdotcc/DPP@10.1.2")

target_link_libraries(${PROJECT_NAME} PRIVATE dpp)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE dpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Lib)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME}Lib PRIVATE include)

if (WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD # Copy every needed dll to the bin dir
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy
        "${DPP_BINARY_DIR}/library/zlib1.dll"
        "${DPP_BINARY_DIR}/library/libssl-1_1-x64.dll"
        "${DPP_BINARY_DIR}/library/libcrypto-1_1-x64.dll"
        "${DPP_BINARY_DIR}/library/opus.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
)
endif (WIN32)

if (DPP_ADDED)
    message(STATUS "Applying patch to DPP...")

    execute_process(
        COMMAND git apply ${CMAKE_SOURCE_DIR}/patches/poll-include.patch
        WORKING_DIRECTORY ${DPP_SOURCE_DIR}
        RESULT_VARIABLE PATCH_RESULT
        ERROR_VARIABLE PATCH_ERROR
    )

    if (PATCH_RESULT)
        message(STATUS "Patch does not apply for current version.")
    else()
        message(STATUS "Patch applied successfully.")
    endif()
endif()
# End Discord Bot Library

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG_VALUE 1)
else()
    set(DEBUG_VALUE 0)
endif()

file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/include/Kai/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Kai/config.h)


install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION bin
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)