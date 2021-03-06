cmake_minimum_required ( VERSION 3.10 )
project ( ReMo VERSION 0.0.3)
set( ReMo_VERSION_ABI 2 )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif( NOT CMAKE_BUILD_TYPE )

#TODO: Eliminate -Wno-deprecated-declarations This is needed because the use of some ffmpeg functions and objects.
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations" )

if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
    message( FATAL "no in source building allowed." )
endif( )

if( NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake )
    message( FATAL_ERROR "CMake/common missing, run: git submodule update --init")
endif( )

list( APPEND CMAKE_MODULE_PATH
 ${PROJECT_SOURCE_DIR}/CMake
 ${CMAKE_SOURCE_DIR}/CMake/common )

include( GitExternal )

option( REMO_WITH_EXAMPLES "REMO_WITH_EXAMPLES" OFF )

set( REMO_DESCRIPTION "ReMo: RenderMovie is a multipurpose video syntesis framework." )
set( REMO_LICENSE LGPL )
set( COMMON_PROJECT_DOMAIN es.gmrv )

include( Common )

common_find_package( Threads SYSTEM REQUIRED )
common_find_package( FFmpeg REQUIRED )

common_find_package( OpenGL SYSTEM )
common_find_package( GLUT SYSTEM )
common_find_package( GLEW SYSTEM )

common_find_package( SDL SYSTEM )

common_find_package( Poco SYSTEM COMPONENTS Util XML JSON NetSSL Crypto Net Foundation )

common_find_package( webstreamer SYSTEM )
if ( Poco_FOUND AND WEBSTREAMER_FOUND )
  common_find_package( Poco REQUIRED COMPONENTS Zip )
endif ( )

common_find_package_post( )

add_subdirectory( ReMo )

if ( REMO_WITH_EXAMPLES )
    add_subdirectory( examples )
endif ()

if ( WEBSTREAMER_FOUND )
    #TODO: Change ${WEBSTREAMER_CMAKE_DIR} when cmake target rule will be incorportaed into webstreamer!
    file( GLOB WS_CLIENT "${WEBSTREAMER_CMAKE_DIR}/../client/*" )
    file( COPY ${WS_CLIENT} DESTINATION "${CMAKE_BINARY_DIR}/bin/client" )

    file( GLOB WS_CFG "${WEBSTREAMER_CMAKE_DIR}/../webstreamer_config.json" )
    file( COPY ${WS_CFG} DESTINATION "${CMAKE_BINARY_DIR}/bin" )
endif ( )
    
set( DOCS README.md LICENSE.txt )
install( FILES ${DOCS} DESTINATION share/ReMo COMPONENT dev )

set( DOXYGEN_MAINPAGE_MD README.md )
set( DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md )
include( DoxygenRule )

include( CPackConfig )
include( CTest )
