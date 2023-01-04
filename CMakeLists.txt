cmake_minimum_required(VERSION 3.6.0)

# Add vcpkg - already compliles the libraries
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" 
	CACHE STRING "Vcpkg toolchain file"
)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION true)

# Project name
project("vis1_volvis")

# Qt flags for simplicity
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Define where the Qt ui file is located
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/res/")

# All source files
file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# And build an exe with it
add_executable(vis1_volvis "${SRC_FILES}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vis1_volvis)

# Qt5 packages necessary for our project
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(vis1_volvis Qt5::Widgets)

# Include all header files (located in the same folder as glsw.h for sure)
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/include")
target_include_directories(vis1_volvis PRIVATE ${INC_DIR})

find_package(netCDF CONFIG REQUIRED)
find_library(NETCDF_LIBRARY netcdf)
target_link_libraries(vis1_volvis ${NETCDF_LIBRARY})

find_library(GLSW_LIBRARY glsw)
target_link_libraries(vis1_volvis ${GLSW_LIBRARY})

find_package(GLEW REQUIRED)
target_link_libraries(vis1_volvis GLEW::GLEW)

# Only build Debug & Release
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE)
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
ENDIF()