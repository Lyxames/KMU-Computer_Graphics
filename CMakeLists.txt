
cmake_minimum_required(VERSION 3.14)
project(app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#fltk
set(FLTK_BUILD_TEST OFF CACHE BOOL " " FORCE)
if(UNIX AND NOT APPLE) 
    set(OPTION_USE_PANGO ON CACHE BOOL " " FORCE)
endif()

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(FLTK
    GIT_REPOSITORY https://github.com/fltk/fltk
)
FetchContent_MakeAvailable(FLTK)

if(WIN32)
    set(GUI_TYPE WIN32)
elseif(APPLE)
    set(GUI_TYPE MACOSX_BUNDLE)
else()
    set(GUI_TYPE)
endif()

#glfw
#find_library(GLFW3_LIBRARY glfw)
#if(NOT GLFW3_LIBRARY)
#    message(FATAL_ERROR "GLFW3 library not found")
#endif()

########
# GLM  #
########

#glm https://github.com/g-truc/glm/releases/tag/1.0.1
#FetchContent_Declare(glm
#    GIT_REPOSITORY https://github.com/g-truc/glm
#)
#FetchContent_MakeAvailable(glm)

add_subdirectory(include/glm/)

#execute_process(
#add_subdirectory(include/glm)
#include(include/glm/CMakeLists.txt)
#glm_static




###########
# cyclone #
###########

set(CYCLONE_LIBRARY_NAME cyclone)
set(CYCLONE_LIBRARY_SOURCE_FILES

  src/Cyclone/body.cpp
  src/Cyclone/collide_coarse.cpp
  src/Cyclone/collide_fine.cpp
  src/Cyclone/contacts.cpp
  src/Cyclone/core.cpp
  src/Cyclone/fgen.cpp
  src/Cyclone/joints.cpp
  src/Cyclone/particle.cpp
  src/Cyclone/pcontacts.cpp
  src/Cyclone/pfgen.cpp
  src/Cyclone/plinks.cpp
  src/Cyclone/pworld.cpp
  src/Cyclone/random.cpp
  src/Cyclone/world.cpp
)

set(CYCLONE_LIBRARY_INCLUDE_DIRECTORIES
  include/Cyclone
)


add_library(${CYCLONE_LIBRARY_NAME} STATIC ${CYCLONE_LIBRARY_SOURCE_FILES})
target_include_directories(${CYCLONE_LIBRARY_NAME} PUBLIC ${CYCLONE_LIBRARY_INCLUDE_DIRECTORIES}) # needed for visual studio
target_link_libraries(${CYCLONE_LIBRARY_NAME} PUBLIC ${FLTK} fltk_gl fltk_images fltk_png fltk_jpeg fltk_z GLUT::GLUT OpenGL::GL)  #${GLFW3_LIBRARY})

########
#  FL  #
########

#set(FL_LIBRARY_NAME fl)

#set(FL_LIBRARY_INCLUDE_DIRECTORIES
##  include/
#  include/FL
#  include/GL
#  include/glm
#)

#find_library(OPENGL_LIBRARY OpenGL)
#target_link_libraries(${CYCLONE_LIBRARY_NAME} PUBLIC ${OPENGL_LIBRARY})


###########
# project #
###########

set(SOURCE_FILES
  src/3DUtils.cpp
  src/DrawUtils.cpp
  src/main.cpp
  src/MMatrix.cpp
  src/MyGlWindow.cpp
  src/object.cpp
  src/stdafx.cpp
  src/timing.cpp
  src/Viewer.cpp
)
set(LIBRARY_INCLUDE_DIRECTORIES
  include/
#  include/FL
#  include/GL
#  include/glm
)



#set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${LIBRARY_SOURCE_FILES}) #add ${GUI_TYPE} between {PROJECT_NAME} & ${SOURCE_FILES} To create executable in app.app/Content/GUI_TYPE
target_link_libraries(${PROJECT_NAME} PUBLIC cyclone GLUT::GLUT OpenGL::GL) # if needed: fltk_gl fltk_images fltk_png fltk_jpeg fltk_z
target_include_directories(${PROJECT_NAME} PUBLIC ${fltk_SOURCE_DIR} ${fltk_BINARY_DIR} ${LIBRARY_INCLUDE_DIRECTORIES}) # needed for visual studio
#target_link_libraries(${PROJECT_NAME} PRIVATE fltk glm cyclone) # if needed: fltk_gl fltk_images fltk_png fltk_jpeg fltk_z

if(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
endif()
