cmake_minimum_required(VERSION 3.16)

project(line)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${glfw_SOURCE_DIR}/include
    PRIVATE ${glad_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE glfw 
    PRIVATE glm 
    PRIVATE glad
)

