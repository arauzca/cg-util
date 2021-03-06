# Define library. Only source files here!
project(CommonLibraries VERSION 0.1)

set( ASSIMP_INCLUDE_DIRS "${CMAKE_HOME_DIRECTORY}/_LIBS/ASSIMP/include"
                         "${CMAKE_BINARY_DIR}/_LIBS/ASSIMP/include" )

# setup package root directories
if(FOUND_REQUIRED_PACKAGES)
  set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH_OLD};/usr/local/lib/cmake")
  set( CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3")
  unset( FLTK_ROOT_DIR )
  unset( GLEW_ROOT_DIR )
  unset( GLM_ROOT_DIR )
else()
  set( FLTK_ROOT_DIR   "${CMAKE_HOME_DIRECTORY}/_LIBS/FLTK")
  set( GLEW_ROOT_DIR   "${CMAKE_HOME_DIRECTORY}/_LIBS/GLEW")
  set( GLM_ROOT_DIR    "${CMAKE_HOME_DIRECTORY}/_LIBS/GLM")
endif()


file( GLOB SRCS
        ./src/util/*.cpp
        ./src/util/*.c
        ./src/SOIL2/*.cpp
        ./src/SOIL2/*.c)
source_group("Source Files" FILES ${SRCS})

file(GLOB HDRS
          ./include/util/*.h
          ./include/util/*.hpp)
source_group("include" FILES ${HDRS})


# create library
add_library(commonlibs SHARED ${SRCS})


# find packages and libs
if(FOUND_REQUIRED_PACKAGES)
  find_package(PkgConfig REQUIRED)
  find_package(glfw3     REQUIRED NO_MODULE)
endif()

find_package(OpenCV    REQUIRED )
find_package(OpenGL REQUIRED)
find_package(FLTK   REQUIRED)
find_package(GLEW   REQUIRED STATIC)
find_package(GLM    REQUIRED)


# find framework (specific to mac)
if ( APPLE )
    find_library(COCOA_LIBRARY   Cocoa )
    find_library(IOKIT_LIBRARY   IOKit REQUIRED )
    find_library(COREVID_LIBRARY CoreVideo REQUIRED )
else()
    set(COCOA_LIBRARY "")
    set(IOKIT_LIBRARY "")
    set(COREVID_LIBRARY "")
endif( APPLE )


# setup package headers
include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${ASSIMP_INCLUDE_DIRS}
        ${FLTK_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIRS}
)


# set up headers for other projects
set( COMMONLIBS_INCLUDE_DIR "${CMAKE_HOME_DIRECTORY}/_LIBS/COMMONLIBS/include" )



# force older GLM versions to use radians instead of degrees
add_definitions( -DGLM_FORCE_RADIANS )


# add framework (specific to mac)
target_link_libraries(commonlibs
        glfw
        assimp
        ${OpenCV_LIBS}
        ${OPENGL_LIBRARIES}
        ${FLTK_LIBRARIES}
        ${GLEW_LIBRARY}
        ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY})

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(commonlibs PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# Let source and header files appear in the IDE
target_sources(commonlibs PUBLIC ${SRCS} ${HDRS})
# If we have compiler requirements for this library, list them
# here
set_property(TARGET commonlibs PROPERTY CXX_STANDARD 17)
#target_compile_features(mem_mngr
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# for cmake_install.cmake:
#   DIRECTORY   the content (directories and files) of this directory will copied to the destination directory
#   DESTINATION if defined relative the full path will be ${CMAKE_INSTALL_PREFIX}/[DESTINATION]
install(DIRECTORY include/ DESTINATION include/)
add_dependencies(commonlibs assimp)
