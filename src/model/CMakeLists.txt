add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/user)


set (Model_SOURCES ${Model_SOURCES} 
 					Model.cpp)


add_library(model OBJECT ${Model_SOURCES})
						
