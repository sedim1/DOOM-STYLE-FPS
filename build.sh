set -e  # Detiene la ejecución si hay algún error
set -x  # Muestra cada comando antes de ejecutarlo

BUILD_DIR="build"

# Establece un valor por defecto para BUILD_TYPE
BUILD_TYPE=${BUILD_TYPE:-Release}

# Asegúrate de que BUILD_TYPE no esté vacío
echo "BUILD_TYPE: $BUILD_TYPE"

# Verifica si el directorio de construcción no existe y créalo
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

pushd "$BUILD_DIR"

# Ejecuta CMake para configurar el proyecto
# Install Conan dependencies
conan profile detect --force
conan install .. --output-folder=. --build=missing --settings=build_type=$BUILD_TYPE

# Run CMake to generate the build system in the current directory (build/)
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1

# Compila el proyecto
cmake --build .

# Ejecuta el binario resultante (suponiendo que el nombre sea correcto)
./DOOM_STYLE

popd

