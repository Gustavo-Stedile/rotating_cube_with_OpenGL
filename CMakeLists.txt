cmake_minimum_required(VERSION 3.29)

project(engine VERSION 0.1.0 LANGUAGES C CXX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(CTest)
enable_testing()

add_subdirectory(glew)
add_subdirectory(glfw)
add_subdirectory(glm)

include_directories("glew/include")

find_package(OpenGL REQUIRED)

add_executable(engine 
  src/VertexBuffer.h
  src/VertexBuffer.cpp
  src/IndexBuffer.h 
  src/IndexBuffer.cpp
  src/VertexArray.h
  src/VertexBufferLayout.h
  src/VertexArray.cpp
  src/Shader.h
  src/Shader.cpp
  src/Renderer.h
  src/Renderer.cpp
  src/main.cpp 
)

target_link_libraries(engine glfw)
target_link_libraries(engine OpenGL::GL)
target_link_libraries(engine libglew_static)
target_link_libraries(engine glm)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
