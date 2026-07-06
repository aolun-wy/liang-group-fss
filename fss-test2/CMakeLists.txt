# Minimum Version Required
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Name of the project
project(FSS_Test2)

# The package needed, Required, and User Interface (no Visulization for Expanse)
find_package(Geant4 REQUIRED ui_all vis_all)

# Include the files in this folder
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})

# Compile the source files in /src
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
# Compile the header files
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Copy the macro files
# Find all macro files in macros/
file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY ${macros} DESTINATION ${PROJECT_BINARY_DIR})

# create the executable file
add_executable(fss-test2 fss-test2.cc ${sources} ${headers})
# Link some libraries to the executable we have created
target_link_libraries(fss-test2 ${Geant4_LIBRARIES})

# template
add_custom_target(FSS_Test2 DEPENDS fss-test2)
