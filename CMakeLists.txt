cmake_minimum_required (VERSION 3.13)
include(FetchContent)
project (
    Bulldozer 
    VERSION 0.9.5
)

add_subdirectory(sdk)
add_subdirectory(samples)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
        "MinSizeRel" "RelWithDebInfo")
endif()

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(thirdparty/json)
add_subdirectory(thirdparty/minhook)

find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/common"
    "${CMAKE_SOURCE_DIR}/sdk/include"
)

file(GLOB src
    src/*.cpp
    src/*.h
    src/*.hpp
)

set( SOURCE_FILES ${src} )
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLFW_LIBRARY}
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE ${CMAKE_DL_LIBS}
    PRIVATE minhook
    PRIVATE BulldozerSDK
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME "winmm"
    VERSION ${PROJECT_VERSION}
)

target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/minhook/include)
