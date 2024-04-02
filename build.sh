g++ -m32    \
    src/main.cpp \
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
    -lGL \
    -lfltk \
    -lfltk_gl \
    -lGLU \
