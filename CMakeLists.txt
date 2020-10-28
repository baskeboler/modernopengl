cmake_minimum_required(VERSION 3.5)


set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(modernopengl LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_path(STB_INCLUDE_DIRS "stb.h")
  
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
find_package(X11 REQUIRED)
# note that the order is important for setting the libs
# use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype ${ASSIMP_LIBRARY})
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

set(CMAKE_EXE_LINKER_FLAGS  "-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl")

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Assimp CONFIG REQUIRED)

set(sources glad.c glad/glad.h KHR/khrplatform.h shader.cpp shader.h camera.cpp camera.h mesh.cpp mesh.h model.cpp model.h)
add_executable(modernopengl main.cpp ${sources})
target_include_directories(modernopengl PRIVATE ${STB_INCLUDE_DIRS})
target_link_libraries(modernopengl glfw glm assimp::assimp)

include_directories(.)
file(COPY shaders DESTINATION .)
file(COPY resources DESTINATION .)