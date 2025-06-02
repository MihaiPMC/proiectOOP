cmake_minimum_required(VERSION 3.16)
project(ProiectOOP VERSION 1.0.0 LANGUAGES CXX)

# C++17 setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Installation directory setup
set(BIN_DIR "bin" CACHE STRING "Binary installation directory")
set(DESTINATION_DIR "${BIN_DIR}" CACHE STRING "Installation destination directory")

# Include options
include(cmake/Options.cmake)

# Ensure required directories exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Collect source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp" "include/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "src/*.h*" "include/*.h*")

# Create default main.cpp if no sources exist
if(NOT PROJECT_SOURCES)
    set(DEFAULT_MAIN_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    message(STATUS "No source files found. Creating a default main.cpp")
    file(WRITE ${DEFAULT_MAIN_CPP} "#include <SFML/Graphics.hpp>\n\nint main() {\n    sf::RenderWindow window(sf::VideoMode(800, 600), \"SFML Window\");\n    sf::CircleShape shape(100.f);\n    shape.setFillColor(sf::Color::Green);\n\n    while (window.isOpen()) {\n        sf::Event event;\n        while (window.pollEvent(event)) {\n            if (event.type == sf::Event::Closed)\n                window.close();\n        }\n\n        window.clear();\n        window.draw(shape);\n        window.display();\n    }\n\n    return 0;\n}\n")
    set(PROJECT_SOURCES ${DEFAULT_MAIN_CPP})
endif()

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "oop")
target_include_directories(${PROJECT_NAME} PRIVATE src include)

# Handle macOS specific fixes
if(APPLE)
    include(cmake/MacOSFixes.cmake)
endif()

# SFML configuration
set(SFML_VERSION 2.6.2)
set(SFML_COMPONENTS graphics window system audio)

# Try to find system SFML or build from source
find_package(SFML ${SFML_VERSION} COMPONENTS ${SFML_COMPONENTS})
if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG ${SFML_VERSION})
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif()

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Include compiler flags
include(cmake/CompilerFlags.cmake)

# Setup asset copying
include(cmake/CopyHelper.cmake)
copy_files(DIRECTORY assets)

# Set working directory for Visual Studio
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Installation configuration
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION ${DESTINATION_DIR} FILES_MATCHING PATTERN "*.*")
