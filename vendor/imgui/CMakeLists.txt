cmake_minimum_required(VERSION 3.30)

add_library(imgui STATIC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_opengl3.cpp
    imgui_impl_sdl3.cpp
)

target_include_directories(imgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Get SDL include directories
target_include_directories(imgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/vendor/SDL/include
)

# Find SDL3's build directory and add its library path
if(WIN32)
    target_link_directories(imgui PUBLIC
        ${CMAKE_BINARY_DIR}/vendor/SDL/Debug
        ${CMAKE_BINARY_DIR}/vendor/SDL/Release
    )
endif()

# Link against SDL3
target_link_libraries(imgui PUBLIC SDL3)

# Enable C++11 (or higher if needed)
target_compile_features(imgui PUBLIC cxx_std_11)

# Windows-specific settings
if(WIN32)
    target_compile_definitions(imgui PRIVATE
        WIN32
        _WINDOWS
        UNICODE
        _UNICODE
    )
endif()
