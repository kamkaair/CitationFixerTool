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
    ${CMAKE_SOURCE_DIR}/ext/pugixml-1.9/src/pugixml.cpp
)

target_include_directories(pugixml PUBLIC
    ${CMAKE_SOURCE_DIR}/ext/pugixml-1.9/src
)

#add_subdirectory(DuckX/ext/pugixml-1.15)

# ----------------------------
# Add zip library
# ----------------------------
add_library(zip STATIC
    ${CMAKE_SOURCE_DIR}/ext/zip-0.1.15/src/zip.c
)

target_include_directories(zip PUBLIC
    ${CMAKE_SOURCE_DIR}/ext/zip-0.1.15/src
)

# ----------------------------
# Add DuckX
# ----------------------------
file(GLOB DUCKX_SRC
	${CMAKE_SOURCE_DIR}/ext/DuckX-1.2.2/src/*.cpp
)

add_library(duckx STATIC ${DUCKX_SRC})

target_include_directories(duckx PUBLIC
	${CMAKE_SOURCE_DIR}/ext/DuckX-1.2.2/src
    ${CMAKE_SOURCE_DIR}/ext/pugixml-1.9/src
    ${CMAKE_SOURCE_DIR}/ext/zip-0.1.15/src
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

