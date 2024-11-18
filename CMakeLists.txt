cmake_minimum_required(VERSION 3.10)
project(CubeDash)

# Configuration standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Chemin vers le dossier contenant SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies")

# Ajouter les chemins pour inclure les headers (header/)
include_directories("${CMAKE_SOURCE_DIR}/header" "${SFML_DIR}/include")

# Trouver automatiquement tous les fichiers sources dans le dossier src/
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Créer l'exécutable principal
add_executable(CubeDash ${PROJECT_SOURCES})

# Trouver la bibliothèque Freetype installée par Homebrew
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

# Ajouter OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(CubeDash ${OpenCV_LIBS})

# Lier les bibliothèques SFML et Freetype
target_link_libraries(CubeDash
    "${SFML_DIR}/lib/libsfml-graphics.dylib"
    "${SFML_DIR}/lib/libsfml-window.dylib"
    "${SFML_DIR}/lib/libsfml-system.dylib"
    ${FREETYPE_LIBRARIES}
)

# Assurer que les bibliothèques dynamiques SFML soient trouvées à l'exécution
set_target_properties(CubeDash PROPERTIES
    INSTALL_RPATH "${SFML_DIR}/lib"
)
 

