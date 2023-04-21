cmake_minimum_required(VERSION 3.10)

project(Please)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


file(GLOB_RECURSE please_SRC
     "./source/*.h"
     "./source/*.cpp"
)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


add_executable(${PROJECT_NAME} ${please_SRC})