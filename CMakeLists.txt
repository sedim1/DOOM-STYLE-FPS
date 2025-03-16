cmake_minimum_required(VERSION 3.24)
project(DOOM_STYLE)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find Libraries
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

# Incluir directorios de encabezados
include_directories(${PROJECT_SOURCE_DIR}/include)

# Buscar automáticamente todos los archivos .c y .cpp dentro de src/
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

# Crear el ejecutable
add_executable(DOOM_STYLE ${SOURCES})

#Link libraries to target
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} assimp)

