cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Force C++17
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

project(Freezer)

enable_testing()

set (Freezer_VERSION_MAJOR 1)
set (Freezer_VERSION_MINOR 0)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra") #-Werror
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    	set(compilation "-g -O0")
    else()
    	set(compilation "-O2")
    endif()
    set(compilation "${compilation}")
endif()

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings} ${compilation}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${compilation}")


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/FreezerConfig.h.in"
  "${PROJECT_BINARY_DIR}/FreezerConfig.h"
  )
        

  
# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

set (CMAKE_INCLUDE_CURRENT_DIR ON)


set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)  

# Search dependencies

find_package(Qt5Widgets REQUIRED)
find_package(Boost 1.36.0 REQUIRED COMPONENTS filesystem serialization date_time )    
find_package( Threads )
  
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${Boost_INCLUDE_DIR})

set(OCUtils ${CMAKE_CURRENT_SOURCE_DIR}/utils/OCUtils)
include_directories(${OCUtils}/src)
include_directories(${OCUtils}/include)



set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_LIB_DIR ${PROJECT_DIR}/lib)
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

link_directories(${PROJECT_LIB_DIR})

set (PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
set (PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)


add_subdirectory(${PROJECT_SOURCE_DIR})

add_subdirectory(${PROJECT_TEST_DIR})




set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")




