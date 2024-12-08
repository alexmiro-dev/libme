cmake_minimum_required(VERSION 3.28)  # For better C++23 modules support
project(libme VERSION 0.1.0 LANGUAGES CXX)

# Enable C++23 and modules support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable module scanning
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Enable compiler modules support for GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fmodules-ts)
endif()

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Library target
add_library(libme INTERFACE)
target_include_directories(libme INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Module definition
add_library(libme_modules)
target_sources(libme_modules
    PUBLIC
    FILE_SET CXX_MODULES FILES
    src/ds/circular_buffer.cppm
)

# Tests
enable_testing()
add_executable(libme_tests tests/ds/circular_buffer_test.cpp)
target_link_libraries(libme_tests PRIVATE Catch2::Catch2WithMain libme_modules)
add_test(NAME libme_tests COMMAND libme_tests)

# Examples
add_executable(basic_usage examples/basic_usage.cpp)
target_link_libraries(basic_usage PRIVATE libme_modules)

# Optional: Only build examples if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_custom_target(examples)
    add_dependencies(examples basic_usage)
endif()

# Installation rules
include(GNUInstallDirs)
install(TARGETS libme libme_modules
    EXPORT libmeTargets
    FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export configuration
install(EXPORT libmeTargets
    FILE libmeConfig.cmake
    NAMESPACE libme::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libme
)
