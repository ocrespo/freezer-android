
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/freezer)

set (Model_SOURCES ${Model_SOURCES} 
 					${CMAKE_CURRENT_SOURCE_DIR}/User.cpp
 					PARENT_SCOPE)
