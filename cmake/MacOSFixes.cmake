# macOS specific fixes for SFML and C++17 compatibility
if(APPLE)
    # Add required definitions for C++17 on macOS
    add_definitions(-D_LIBCPP_DISABLE_AVAILABILITY -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS deployment version" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LIBCPP_DISABLE_AVAILABILITY -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES")

    # Create the char_traits fix header
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
")

    # Create the SFML wrapper header
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sfml_wrapper.hpp" "
#pragma once
#include \"sfml_char_traits_fix.hpp\"
#include <SFML/Graphics.hpp>
")

    # Configure target with macOS fixes
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_SFML_CHAR_TRAITS_FIX)
    target_compile_options(${PROJECT_NAME} PRIVATE "-include${CMAKE_CURRENT_BINARY_DIR}/sfml_wrapper.hpp")

    # Create launcher script for macOS
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/launcher.command" "#!/bin/bash\ncd \"$(dirname \"$0\")\"\n./oop")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/launcher.command"
            DESTINATION ${DESTINATION_DIR}
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)

    # Find SFML include directories on macOS
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
