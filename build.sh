#FLAGS
FLAGS="-Wno-deprecated-declarations"

#Libs
MACOS_LIB="-framework GLUT -framework OpenGL -framework Carbon -framework fltk_gl -framework Cocoa"
#-framework fltk
#            -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT"

#MACOS_FLAG="-D__APPLE__"

LINUX_LIB="-lGL -lfltk -lfltk_gl -lGLU"

WINDOW="?"

g++ src/main.cpp \
    src/MyGlWindow.cpp \
    src/Viewer.cpp \
    src/timing.cpp \
    src/3DUtils.cpp \
    src/DrawUtils.cpp \
    src/MMatrix.cpp \
    src/Cyclone/particle.cpp \
    src/Cyclone/core.cpp \
    -I include/ \
    -I include/Cyclone \
    $FLAGS \
    $MACOS_LIB \
#    $MACOS_FLAG
