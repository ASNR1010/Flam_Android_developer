cmake_minimum_required(VERSION 3.10)
project(ParticleSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

include_directories(
    external/glad/include
    external/glfw/include
    ${OPENGL_INCLUDE_DIRS}
)

file(GLOB SRC "src/*.cpp")

add_executable(ParticleSystem ${SRC})
target_link_libraries(ParticleSystem glad glfw ${OPENGL_gl_LIBRARY})
