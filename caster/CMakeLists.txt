cmake_minimum_required(VERSION 3.16)

project(caster)

file(GLOB
    SRC

    *.c
    *.h
)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${glfw_SOURCE_DIR}/include
    PRIVATE ${glad_SOURCE_DIR}/include
    PRIVATE lodepng
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE glfw
    PRIVATE glad
    PRIVATE cglm
    PRIVATE stb
    PRIVATE lodepng
)
