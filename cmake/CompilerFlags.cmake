# target definitions

if(GITHUB_ACTIONS)
    message("NOTE: GITHUB_ACTIONS defined")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GITHUB_ACTIONS)
endif()

###############################################################################

if(PROJECT_WARNINGS_AS_ERRORS)
    set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0 /utf-8 /MP)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

###############################################################################

# sanitizers
include(cmake/CustomStdlibAndSanitizers.cmake)

# Only apply sanitizers to our own target, not to SFML
set_custom_stdlib_and_sanitizers(${PROJECT_NAME} true)
