cmake_minimum_required(VERSION 3.16)
project(ProiectOOP VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define installation directories
set(BIN_DIR "bin" CACHE STRING "Binary installation directory")
set(DESTINATION_DIR "${BIN_DIR}" CACHE STRING "Installation destination directory")

# For macOS, we need to handle special requirements BEFORE any targets are created
if(APPLE)
    # Set preprocessor definitions globally
    add_definitions(-D_LIBCPP_DISABLE_AVAILABILITY)
    add_definitions(-D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES)

    # Set the minimum macOS version to 10.15
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS deployment version" FORCE)

    # Explicitly add these flags to CXX_FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LIBCPP_DISABLE_AVAILABILITY -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES")
endif()

# Include custom CMake modules
include(cmake/Options.cmake)

# Ensure src directory exists
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Define source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "src/*.hpp" "src/*.h")

# If no source files found, use a default main.cpp
if(NOT PROJECT_SOURCES)
    set(DEFAULT_MAIN_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    message(STATUS "No source files found. Creating a default main.cpp at ${DEFAULT_MAIN_CPP}")

    file(WRITE ${DEFAULT_MAIN_CPP} "#include <SFML/Graphics.hpp>\n\nint main() {\n    sf::RenderWindow window(sf::VideoMode(800, 600), \"SFML Window\");\n    sf::CircleShape shape(100.f);\n    shape.setFillColor(sf::Color::Green);\n\n    while (window.isOpen()) {\n        sf::Event event;\n        while (window.pollEvent(event)) {\n            if (event.type == sf::Event::Closed)\n                window.close();\n        }\n\n        window.clear();\n        window.draw(shape);\n        window.display();\n    }\n\n    return 0;\n}\n")

    set(PROJECT_SOURCES ${DEFAULT_MAIN_CPP}
            src/Zoo.cpp
            include/Zoo.hpp
            src/Animal.cpp
            include/Animal.hpp
            src/Habitat.cpp
            include/Habitat.hpp
            src/Visitor.cpp
            include/Visitor.hpp
            src/Game.cpp
            include/Game.hpp
            include/Bird.hpp
            include/Mammal.hpp
            include/Fish.hpp
            src/Bird.cpp
            src/Mammal.cpp
            src/Fish.cpp
            src/AnimalException.cpp
            include/AnimalException.hpp
            src/BudgetException.cpp
            include/BudgetException.hpp
            src/ZooExceptions.cpp
            include/ZooExceptions.hpp
            src/HabitatException.cpp
            include/HabitatException.hpp
    )
endif()

# Create the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Set the output name to match the expected executable name in GitHub Actions
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "oop")

# Specify include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Using a different approach for macOS - undefine the problematic template
if(APPLE)
    # Try another approach - explicitly create a char_traits specialization before SFML includes it
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sfml_char_traits_fix.hpp" "
#pragma once
#include <cstddef>      // for size_t
#include <ios>          // for streamoff, streampos
#include <cwchar>       // for mbstate_t
#include <cstdio>       // for EOF
#include <cstring>      // for memcpy and memmove

// Fix for the libc++ namespace issue on macOS - only in std::__1 namespace
namespace std { inline namespace __1 {
    template<> struct char_traits<unsigned int> {
        typedef unsigned int char_type;
        typedef int int_type;
        typedef streamoff off_type;
        typedef streampos pos_type;
        typedef mbstate_t state_type;

        static void assign(char_type& c1, const char_type& c2) noexcept { c1 = c2; }
        static bool eq(const char_type& c1, const char_type& c2) noexcept { return c1 == c2; }
        static bool lt(const char_type& c1, const char_type& c2) noexcept { return c1 < c2; }

        static int compare(const char_type* s1, const char_type* s2, size_t n) {
            for (size_t i = 0; i < n; ++i) {
                if (lt(s1[i], s2[i])) return -1;
                if (lt(s2[i], s1[i])) return 1;
            }
            return 0;
        }

        static size_t length(const char_type* s) {
            size_t len = 0;
            while (!eq(s[len], char_type())) ++len;
            return len;
        }

        static const char_type* find(const char_type* s, size_t n, const char_type& a) {
            for (size_t i = 0; i < n; ++i) {
                if (eq(s[i], a)) return s + i;
            }
            return nullptr;
        }

        static char_type* move(char_type* s1, const char_type* s2, size_t n) {
            if (n == 0) return s1;
            return static_cast<char_type*>(memmove(s1, s2, n * sizeof(char_type)));
        }

        static char_type* copy(char_type* s1, const char_type* s2, size_t n) {
            return static_cast<char_type*>(memcpy(s1, s2, n * sizeof(char_type)));
        }

        static char_type* assign(char_type* s, size_t n, char_type a) {
            for (size_t i = 0; i < n; ++i) s[i] = a;
            return s;
        }

        static char_type to_char_type(const int_type& c) noexcept { return char_type(c); }
        static int_type to_int_type(const char_type& c) noexcept { return int_type(c); }
        static bool eq_int_type(const int_type& c1, const int_type& c2) noexcept { return c1 == c2; }
        static int_type eof() noexcept { return int_type(EOF); }
        static int_type not_eof(const int_type& c) noexcept { return c == eof() ? int_type(0) : c; }
    };
}}

// Removed the redefinition in the std namespace that was causing the error
")

    # Include our fix header
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_SFML_CHAR_TRAITS_FIX)

    # Create a wrapper header for SFML/Graphics.hpp
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sfml_wrapper.hpp" "
#pragma once
#include \"sfml_char_traits_fix.hpp\"
#include <SFML/Graphics.hpp>
")

    # Force our wrapped SFML headers to be included first
    target_compile_options(${PROJECT_NAME} PRIVATE "-include${CMAKE_CURRENT_BINARY_DIR}/sfml_wrapper.hpp")
endif()

# Find SFML 2.6.2
set(SFML_VERSION 2.6.2)
set(SFML_COMPONENTS graphics window system audio)

# Try to find SFML with the specific version
find_package(SFML ${SFML_VERSION} COMPONENTS ${SFML_COMPONENTS})

if(SFML_FOUND)
    message(STATUS "Using system-installed SFML ${SFML_VERSION}")

    # On macOS with Homebrew SFML, add include directories
    if(APPLE)
        find_path(SFML_INCLUDE_DIR SFML/Config.hpp
            PATHS
            /opt/homebrew/include
            /usr/local/include
            /usr/include
        )
        if(SFML_INCLUDE_DIR)
            target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_INCLUDE_DIR})
        endif()
    endif()
else()
    message(STATUS "SFML ${SFML_VERSION} not found, building from source")
    # If not found, use FetchContent to download and build SFML
    include(FetchContent)

    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
    )

    # Configure SFML options
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SFML)
endif()

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Set compiler flags
include(cmake/CompilerFlags.cmake)

# Create assets directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Copy assets to build directory
include(cmake/CopyHelper.cmake)
copy_files(
    DIRECTORY assets
)

# Set working directory for Visual Studio
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Install configuration - important for GitHub Actions artifacts
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})

# Install additional files needed by the application (for GitHub Actions)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        DESTINATION ${DESTINATION_DIR}
        FILES_MATCHING
        PATTERN "*.*")

# Create and install a launcher script for macOS
if(APPLE)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/launcher.command"
        "#!/bin/bash\ncd \"$(dirname \"$0\")\"\n./oop")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/launcher.command"
            DESTINATION ${DESTINATION_DIR}
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
endif()
