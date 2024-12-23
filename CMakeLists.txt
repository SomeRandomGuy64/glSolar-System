cmake_minimum_required(VERSION 3.30)
project(glSolarSystem
    VERSION 0.01
    DESCRIPTION "A simulation of the solar system made with OpenGL"
    LANGUAGES CXX
)

find_package(OpenGL REQUIRED)

# Add cmake directory to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include modular cmake configurations
include(compiler_options)

add_library(KHR INTERFACE)
target_include_directories(KHR INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

# Collect all shader files
file(GLOB SHADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.comp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.geom
)

# Add shaders
add_library(shaders INTERFACE)
target_include_directories(shaders INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
)
target_sources(shaders INTERFACE
    ${SHADER_FILES}
)

# Create source groups for shaders (Visual Studio filters)
source_group("Shaders" FILES ${SHADER_FILES})

# Main executable
add_executable(glSolarSystem
    src/main.cpp
    src/glad.c
    src/shader.h
    ${SHADER_FILES}  # Add shader files to the main target so they show up in VS
)

set_compiler_flags(glSolarSystem)

# Add vendor targets
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/imgui)

target_include_directories(glSolarSystem PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL/include
)

target_link_libraries(glSolarSystem PUBLIC 
    fmt
    imgui
    SDL3
    KHR
    stb
    glad
    glm
    shaders
	
	OpenGL::GL
)