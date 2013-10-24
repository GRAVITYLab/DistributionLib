cmake_minimum_required( VERSION 2.8 )

project( FieldPartitionLib )

# Use MPI compiler and linker
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})

# Use mpicxx to replace 
SET( CMAKE_C_COMPILER mpicc )
SET( CMAKE_CXX_COMPILER mpicxx )

# Set MPI path in windows
# In unix, it will probably find automatically
if( WIN32 )
	set(MPI_INSTALL_DIR "/home/abon/code/chaudhua/install" CACHE PATH "The path to MPI")
endif()

# Set ITL path
set(ITL_DIR "/home/abon/code/chaudhua/install" CACHE PATH "The path to ITL")

# Set OSUFlow path
set( OSUFLOW_INSTALL_DIR "/home/abon/install/osuflow/osuflow" CACHE PATH "Installed path of osuflow" )

# Include header file directory to the search path
#####
if( WIN32 )
	include_directories ( "${MPI_INSTALL_DIR}/include" )
endif()
#####
include_directories ( "${OSUFLOW_INSTALL_DIR}/include" )
#####
include_directories( "${ITL_DIR}/include" )
#####
include_directories ( "${PROJECT_SOURCE_DIR}/include" )

add_library( FieldPartitionLib STATIC 
                  ${PROJECT_SOURCE_DIR}/src/emd.c
				  ${PROJECT_SOURCE_DIR}/src/ITL_emdcomputer.cpp	
				  ${PROJECT_SOURCE_DIR}/src/ITL_distcomputer.cpp	
				  ${PROJECT_SOURCE_DIR}/src/ITL_distribution.cpp
				  ${PROJECT_SOURCE_DIR}/src/ITL_multidistribution.cpp
				  ${PROJECT_SOURCE_DIR}/src/ITL_spacetreenode.cpp )
     
# Installation Instructions
# lib is interpreted as relative to CMAKE_INSTALL_PREFIX
FILE(GLOB headers "${PROJECT_SOURCE_DIR}/include/*.h")
install( FILES ${headers} DESTINATION include )
install( TARGETS FieldPartitionLib DESTINATION lib )