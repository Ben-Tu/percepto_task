cmake_minimum_required( VERSION 3.11 )
project( percepto LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" )


set( CMAKE_CXX_FLAGS_DEBUG "-g" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic" )


#####################
### BUILD TARGETS ###
#####################
set( TARGET percepto )
add_executable( ${TARGET}
        main.cpp
        tools.cpp
        converter.cpp
        client_tools.cpp
        )

set_property( TARGET ${TARGET} PROPERTY CXX_STANDARD 17 )
target_link_libraries( ${TARGET} paho-mqttpp3 paho-mqtt3as pthread)
target_link_libraries( ${TARGET} PRIVATE ${PAHO_BUILD_SHARED} )
target_link_libraries(${TARGET} PRIVATE ${PAHO_CPP_LIB})


option( WITH_DEBUG_PRINT "Print debug" OFF )
if (WITH_DEBUG_PRINT)
    add_definitions( -DWITH_DEBUG_PRINT=true )
endif ()