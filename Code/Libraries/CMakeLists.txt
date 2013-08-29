include_directories(${CMAKEDEMO_SOURCE_DIR}/Code)
link_directories(${CMAKEDEMO_BINARY_DIR}/Code)
include_directories(${CMAKEDEMO_SOURCE_DIR}/Code/Libraries)
link_directories(${CMAKEDEMO_BINARY_DIR}/Code/Libraries)
include_directories(${CMAKEDEMO_SOURCE_DIR}/Code/OpenGLHandling)
link_directories(${CMAKEDEMO_BINARY_DIR}/Code/OpenGLHandling)
include_directories(${CMAKEDEMO_SOURCE_DIR}/Code)
link_directories(${CMAKEDEMO_BINARY_DIR}/Code)
include_directories(${CMAKEDEMO_SOURCE_DIR}/Code/VectorFieldManagement)
link_directories(${CMAKEDEMO_BINARY_DIR}/Code/VectorFieldManagement)

#these are all compiled the same way
set(LIBRARY aVector Color GL3 Material Point)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_library(Color Color.C)
add_library(Material Material.C)
add_library(aVector aVector.C)
add_library(Point Point.C)
add_library(GL3 GL3.C)

#foreach(library ${LIBRARY})
#  add_library(library ${library}.cpp)
#//  add_executable(${program} ${program}.cpp)
#//  target_link_libraries(${program} ${CORELIBS})
#endforeach(program)

#building just a library. 
#add_library(geometry geometry.cpp)

#add_executable(test_geometry test_geometry.cpp)
#linking against a custom library
#target_link_libraries(test_geometry ${CORELIBS} geometry)

