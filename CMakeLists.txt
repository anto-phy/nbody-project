cmake_minimum_required(VERSION 3.28)

project(nbody VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------------------------
# Dependencies
# --------------------------------------------------

set(CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/modules/"
    ${CMAKE_MODULE_PATH}
)

# Corrade
add_subdirectory(corrade EXCLUDE_FROM_ALL)

# Magnum
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
add_subdirectory(magnum EXCLUDE_FROM_ALL)

# --------------------------------------------------
# Compiler checks / assertions
# --------------------------------------------------

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_definitions(_GLIBCXX_ASSERTIONS)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_definitions(
        _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE
    )
endif()

# --------------------------------------------------
# Address + Undefined Behavior Sanitizers
# --------------------------------------------------

set(SANITIZER_FLAGS
    -fsanitize=address,undefined
)

set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} ${SANITIZER_FLAGS}"
)

set(CMAKE_EXE_LINKER_FLAGS_DEBUG
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${SANITIZER_FLAGS}"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_definitions(_GLIBCXX_SANITIZE_STD_ALLOCATOR)
endif()

# --------------------------------------------------
# Main executable
# --------------------------------------------------

add_executable(nbody
    apps/main.cpp
    src/body.cpp
    src/engine.cpp
    src/simulation.cpp
)

target_include_directories(nbody
    PRIVATE
        src
)

target_link_libraries(nbody
    PRIVATE
        Magnum::Magnum
        Magnum::GL
        Magnum::Shaders
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::Platform
)

# --------------------------------------------------
# Tests
# --------------------------------------------------

if(BUILD_TESTING)

    add_executable(nbody.t
        tests/main_test.cpp
        src/body.cpp
        src/simulation.cpp
    )

    target_include_directories(nbody.t
        PRIVATE
            src
    )

    add_test(
        NAME nbody.t
        COMMAND nbody.t
    )

endif()