# Specify minimum supported cmake version
cmake_minimum_required(VERSION 3.5)

# set the project name
project(CitationFixer)

## C++ 17
set(CMAKE_CXX_STANDARD 17)
##set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# Set the assets directory relative to the project root
set(ASSET_DIR "${CMAKE_SOURCE_DIR}/assets")

# Add this as a preprocessor definition
add_compile_definitions(ASSET_DIR="${ASSET_DIR}")

# ----------------------------
# Add pugixml
# ----------------------------
#${CMAKE_SOURCE_DIR}
add_library(pugixml STATIC
    F:/Koulu/Opari/CitationFixer/DuckX/ext/pugixml-1.9/src/pugixml.cpp
)

target_include_directories(pugixml PUBLIC
    F:/Koulu/Opari/CitationFixer/DuckX/ext/pugixml-1.9/src
)

#add_subdirectory(DuckX/ext/pugixml-1.15)

# ----------------------------
# Add zip library
# ----------------------------
add_library(zip STATIC
    F:/Koulu/Opari/CitationFixer/DuckX/ext/zip-0.1.15/src/zip.c
)

target_include_directories(zip PUBLIC
    F:/Koulu/Opari/CitationFixer/DuckX/ext/zip-0.1.15/src
)

# ----------------------------
# Add DuckX
# ----------------------------
file(GLOB DUCKX_SRC
	F:/Koulu/Opari/CitationFixer/DuckX/ext/DuckX-1.2.2/src/*.cpp
    #F:/Koulu/Opari/CitationFixer/DuckX/src/*.cpp
)

add_library(duckx STATIC ${DUCKX_SRC})

target_include_directories(duckx PUBLIC
    F:/Koulu/Opari/CitationFixer/DuckX/ext/DuckX-1.2.2/src
    F:/Koulu/Opari/CitationFixer/DuckX/ext/pugixml-1.9/src
    F:/Koulu/Opari/CitationFixer/DuckX/ext/zip-0.1.15/src
)

target_link_libraries(duckx
    pugixml
    zip
)

# ----------------------------
# Your executable
# ----------------------------
file(GLOB SRC_FILES "src/*.cpp")

add_executable(CitationFixer ${SRC_FILES})

target_link_libraries(CitationFixer
    duckx
)

