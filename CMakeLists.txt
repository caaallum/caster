cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET OFF)

include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw
    GIT_TAG         3.3.8
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
)
set(GLFW_BUILD_EXAMPLES     OFF CACHE BOOL "Build Examples" FORCE)
set(GLFW_BUILD_TESTS        OFF CACHE BOOL "Build tests" FORCE)
set(GLFW_BUILD_DOCS         OFF CACHE BOOL "Build docs" FORCE)
set(GLFW_INSTALL            OFF CACHE BOOL "Configure an install" FORCE)

FetchContent_Declare(glad
    GIT_REPOSITORY  https://github.com/Dav1dde/glad
    GIT_TAG         v0.1.33
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
)
set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)

FetchContent_Declare(cjson
    GIT_REPOSITORY  https://github.com/DaveGamble/cJSON.git
    GIT_TAG         v1.7.16
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
)
# set(ENABLE_CJSON_UTILS  ON  CACHE BOOL "Enable cJSON utils" FORCE)
set(ENABLE_CJSON_TEST   OFF CACHE BOOL "Disable cJSON tests" FORCE)

FetchContent_Declare(cglm
    GIT_REPOSITORY  https://github.com/recp/cglm.git
    GIT_TAG         v0.9.0
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
)

FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)

FetchContent_GetProperties(stb)
if (NOT stb_POPULATED)
    FetchContent_Populate(stb)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()

FetchContent_MakeAvailable(glfw glad cglm cjson)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(lodepng)
add_subdirectory(caster)
