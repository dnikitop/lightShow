cmake_minimum_required(VERSION 2.8.3)
project(srsnode_fun)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    srslib_framework
)



include_directories(include
    src/
    include/
    ${catkin_INCLUDE_DIRS}
    ${srslib_framework_INCLUDE_DIRS}
    ${OpenGL_INCLUDE_DIRS}
 	${GLUT_INCLUDE_DIRS}
)


####################################################################################################
# Target

catkin_package(
    DEPENDS
)

add_executable(srsnode_fun_lights
    src/first.cpp src/chuckLight.cpp src/Color.cpp src/Cylinder.cpp src/Floor.cpp src/Light.cpp src/Point.cpp src/Rectangle.cpp src/Shape.cpp  src/Chuck.cpp
)


add_dependencies(srsnode_fun_lights
    ${catkin_EXPORTED_TARGETS}

)


target_link_libraries(srsnode_fun_lights
    ${catkin_LIBRARIES}

    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
)

####################################################################################################
# Installation

install(TARGETS srsnode_fun_lights
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY launch/
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)


####################################################################################################