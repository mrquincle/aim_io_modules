##########################################################################################
#               _/\/\/\/\/\____/\/\/\/\__/\/\/\/\/\____/\/\_______                       #
#               _/\/\____/\/\____/\/\____/\/\____/\/\__/\/\_______                       #
#               _/\/\/\/\/\______/\/\____/\/\____/\/\__/\/\_______                       #
#               _/\/\__/\/\______/\/\____/\/\____/\/\__/\/\_______                       #
#               _/\/\____/\/\__/\/\/\/\__/\/\/\/\/\____/\/\/\/\/\_                       #
#               __________________________________________________                       #
##########################################################################################
# Part of RIDL, the RUR IDL builder which generates modules for middlewares, including 
# lightweight (robotic) middleware like YARP. 
# This makefile is part of a cmake build system. The code falls under the Lesser General 
# Public License (LGPL GNU v3).

# Author:	 Anne C. van Rossum (Almende B.V.)
# Date: 	 Nov 7, 2011
#
# ASCII Art generated by: http://www.network-science.de/ascii/ with font "ticks".
#
# Copyright © 2011 Anne van Rossum <anne@almende.com>
##########################################################################################

IF(WIN32)
cmake_minimum_required(VERSION 2.6)
ELSE(WIN32)
cmake_minimum_required(VERSION 2.4)
ENDIF(WIN32)

# The directory with all the FindXXX modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/aim/cmake/")

SET(PROJECT_NAME "ExampleModule")

# The macro below forces the build directory to be different from source directory:
INCLUDE( MacroEnsureOutOfSourceBuild )
MACRO_ENSURE_OUT_OF_SOURCE_BUILD(
	"${PROJECT_NAME} requires an out of source build."
)

# Build options
OPTION(BUILD_YARP      "Build module with YARP" OFF)
OPTION(BUILD_ROS       "Build module with ROS" OFF)

# Should actually only be turned on if the others are OFF
OPTION(BUILD_STANDARD  "DEFAULT build option" ON)

# Start a project
PROJECT(${PROJECT_NAME})

# Find all cmake packages
IF (BUILD_YARP)
  MESSAGE("YARP build, useful for YARP middleware")
  FIND_PACKAGE(YARP REQUIRED)
  INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
  SET(LIBS ${LIBS} ${YARP_LIBRARIES})
ENDIF (BUILD_YARP)

IF (BUILD_ROS)
  MESSAGE("ROS build, useful for ROS middleware")
  include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
  rosbuild_init()
ENDIF (BUILD_ROS)

# Some debug information
MESSAGE("[*] \"${PROJECT_NAME}\" uses the following CXX flags: \"${CMAKE_CXX_FLAGS}\" (can be empty)")
MESSAGE ("[*] Libraries included: ${LIBS}")

# Source directory
SET(SOURCE_DIR "src")
SET(INCLUDE_DIR "inc")

# Source directory for AIM related files
SET(AIM_DIR "aim")

# Warning for user when standard build
IF (BUILD_STANDARD)
  MESSAGE("Standard build, not usable in middleware yet")
ENDIF (BUILD_STANDARD)

# Search for functional source code
FILE(GLOB folder_source ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cc ${SOURCE_DIR}/*.c)
FILE(GLOB folder_header ${INCLUDE_DIR}/*.h)
SOURCE_GROUP("Source files" FILES ${folder_source})
SOURCE_GROUP("Header files" FILES ${folder_header})

# Search for wrapper source code generated by the aim tools and rur-builder
FILE(GLOB aim_source ${AIM_DIR}/*.cpp ${AIM_DIR}/*.cc ${AIM_DIR}/*.c)
FILE(GLOB aim_header ${AIM_DIR}/*.h)
SOURCE_GROUP("Source files (AIM)" FILES ${aim_source})
SOURCE_GROUP("Header files (AIM)" FILES ${aim_header})

# Automatically add include directories if needed.
FOREACH(header_file ${folder_header})
  GET_FILENAME_COMPONENT(p ${header_file} PATH)
  INCLUDE_DIRECTORIES(${p})
ENDFOREACH(header_file ${folder_header})

FOREACH(header_file ${aim_header})
  GET_FILENAME_COMPONENT(p ${header_file} PATH)
  INCLUDE_DIRECTORIES(${p})
ENDFOREACH(header_file ${aim_header})

#rosbuild_add_executable(${PROJECT_NAME} ${folder_source} ${folder_header})
INCLUDE_DIRECTORIES(aim/inc)

# Set up our main executable.
IF (folder_source OR aim_source)
   ADD_EXECUTABLE(${PROJECT_NAME} ${folder_source} ${aim_source} ${folder_header} ${aim_header})
   TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBS})
   install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)   
ELSE ()
  MESSAGE(FATAL_ERROR "No source code files found. Please add something")
ENDIF ()

