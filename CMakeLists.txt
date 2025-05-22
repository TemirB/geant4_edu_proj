#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(SIMPLEGEO)

#----------------------------------------------------------------------------
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# ГЛАВНЫЙ ФАЙЛ main.cpp — лежит в корне!
set(main_src ${PROJECT_SOURCE_DIR}/main.cpp)

#----------------------------------------------------------------------------
add_executable(main.exe ${main_src} ${sources} ${headers})
target_link_libraries(main.exe ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
install(TARGETS main.exe DESTINATION bin)
